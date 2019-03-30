from pykinect2 import PyKinectV2
import pygame

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
    pygame.color.THECOLORS['red'], 
    pygame.color.THECOLORS['blue'], 
    pygame.color.THECOLORS['green'], 
    pygame.color.THECOLORS['orange'], 
    pygame.color.THECOLORS['purple'], 
    pygame.color.THECOLORS['yellow']
]

# List of all the available joints
JOINTS = [
    PyKinectV2.JointType_Head,          PyKinectV2.JointType_Neck, 
    PyKinectV2.JointType_SpineShoulder, PyKinectV2.JointType_SpineMid,      PyKinectV2.JointType_SpineBase, 
    PyKinectV2.JointType_ShoulderLeft,  PyKinectV2.JointType_ShoulderRight, 
    PyKinectV2.JointType_HipRight,      PyKinectV2.JointType_HipLeft,
    PyKinectV2.JointType_ElbowRight,    PyKinectV2.JointType_ElbowLeft, 
    PyKinectV2.JointType_WristLeft,     PyKinectV2.JointType_WristRight,
    PyKinectV2.JointType_HandLeft,      PyKinectV2.JointType_HandRight,
    PyKinectV2.JointType_ThumbLeft,     PyKinectV2.JointType_ThumbRight,
    PyKinectV2.JointType_AnkleLeft,     PyKinectV2.JointType_AnkleRight,
    PyKinectV2.JointType_HandTipLeft,   PyKinectV2.JointType_HandTipRight,
    PyKinectV2.JointType_KneeLeft,      PyKinectV2.JointType_KneeRight,
    PyKinectV2.JointType_FootLeft,      PyKinectV2.JointType_FootRight

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
