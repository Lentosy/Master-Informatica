from pykinect2 import PyKinectV2
import pygame

PERSONS = ['BERT', 'DEMING', 'NIELS'] 
ACTIONS = ['DEFAULT',                       #0
           'EMERGENCY_STOP',                #1
           'RH_NORMAL_STOP',                #2
           'LH_NORMAL_STOP',                #3
           'RH_MOVE_FORWARD',               #4
           'RH_MOVE_BACKWARD',              #5
           'RH_MOVE_RIGHT',                 #6
           'LH_MOVE_FORWARD',               #7
           'LH_MOVE_BACKWARD',              #8
           'LH_MOVE_LEFT',                  #9
           'RH_ROTATE_ABOUT_AXIS',          #10
           'LH_ROTATE_ABOUT_AXIS',          #11
           'DEBUG']                         #0

DEBUG_FPS = 2
DEFAULT_FPS = 30

SKELETON_LINE_THICKNESS = 28
SKELETON_CIRCLE_RADIUS = 25

SKELETON_COLORS = [
    (255, 0, 0), # red
    (0, 255, 0), # green
    (0, 0, 255), # blue
    (255, 100, 10), # orange
    (240, 0, 255), # purple
    (255, 255, 0) # yellow
]

# List of all the available joints (same order as the PyKinectv2.JointType enumeration)
JOINTS = [
    PyKinectV2.JointType_SpineBase,           # 0 quaternion exists - parent is neck
    PyKinectV2.JointType_SpineMid,            # 1 quaternion exists - parent is neck
    PyKinectV2.JointType_Neck,                # 2 quaternion exists - parent is head
    PyKinectV2.JointType_Head,                # 3
    PyKinectV2.JointType_ShoulderLeft,        # 4 quaternion exists - parent is neck
    PyKinectV2.JointType_ElbowLeft,           # 5 quaternion exists
    PyKinectV2.JointType_WristLeft,           # 6 quaternion exists
    PyKinectV2.JointType_HandLeft,            # 7 quaternion exists
    PyKinectV2.JointType_ShoulderRight,       # 8 quaternion exists
    PyKinectV2.JointType_ElbowRight,          # 9 quaternion exists
    PyKinectV2.JointType_WristRight,          # 10 quaternion exists
    PyKinectV2.JointType_HandRight,           # 11 quaternion exists
    PyKinectV2.JointType_HipLeft,             # 12 quaternion exists
    PyKinectV2.JointType_KneeLeft,            # 13 quaternion exists
    PyKinectV2.JointType_AnkleLeft,           # 14 quaternion exists
    PyKinectV2.JointType_FootLeft,            # 15
    PyKinectV2.JointType_HipRight,            # 16 quaternion exists
    PyKinectV2.JointType_KneeRight,           # 17 quaternion exists
    PyKinectV2.JointType_AnkleRight,          # 18 quaternion exists
    PyKinectV2.JointType_FootRight,           # 19
    PyKinectV2.JointType_SpineShoulder,       # 20 quaternion exists
    PyKinectV2.JointType_HandTipLeft,         # 21
    PyKinectV2.JointType_ThumbLeft,           # 22
    PyKinectV2.JointType_HandTipRight,        # 23
    PyKinectV2.JointType_ThumbRight,          # 24
]
JOINTS_NAMES = [
    "SpineBase",           # 0 quaternion exists - parent is neck
    "SpineMid",            # 1 quaternion exists - parent is neck
    "Neck",                # 2 quaternion exists - parent is head
    "Head",                # 3
    "ShoulderLeft",        # 4 quaternion exists - parent is neck
    "ElbowLeft",           # 5 quaternion exists
    "WristLeft",           # 6 quaternion exists
    "HandLeft",            # 7 quaternion exists
    "ShoulderRight",       # 8 quaternion exists
    "ElbowRight",          # 9 quaternion exists
    "WristRight",          # 10 quaternion exists
    "HandRight",           # 11 quaternion exists
    "HipLeft",             # 12 quaternion exists
    "KneeLeft",            # 13 quaternion exists
    "AnkleLeft",           # 14 quaternion exists
    "FootLeft",            # 15
    "HipRight",            # 16 quaternion exists
    "KneeRight",           # 17 quaternion exists
    "AnkleRight",          # 18 quaternion exists
    "FootRight",           # 19
    "SpineShoulder",       # 20 quaternion exists
    "HandTipLeft",         # 21
    "ThumbLeft",           # 22
    "HandTipRight",        # 23
    "ThumbRight",          # 24

]

# List of all the connections between two joints
CONNECTIONS = [
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
