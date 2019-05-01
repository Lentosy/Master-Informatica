from constants import JOINTS
from pykinect2 import PyKinectV2
from math import sqrt, acos, pi, cos, sin
import numpy

class FeatureTransformer(object):
    @classmethod
    def __init__(self, rawData):
        self.featureVectors = rawData

    @classmethod
    def preProcessing(self):
        for featureVector in self.featureVectors:
            self._translateToOrigin(featureVector)
            self._scale(featureVector)
            self._toLocalSkeletonCoördinateSystem(featureVector)
            for i in range(75, len(featureVector)):
                featureVector[i] = float(featureVector[i])
        return self.featureVectors

    @classmethod
    def _translateToOrigin(self, featureVector):
        """
        This processing step translates the whole skeleton so that the spine base becomes the origin in the camera coördinate system.
        """
        # The lower spine is used as the origin
        spine_x = float(featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + 0])
        spine_y = float(featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + 1])
        spine_z = float(featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + 2])
        for i in range(0, 75, 3):
            featureVector[i+0] = float(featureVector[i+0]) - spine_x
            featureVector[i+1] = float(featureVector[i+1]) - spine_y
            featureVector[i+2] = float(featureVector[i+2]) - spine_z

    @classmethod
    def _scale(self, featureVector):
        """
        This processing step makes the feature vector scale invariant by dividing each position vector with the length of the Neck position vector.
        """
        neck_x = float(featureVector[JOINTS[PyKinectV2.JointType_Neck] + 0])
        neck_y = float(featureVector[JOINTS[PyKinectV2.JointType_Neck] + 1])
        neck_z = float(featureVector[JOINTS[PyKinectV2.JointType_Neck] + 2])
        length = sqrt(neck_x * neck_x + neck_y * neck_y + neck_z * neck_z)
        for i in range(0, 75, 3):
            featureVector[i+0] = float(featureVector[i+0]) / length
            featureVector[i+1] = float(featureVector[i+1]) / length
            featureVector[i+2] = float(featureVector[i+2]) / length

        
    @classmethod
    def _toLocalSkeletonCoördinateSystem(self, featureVector):
        xAngle = acos(featureVector[PyKinectV2.JointType_HipLeft] + featureVector[PyKinectV2.JointType_HipLeft + 1] + featureVector[PyKinectV2.JointType_HipLeft + 2])
        rotationX = numpy.matrix([[1, 0, 0], [0, cos(xAngle), -sin(xAngle)], [0, sin(xAngle), cos(xAngle)]])
        
        for i in range(0, 75, 3):
            coördinateVector = (featureVector[i], featureVector[i+1], featureVector[i+2])
            result = (rotationX @ coördinateVector).getA1()
            featureVector[i], featureVector[i+1], featureVector[i+2] = result


    
