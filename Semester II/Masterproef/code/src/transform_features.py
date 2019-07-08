import numpy
import time
import copy

from domain.constants import JOINTS, JOINTS_NAMES, JOINT_TREE, LENGTHS
from pykinect2 import PyKinectV2
from math import sqrt, acos, pi, cos, sin
from pyquaternion import Quaternion
from sklearn.feature_selection import VarianceThreshold

class FeatureTransformer(object):
    @classmethod
    def __init__(self, rawData = None):
        self.featureVectors = rawData

        
    @classmethod
    def setFeatureVectors(self, rawData):
        self.featureVectors = rawData

    @classmethod
    def preProcessing(self):
        if __debug__:
            start = time.time()
        for i in range(0, len(self.featureVectors)):
            self._translate(self.featureVectors[i])
            self._rotate(self.featureVectors[i])
           # self._scale(self.featureVectors[i])
        if __debug__:
            end = time.time()
            print(f"Preprocessing: {end - start} seconds")
        return self.featureVectors




    @classmethod
    def _varianceThreshold(self, threshold):
        sel = VarianceThreshold(threshold=threshold) 
        sel.fit_transform(self.featureVectors)
        
    @classmethod
    def _removeLowerBody(self, featureVector):
        jointsToRemove = [19, 18, 15, 14]
        
        for index in jointsToRemove:
            del featureVector[index]
                
        

    @classmethod
    def _translate(self, featureVector):
        """
        This processing step translates the whole skeleton so that the spine base becomes the origin in the camera coördinate system.
        """
        # The lower spine is used as the origin
        spine = copy.deepcopy(featureVector[JOINTS[PyKinectV2.JointType_SpineBase]])
        for i in range(0, len(featureVector)):
            featureVector[i].point = featureVector[i].point - spine.point

    @classmethod
    def _scale(self, featureVector):        
        #for parent_joint in JOINT_TREE.keys():
        #    parent = featureVector[parent_joint]
        #    for child_joint in JOINT_TREE[parent_joint]:
        #        child = featureVector[child_joint]
        #        diff = child.point - parent.point
        #        norm = diff.norm()
#
        #        child.point = (LENGTHS[child_joint] * diff / norm) + parent.point
        pass
        


    @classmethod
    #TODO: voor sommige joints is er een compleet foute z-waarde (diepte) geassocieerd.
    # Aangezien elk component met elk ander component vermenigvuldigd wordt (Hamilton product),
    #   zal dit een enorme invloed hebben op de geroteerde joints met een foute z-waarde.
    #   -> nieuwe opnames maken (MAANDAG 1 juli)
    #   -> VOORLOPIG: diepte negeren (krijgt waarde 0)
    def _rotate(self, featureVector):

        ref = copy.deepcopy(featureVector[PyKinectV2.JointType_SpineBase])
        conjugate = ref.quaternion.conjugate

        for i in range(0, len(featureVector)):
            joint = featureVector[i]
            joint.point = (ref.quaternion * joint.point.to_quaternion() * conjugate).to_point()
            joint.quaternion *= conjugate
