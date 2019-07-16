import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.projections as proj

from scipy import interpolate

from math import sqrt

from dataset import Dataset
from domain.constants import JOINTS
from transform_features import FeatureTransformer

def main():
    dataset = Dataset(['BERT'])
    ft = FeatureTransformer(dataset.data)
    ft.preProcessing()
    plotEnergy(dataset)
    

def plotEnergy(dataset):
    data = []
    
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

        data.append(totalKineticEnergy)

    fig = plt.figure()
    fig.legend(labels=('epic'), loc='upper left')
    ax = fig.gca()
    ax.plot(data)

    ax.set( xlabel='frame',
            ylabel='kinetische energie')


    actionStarted = False
    gtActionStarted = False

    maxE = max(data)
    threshold = 0.05

    buffersize = 10

    for i in range(0, len(data)):
        energy = data[i]
        target = dataset.target[i]

        if gtActionStarted == False and target != 0:
            gtActionStarted = True
            plt.plot((i, i), (0, maxE), linestyle='-', color="green")
        if gtActionStarted == True and target == 0:
            gtActionStarted = False
            plt.plot((i, i), (0, maxE), linestyle='-', color="red")

        if actionStarted == False and energy >= threshold:
            actionStarted = True
            plt.plot((i, i), (0, maxE), linestyle=':', color="green")
        if actionStarted == True and energy < threshold:
            actionStarted = False
            plt.plot((i, i), (0, maxE), linestyle=':', color="red")          

    plt.show()

if __name__ == '__main__':
    main()