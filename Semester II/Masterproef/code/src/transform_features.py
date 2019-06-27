from constants import JOINTS
from pykinect2 import PyKinectV2
from math import sqrt, acos, pi, cos, sin
import numpy
import time
from pyquaternion import Quaternion

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
            self._rotate(self.featureVectors[i])
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
    def _rotate(self, featureVector):
        qref = Quaternion(featureVector[75], featureVector[76], featureVector[77] ,featureVector[78])
        print(qref)
        conqref = qref.conjugate
        print(conqref)
        
        j = 0
        for i in range(0, 75, 3):
            coordinates = Quaternion(0, featureVector[i], featureVector[i + 1], featureVector[i + 2])
            quaternion = Quaternion(featureVector[75 + j], featureVector[76 + j], featureVector[77 + j], featureVector[78 + j])
            

            coordinatesRot = coordinates * qref
            quaternionRot = quaternion * qref

            featureVector[i]      = coordinatesRot[1]
            featureVector[i + 1]  = coordinatesRot[2]
            featureVector[i + 2]  = coordinatesRot[3]

            featureVector[75 + j] = quaternionRot[0]
            featureVector[76 + j] = quaternionRot[1]
            featureVector[77 + j] = quaternionRot[2]
            featureVector[78 + j] = quaternionRot[3]

            j+=4
            