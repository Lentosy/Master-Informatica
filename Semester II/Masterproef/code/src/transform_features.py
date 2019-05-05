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
        for i in range(0, len(self.featureVectors)):
            self._translateToOrigin(self.featureVectors[i])
            self._scale(self.featureVectors[i])
            self._toLocalSkeletonCoördinateSystem(self.featureVectors[i])
          #  self._removeUselessQuaternions(self.featureVectors[i])

            self.featureVectors[i] = self.featureVectors[i][:175 - 100] # 24 because 6 joints without quaternions

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
    def _removeUselessQuaternions(self, featureVector):
        #jointsWithoutQuaternions = [3, 15, 21, 22, 23, 24]
        for i in range(75, len(featureVector)):
            featureVector[i] = float(featureVector[i])

        for i in range(75 + (3)*4, len(featureVector) - 4):
            featureVector[i] = featureVector[i + 4]

        for i in range(75 + (15)*4, len(featureVector) - 4):
            featureVector[i] = featureVector[i + 4]
            

    @classmethod
    def _toLocalSkeletonCoördinateSystem(self, featureVector):
        pass