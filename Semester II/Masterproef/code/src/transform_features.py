import pandas as pd
from pykinect2 import PyKinectV2
from pykinect2.PyKinectV2 import *

PATH = "data\\BERT\\EMERGENCY_STOP\\joints.txt"
joints = pd.read_csv(PATH, header = None, sep = ';')

spine_info = joints[joints.columns[PyKinectV2.JointType_SpineBase:PyKinectV2.JointType_SpineBase + 3]]
other_joints = joints[joints.columns[PyKinectV2.JointType_SpineMid * 3:PyKinectV2.JointType_ThumbRight * 3 + 3]]
all_joints = joints[joints.columns[PyKinectV2.JointType_SpineBase : PyKinectV2.JointType_ThumbRight * 3 + 3]]

all_joints[:, 3] = all_joints[:, 3] - all_joints[:, 0]
print(all_joints.head())