from constants import JOINTS, JOINTS_NAMES
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
            self._translate(self.featureVectors[i])
            self._rotate(self.featureVectors[i])
            self._scale(self.featureVectors[i])
        if __debug__:
            end = time.time()
            print(f"Preprocessing: {end - start} seconds")
        return self.featureVectors

    @classmethod
    def _translate(self, featureVector):
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
    #TODO: voor sommige joints is er een compleet foute z-waarde (diepte) geassocieerd.
    # Aangezien elk component met elk ander component vermenigvuldigd wordt (Hamilton product),
    #   zal dit een enorme invloed hebben op de geroteerde joints met een foute z-waarde.
    #   -> nieuwe opnames maken 
    #   -> VOORLOPIG: diepte negeren (krijgt waarde 0)
    def _rotate(self, featureVector):
        qref = Quaternion( # the spine base joint quaternion
            featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + (3 * 25) + 3],  #the constant is always the last one 
            featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + (3 * 25) + 0],  
            featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + (3 * 25) + 1], 
            featureVector[JOINTS[PyKinectV2.JointType_SpineBase] + (3 * 25) + 2]
        )
        conqref = qref.conjugate # the conjugate of the spine base joint quaternion
        print(f"Reference Quaternion: {qref}")
        print(f"Conjugate:{conqref}")
        j = 0
        for i in range(0, 75, 3):
            coordinates = Quaternion(w=0, x=featureVector[i], y=featureVector[i + 1], z=featureVector[i + 2])
            quaternion = Quaternion(w=featureVector[78 + j], x=featureVector[75 + j], y=featureVector[76 + j], z=featureVector[77 + j])
            print(f"-- Joint: {JOINTS_NAMES[int(i / 3)]}")

            coordinates = qref * coordinates * conqref
            quaternion *= conqref

            print(f"-- Coordinates: {coordinates}")
            print(f"-- New Coordinates: {coordinates}")

            print(f"-- Quaternion: {quaternion}")
            print(f"-- New Quaternion: {quaternion}")
            featureVector[i]      = coordinates[1]
            featureVector[i + 1]  = coordinates[2]
            featureVector[i + 2]  = coordinates[3]

            featureVector[78 + j] = quaternion[0]
            featureVector[75 + j] = quaternion[1]
            featureVector[76 + j] = quaternion[2]
            featureVector[77 + j] = quaternion[3]
            

            j+=4
            print()
            