from constants import JOINTS, JOINTS_NAMES, JOINT_TREE, LENGTHS
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
    #TODO: ga de maximale pixelwaarde na die de Kinect kan detecteren. Zou normaal 1920 * 1080 moeten zijn
    #      -> Methode zoeken om de centimeters van de ideale verhoudingen om te zetten naar pixelwaarden, of omgekeerd
    def _scale(self, featureVector):        
        for parent_joint in JOINT_TREE.keys():
            parent_point = featureVector[(parent_joint*3):(parent_joint*3)+3]
            #print(f"{JOINTS_NAMES[parent_joint]} : {parent_point}")
            for child_joint in JOINT_TREE[parent_joint]:
                child_point = featureVector[(child_joint*3):(child_joint*3)+3]
                diff = [child - parent for (child, parent) in zip(child_point, parent_point)]
                norm = sqrt(diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2])
                featureVector[(child_joint * 3) + 0] = (LENGTHS[child_joint] * diff[0]/norm) + parent_point[0]
                featureVector[(child_joint * 3) + 1] = (LENGTHS[child_joint] * diff[1]/norm) + parent_point[1]
                featureVector[(child_joint * 3) + 2] = (LENGTHS[child_joint] * diff[2]/norm) + parent_point[2]
        


    @classmethod
    #TODO: voor sommige joints is er een compleet foute z-waarde (diepte) geassocieerd.
    # Aangezien elk component met elk ander component vermenigvuldigd wordt (Hamilton product),
    #   zal dit een enorme invloed hebben op de geroteerde joints met een foute z-waarde.
    #   -> nieuwe opnames maken (MAANDAG 1 juli)
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
            coordinates = Quaternion(w=0, x=featureVector[i], y=featureVector[i + 1], z=0)
            quaternion = Quaternion(w=featureVector[78 + j], x=featureVector[75 + j], y=featureVector[76 + j], z=featureVector[77 + j])
            print(f"-- Joint: {JOINTS_NAMES[int(i / 3)]}")


            print(f"-- Coordinates: {coordinates}")
            print(f"-- Quaternion: {quaternion}")
            
            coordinates = qref * coordinates * conqref
            quaternion *= conqref
            print(f"-- New Coordinates: {coordinates}")
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
            