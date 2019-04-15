#from pykinect2 import PyKinectV2
#import pygame

PERSONS = ['BERT', 'DEMING', 'NIELS'] 
ACTIONS = ['DEFAULT',               'EMERGENCY_STOP',       
           'RH_NORMAL_STOP',        'LH_NORMAL_STOP',
           'RH_MOVE_FORWARD',       'RH_MOVE_BACKWARD',     'RH_MOVE_RIGHT',
           'LH_MOVE_FORWARD',       'LH_MOVE_BACKWARD',     'LH_MOVE_LEFT',
           'RH_ROTATE_ABOUT_AXIS',  'LH_ROTATE_ABOUT_AXIS',
           'DEBUG']

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
#
## List of all the available joints (same order as the PyKinectv2.JointType enumeration)
#JOINTS = [
#    PyKinectV2.JointType_SpineBase,           # 0
#    PyKinectV2.JointType_SpineMid,            # 1
#    PyKinectV2.JointType_Neck,                # 2
#    PyKinectV2.JointType_Head,                # 3
#    PyKinectV2.JointType_ShoulderLeft,        # 4
#    PyKinectV2.JointType_ElbowLeft,           # 5
#    PyKinectV2.JointType_WristLeft,           # 6
#    PyKinectV2.JointType_HandLeft,            # 7
#    PyKinectV2.JointType_ShoulderRight,       # 8
#    PyKinectV2.JointType_ElbowRight,          # 9
#    PyKinectV2.JointType_WristRight,          # 10
#    PyKinectV2.JointType_HandRight,           # 11
#    PyKinectV2.JointType_HipLeft,             # 12
#    PyKinectV2.JointType_KneeLeft,            # 13
#    PyKinectV2.JointType_AnkleLeft,           # 14
#    PyKinectV2.JointType_FootLeft,            # 15
#    PyKinectV2.JointType_HipRight,            # 16
#    PyKinectV2.JointType_KneeRight,           # 17
#    PyKinectV2.JointType_AnkleRight,          # 18
#    PyKinectV2.JointType_FootRight,           # 19
#    PyKinectV2.JointType_SpineShoulder,       # 20
#    PyKinectV2.JointType_HandTipLeft,         # 21
#    PyKinectV2.JointType_ThumbLeft,           # 22
#    PyKinectV2.JointType_HandTipRight,        # 23
#    PyKinectV2.JointType_ThumbRight,          # 24
#
#]
#
## List of all the connections between two joints
#CONNECTIONS = [
#    # Torso
#    [PyKinectV2.JointType_Head,             PyKinectV2.JointType_Neck],
#    [PyKinectV2.JointType_Neck,             PyKinectV2.JointType_SpineShoulder],
#    [PyKinectV2.JointType_SpineShoulder,    PyKinectV2.JointType_SpineMid],
#    [PyKinectV2.JointType_SpineMid,         PyKinectV2.JointType_SpineBase],
#    [PyKinectV2.JointType_SpineShoulder,    PyKinectV2.JointType_ShoulderRight],
#    [PyKinectV2.JointType_SpineShoulder,    PyKinectV2.JointType_ShoulderLeft],
#    [PyKinectV2.JointType_SpineBase,        PyKinectV2.JointType_HipRight],
#    [PyKinectV2.JointType_SpineBase,        PyKinectV2.JointType_HipLeft],
#    # Right arm
#    [PyKinectV2.JointType_ShoulderRight,    PyKinectV2.JointType_ElbowRight],
#    [PyKinectV2.JointType_ElbowRight,       PyKinectV2.JointType_WristRight],
#    [PyKinectV2.JointType_WristRight,       PyKinectV2.JointType_HandRight],
#    [PyKinectV2.JointType_HandRight,        PyKinectV2.JointType_HandTipRight],
#    [PyKinectV2.JointType_WristRight,       PyKinectV2.JointType_ThumbRight],
#    # Left arm
#    [PyKinectV2.JointType_ShoulderLeft,     PyKinectV2.JointType_ElbowLeft],
#    [PyKinectV2.JointType_ElbowLeft,        PyKinectV2.JointType_WristLeft],
#    [PyKinectV2.JointType_WristLeft,        PyKinectV2.JointType_HandLeft],
#    [PyKinectV2.JointType_HandLeft,         PyKinectV2.JointType_HandTipLeft],
#    [PyKinectV2.JointType_WristLeft,        PyKinectV2.JointType_ThumbLeft],
#    # Right leg
#    [PyKinectV2.JointType_HipRight,         PyKinectV2.JointType_KneeRight],
#    [PyKinectV2.JointType_KneeRight,        PyKinectV2.JointType_AnkleRight],
#    [PyKinectV2.JointType_AnkleRight,       PyKinectV2.JointType_FootRight],
#    # Left leg
#    [PyKinectV2.JointType_HipLeft,          PyKinectV2.JointType_KneeLeft],
#    [PyKinectV2.JointType_KneeLeft,         PyKinectV2.JointType_AnkleLeft],
#    [PyKinectV2.JointType_AnkleLeft,        PyKinectV2.JointType_FootLeft]
#]
#