from pykinect2 import PyKinectV2
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import pygame

PERSONS = ['BERT',                          #0
           'DEMING',                        #1
           #'NIELS',                         #2
           ]                         
ACTIONS = ['DEFAULT',                       #0
           'EMERGENCY_STOP',                #1
           'RH_NORMAL_STOP',                #2
           'RH_MOVE_RIGHT',                 #3
           'LH_MOVE_LEFT',                  #4
           'RH_MOVE_FORWARD',               #5
           'RH_ROTATE_ABOUT_AXIS',          #6
           ]                        


DEBUG_FPS = 2
DEFAULT_FPS = 15

SKELETON_LINE_THICKNESS = 18
SKELETON_CIRCLE_RADIUS = 15
SKELETON_COLOR = (255, 0, 0) # red

JOINTS = [
    { 'name': 'SpineBase'       , 'weight': 0 } ,           
    { 'name': 'SpineMid'        , 'weight': 0 } ,            
    { 'name': 'Neck'            , 'weight': 0 } ,                
    { 'name': 'Head'            , 'weight': 0 } ,                
    { 'name': 'ShoulderLeft'    , 'weight': 1 } ,        
    { 'name': 'ElbowLeft'       , 'weight': 1 } ,           
    { 'name': 'WristLeft'       , 'weight': 1 } ,           
    { 'name': 'HandLeft'        , 'weight': 1 } ,            
    { 'name': 'ShoulderRight'   , 'weight': 1 } ,       
    { 'name': 'ElbowRight'      , 'weight': 1 } ,          
    { 'name': 'WristRight'      , 'weight': 1 } ,          
    { 'name': 'HandRight'       , 'weight': 1 } ,           
    { 'name': 'HipLeft'         , 'weight': 0 } ,             
    { 'name': 'KneeLeft'        , 'weight': 0 } ,            
    { 'name': 'AnkleLeft'       , 'weight': 0 } ,           
    { 'name': 'FootLeft'        , 'weight': 0 } ,            
    { 'name': 'HipRight'        , 'weight': 0 } ,            
    { 'name': 'KneeRight'       , 'weight': 0 } ,           
    { 'name': 'AnkleRight'      , 'weight': 0 } ,          
    { 'name': 'FootRight'       , 'weight': 0 } ,           
    { 'name': 'SpineShoulder'   , 'weight': 0 } ,       
    { 'name': 'HandTipLeft'     , 'weight': 0 } ,         
    { 'name': 'ThumbLeft'       , 'weight': 0 } ,           
    { 'name': 'HandTipRight'    , 'weight': 0 } ,        
    { 'name': 'ThumbRight'      , 'weight': 0 } ,          
]

# List of all the connections between two joints
JOINT_CONNECTIONS = [
    # Torso
    [PyKinectV2.JointType_Head,             PyKinectV2.JointType_Neck],
    [PyKinectV2.JointType_Neck,             PyKinectV2.JointType_SpineShoulder],
    [PyKinectV2.JointType_SpineShoulder,    PyKinectV2.JointType_SpineMid],
    [PyKinectV2.JointType_SpineMid,         PyKinectV2.JointType_SpineBase],
    [PyKinectV2.JointType_SpineShoulder,    PyKinectV2.JointType_ShoulderRight],
    [PyKinectV2.JointType_SpineShoulder,    PyKinectV2.JointType_ShoulderLeft],
    [PyKinectV2.JointType_SpineBase,        PyKinectV2.JointType_HipRight],
    [PyKinectV2.JointType_SpineBase,        PyKinectV2.JointType_HipLeft],
    # Right arm
    [PyKinectV2.JointType_ShoulderRight,    PyKinectV2.JointType_ElbowRight],
    [PyKinectV2.JointType_ElbowRight,       PyKinectV2.JointType_WristRight],
    [PyKinectV2.JointType_WristRight,       PyKinectV2.JointType_HandRight],
    [PyKinectV2.JointType_HandRight,        PyKinectV2.JointType_HandTipRight],
    [PyKinectV2.JointType_WristRight,       PyKinectV2.JointType_ThumbRight],
    # Left arm
    [PyKinectV2.JointType_ShoulderLeft,     PyKinectV2.JointType_ElbowLeft],
    [PyKinectV2.JointType_ElbowLeft,        PyKinectV2.JointType_WristLeft],
    [PyKinectV2.JointType_WristLeft,        PyKinectV2.JointType_HandLeft],
    [PyKinectV2.JointType_HandLeft,         PyKinectV2.JointType_HandTipLeft],
    [PyKinectV2.JointType_WristLeft,        PyKinectV2.JointType_ThumbLeft],
    # Right leg
    [PyKinectV2.JointType_HipRight,         PyKinectV2.JointType_KneeRight],
    [PyKinectV2.JointType_KneeRight,        PyKinectV2.JointType_AnkleRight],
    [PyKinectV2.JointType_AnkleRight,       PyKinectV2.JointType_FootRight],
    # Left leg
    [PyKinectV2.JointType_HipLeft,          PyKinectV2.JointType_KneeLeft],
    [PyKinectV2.JointType_KneeLeft,         PyKinectV2.JointType_AnkleLeft],
    [PyKinectV2.JointType_AnkleLeft,        PyKinectV2.JointType_FootLeft]
]

