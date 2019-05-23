from constants import JOINTS
from pykinect2 import PyKinectV2
from math import sqrt, acos, pi, cos, sin
import numpy
import time

class FeatureTransformer(object):
    @classmethod
    def __init__(self, rawData):
        self.featureVectors = rawData

    @classmethod
    def preProcessing(self):
        if __debug__:
            start = time.time()
        for i in range(0, len(self.featureVectors)):
            self._translateToOrigin(self.featureVectors[i])
            self._scale(self.featureVectors[i])
            self._toLocalSkeletonCoördinateSystem(self.featureVectors[i])
            self.featureVectors[i] = self.featureVectors[i][:175 - 24] # 6 useless quaternions at the end of the list: 6 * 4 : 24
        if __debug__:
            end = time.time()
            print(f"Preprocessing: {end - start} seconds")
        return self.featureVectors

    @classmethod
    def _translateToOrigin(self, featureVector):
        """
        This processing step translates the whole skeleton so that the spine base becomes the origin in the camera coördinate system.
        """
        # The lower spine is used as the origin
        spine_x = featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + 0]
        spine_y = featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + 1]
        spine_z = featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + 2]
        for i in range(0, 75, 3):
            featureVector[i+0] = featureVector[i+0] - spine_x
            featureVector[i+1] = featureVector[i+1] - spine_y
            featureVector[i+2] = featureVector[i+2] - spine_z

    @classmethod
    def _scale(self, featureVector):
        """
        This processing step makes the feature vector scale invariant by dividing each position vector with the length of the Neck position vector.
        """
        neck_x = featureVector[JOINTS[PyKinectV2.JointType_Neck] + 0]
        neck_y = featureVector[JOINTS[PyKinectV2.JointType_Neck] + 1]
        neck_z = featureVector[JOINTS[PyKinectV2.JointType_Neck] + 2]
        length = sqrt(neck_x * neck_x + neck_y * neck_y + neck_z * neck_z)
        for i in range(0, 75, 3):
            featureVector[i+0] = featureVector[i+0] / length
            featureVector[i+1] = featureVector[i+1] / length
            featureVector[i+2] = featureVector[i+2] / length


    @classmethod
    def _toLocalSkeletonCoördinateSystem(self, featureVector):
        pass
    ##    """
    ##    This step transforms the camera coördinate system to a local skeleton coördinate system. 
    ##    The origin is the Spine Base Joint and the Y-axis is defined as the vector trough the Spine Base Joint and Spine Mid Joint.
    ##    The X-axis is orthogonal to the Y-Axis and the Z-axis is orthogonal to the XY-plane.
    ##    """
    ##    spine_x = featureVector[JOINTS[PyKinectV2.JointType_SpineMid]*3 + 0]
    ##    spine_y = featureVector[JOINTS[PyKinectV2.JointType_SpineMid]*3 + 1]
    ##    spine_z = featureVector[JOINTS[PyKinectV2.JointType_SpineMid]*3 + 2]
##
    ##    magnitude = sqrt(spine_x*spine_x + spine_y*spine_y + spine_z*spine_z)
    ##    # angle between two vectors = acos(x . y / ||x|| . ||y||). In this case, y is the unit vector in the y-direction
    ##    # x . y = 0 + 1 * spine_y
    ##    # ||x|| . ||y|| = magnitude . 1
    ##    theta = acos(spine_y / magnitude) 
    ##    if(spine_x <= 0): # if the joint is in the second quadrant, the rotation should happen clockwise (negative theta), otherwise counterclockwise
    ##        theta = -theta
    ##    for i in range(0, 75, 3):
    ##        x = featureVector[i]
    ##        y = featureVector[i+1]
    ##        # implied rotation matrix
    ##        featureVector[i + 0] = x*cos(theta) - y*sin(theta) # x' = x*cos(theta) - y*sin(theta)
    ##        featureVector[i + 1] = x*sin(theta) + y*cos(theta) # y' = x*sin(theta) + y*cos(theta)
