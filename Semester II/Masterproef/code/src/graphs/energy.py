import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.projections as proj

from GraphManager import GraphManager
import numpy as np
from scipy.fftpack import fft
from math import sqrt
from dataset import Dataset
from domain.constants import JOINTS
from transform_features import FeatureTransformer

def main():
    dataset = Dataset(['BERT'])
    ft = FeatureTransformer(dataset.data)
    ft.preProcessing()


    energies = getEnergies(dataset)
    gm = GraphManager(1, 2)
    
    plotEnergy(energies, gm.getNextAx())
    plotFFT(energies, gm.getNextAx())

    gm.show(fullscreen=True)


def getEnergies(dataset):
    y = []
    for i in range(1, len(dataset.data)):
        totalKineticEnergy = 0
        for joint_index in range(0, len(JOINTS)):
            #calculate velocity components
            velX = dataset.data[i - 1][joint_index].point.x - dataset.data[i][joint_index].point.x
            velY = dataset.data[i - 1][joint_index].point.y - dataset.data[i][joint_index].point.y 
            velZ = dataset.data[i - 1][joint_index].point.z - dataset.data[i][joint_index].point.z 
            #magnitude of velocity
            velocity = sqrt(velX * velX + velY * velY + velZ * velZ)
            totalKineticEnergy += JOINTS[joint_index]['weight'] * velocity * velocity # E = mv^2

        y.append(totalKineticEnergy)
    return y

def plotFFT(energies, ax):
    samplingRate = 30
    startTime = 0
    endTime = len(energies)/samplingRate
    time = np.linspace(startTime, endTime, len(energies))

    T = 1/samplingRate
    x = np.linspace(0, 1/2*T, len(energies))
    yr = fft(energies)
    y = 2/len(energies) * np.abs(yr)
    ax.plot(x, y)
    

def plotEnergy(energies, ax, visualizeSegmentation = False, targets=None):
    ax.plot(energies)
    ax.set( xlabel='Frame (ΔT = 1/30)',
            ylabel='Potentiaal')

    if visualizeSegmentation:
        if targets == None:
            raise ValueError("When visualizing the segmentation, the ground truth must also be provided in the 'targets' parameter")
        actionStarted = False
        gtActionStarted = False
        maxE = max(energies)
        threshold = 0.05
        for i in range(0, len(energies)):
            energy = energies[i]
            target = targets[i]

            if gtActionStarted == False and target != 0:
                gtActionStarted = True
                ax.plot((i, i), (0, maxE), linestyle='-', color="green")
            if gtActionStarted == True and target == 0:
                gtActionStarted = False
                ax.plot((i, i), (0, maxE), linestyle='-', color="red")

            if actionStarted == False and energy >= threshold:
                actionStarted = True
                ax.plot((i, i), (0, maxE), linestyle=':', color="green")
            if actionStarted == True and energy < threshold:
                actionStarted = False
                ax.plot((i, i), (0, maxE), linestyle=':', color="red")          



if __name__ == '__main__':
    main()