JOINT_TREE = {
    # hierarchical representation of the skeleton
    PyKinectV2.JointType_SpineBase: [
        PyKinectV2.JointType_SpineMid,   # 17.9  cm
        PyKinectV2.JointType_HipLeft,    # 14.15 cm
        PyKinectV2.JointType_HipRight    # 14.15 cm
        ],

    PyKinectV2.JointType_SpineMid: [PyKinectV2.JointType_SpineShoulder],   # 33.7 cm

    PyKinectV2.JointType_SpineShoulder: [
        PyKinectV2.JointType_Neck,         # 8.4 cm
        PyKinectV2.JointType_ShoulderLeft, # 11 cm
        PyKinectV2.JointType_ShoulderRight  # 11 cm
        ],
        
    PyKinectV2.JointType_Neck: [PyKinectV2.JointType_Head],    # 8.4 cm

    PyKinectV2.JointType_HipLeft: [PyKinectV2.JointType_KneeLeft],   # 55 cm
    PyKinectV2.JointType_KneeLeft: [PyKinectV2.JointType_AnkleLeft], # 22 cm
    PyKinectV2.JointType_AnkleLeft: [PyKinectV2.JointType_FootLeft], # 13 cm

    PyKinectV2.JointType_HipRight: [PyKinectV2.JointType_KneeRight], # 55 cm
    PyKinectV2.JointType_KneeRight: [PyKinectV2.JointType_AnkleRight], # 22 cm
    PyKinectV2.JointType_AnkleRight: [PyKinectV2.JointType_FootRight], # 13 cm

    PyKinectV2.JointType_ShoulderLeft: [PyKinectV2.JointType_ElbowLeft], # 33.2 cm
    PyKinectV2.JointType_ElbowLeft : [PyKinectV2.JointType_WristLeft],  # 27.1 cm

    PyKinectV2.JointType_WristLeft : [
        PyKinectV2.JointType_HandLeft, # 7cm
        PyKinectV2.JointType_ThumbLeft# 7cm
        ],

    PyKinectV2.JointType_HandLeft : [PyKinectV2.JointType_HandTipLeft], # 13.2 cm

    PyKinectV2.JointType_ShoulderRight: [PyKinectV2.JointType_ElbowRight], # 33.2 cm
    PyKinectV2.JointType_ElbowRight : [PyKinectV2.JointType_WristRight],   # 27.1 cm

    PyKinectV2.JointType_WristRight : [
        PyKinectV2.JointType_HandRight, # 7cm
        PyKinectV2.JointType_ThumbRight # 7cm
        ], 

    PyKinectV2.JointType_HandRight : [PyKinectV2.JointType_HandTipRight], # 13.2 cm
}




LENGTHS = [
    0.0,#"SpineBase",           
    0.179,#"SpineMid",            
    0.084, #"Neck",                
    0.084, #"Head",               
    0.110, #"ShoulderLeft",        
    0.332, #"ElbowLeft",           
    0.271, #"WristLeft",           
    0.07, #"HandLeft",            
    0.110, #"ShoulderRight",       
    0.332, #"ElbowRight",          
    0.271, #"WristRight",          
    0.070, #"HandRight",           
    0.142, #"HipLeft",             
    0.550, #"KneeLeft",            
    0.220, #"AnkleLeft",           
    0.130, #"FootLeft",           
    0.142, #"HipRight",            
    0.550, #"KneeRight",           
    0.220, #"AnkleRight",          
    0.130, #"FootRight",          
    0.337, #"SpineShoulder",       
    0.139, #"HandTipLeft",         
    0.070, #"ThumbLeft",          
    0.139, #"HandTipRight",       
    0.070, #"ThumbRight",        

]


