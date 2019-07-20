import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.projections as proj

import numpy as np
from numpy import linspace
from numpy.fft import fft

from GraphManager import GraphManager
from math import sqrt
from dataset import Dataset
from domain.constants import JOINTS
from transform_features import FeatureTransformer

def main():
    dataset = Dataset(['BERT']) 
    ft = FeatureTransformer(dataset.data)
    ft.preProcessing()
    
    gm = GraphManager(1, 1)
    potentials = getPotentialPerJoint(dataset)
    plotPotentialsPerJoint(potentials, gm.getNextAx())
    gm.adjustSubplots(left=0.05, bottom=0.06,right=0.99,top=0.95,wspace=0.30,hspace=0.51)
    gm.show(fullscreen=True, tightLayout = True)

def plotPotentialsPerJoint(potentials, ax):
    maxP = max([max(potentials[i]) for i in range(0, len(potentials))])
    ax.set(
            ylim = (0, maxP)
        )
    colormap = plt.get_cmap('Set1')

    color_index = 0
    for i in range(0, len(JOINTS)):
        if JOINTS[i]['weight'] != 0:
            data = potentials[i]
            ax.plot(data, label=JOINTS[i]['name'], color= colormap(color_index))
            color_index += 0.1

    ax.legend(loc='upper left')


def getPotentialPerJoint(dataset):
    potentials = [[0 for i in range(0, len(dataset))] for j in range(0, len(JOINTS))]
 
    for i in range(1, len(dataset.data)):
        for joint_index in range(0, len(JOINTS)):
            #calculate velocity components
            velX = dataset.data[i - 1][joint_index].point.x - dataset.data[i][joint_index].point.x
            velY = dataset.data[i - 1][joint_index].point.y - dataset.data[i][joint_index].point.y 
            velZ = dataset.data[i - 1][joint_index].point.z - dataset.data[i][joint_index].point.z 
            #magnitude of velocity
            velocity = sqrt(velX * velX + velY * velY + velZ * velZ)
            potential = 0.5 * JOINTS[joint_index]['weight'] * velocity * velocity # E = mv^2
            potentials[joint_index][i] = potential
    return potentials

if __name__ == '__main__':
    main()