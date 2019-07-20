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
    
#    dataset.data = dataset.data[510:565]
#    dataset.target = dataset.target[510:565]

    gm = GraphManager(1, 1)
    energies = getEnergies(dataset)
    
    plotEnergy(energies, gm.getNextAx(), True)
#    plotFFT(energies, gm.getNextAx())

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
    # Number of samplepoints
    N = len(energies)
    # sample spacing
    T = 1.0 / 30.0
    
    mean = sum(energies)/len(energies)
    # remove DC bias by subtracting the mean of the values from every other value
    y = [e - mean for e in energies]
    yf = fft(y)
    xf = linspace(0.0, 1.0/(2.0*T), N/2)  

    ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))
    ax.set( xlabel='Frequency (Hz)',
            ylabel='Potential')


def plotEnergy(energies, ax, visualizeSegmentation = False, targets = None):
    ax.plot(energies)
    ax.set( xlabel='Frame (ΔT = 1/30)',
            ylabel='Potential')

    if visualizeSegmentation:
        actionStarted = False
        gtActionStarted = False
        maxE = max(energies)
        threshold = 0.05
        for i in range(0, len(energies)):
            energy = energies[i]
            if targets is not None:
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