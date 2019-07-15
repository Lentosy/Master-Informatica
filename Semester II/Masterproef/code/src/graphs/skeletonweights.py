import numpy as np
import matplotlib
import matplotlib.projections as proj
import matplotlib.pyplot as plt

import mpl_toolkits.mplot3d
from copy import deepcopy
from pykinect2 import PyKinectV2

import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from domain.constants import JOINTS, JOINT_CONNECTIONS
from transform_features import FeatureTransformer
from dataset import Dataset


def main():


    rawData = getData()
    graphData = getGraphData(rawData)
    plotData(graphData)
    return 0

def connectpoints_xy(p1, p2):
    x1, x2 = p1[0], p2[0]
    y1, y2 = p1[1], p2[1]
    plt.plot([x1, x2], [y1, y2], 'k-')

def connectpoints_yz(p1, p2):
    y1, y2 = p1[1], p2[1]
    z1, z2 = p1[2], p2[2]
    plt.plot([y1, y2], [z1, z2], 'k-')

def connectpoints_xyz(p1, p2):
    x1, x2 = p1[0], p2[0]
    y1, y2 = p1[1], p2[1]
    z1, z2 = p1[2], p2[2]
    plt.plot([x1, x2], [y1, y2], [z1, z2], 'k-')

def connectjoints(xdata, ydata, zdata, plane):
    fun = None
    if plane == 'xy':
        fun = connectpoints_xy
    elif plane == 'yz':
        fun = connectpoints_yz
    else:
        fun = connectpoints_xyz
    for i in range(0, len(JOINT_CONNECTIONS)):
        p1 = [
            xdata[JOINT_CONNECTIONS[i][0]],
            ydata[JOINT_CONNECTIONS[i][0]],
            zdata[JOINT_CONNECTIONS[i][0]],
        ]
        p2 = [
            xdata[JOINT_CONNECTIONS[i][1]],
            ydata[JOINT_CONNECTIONS[i][1]],
            zdata[JOINT_CONNECTIONS[i][1]],
        ]
        fun(p1, p2)


def plotData(graphData):
    fig = plt.figure()
    size = 20
    domain = [-1, 1]
    ticks = [-1, -0.5, 0, 0.5, 1]

    
    xdata, ydata, zdata = ([], [], [])
    for k in range(0, len(graphData[0])):
            xdata.append(graphData[0][k].point.x)
            ydata.append(graphData[0][k].point.y)
            zdata.append(JOINTS[k]['weight'] * 50)
    ax = fig.add_subplot(1,1, 1, projection='rectilinear')
    ax.scatter(xdata, ydata, zdata,
            label="skelet joints")
    connectjoints(xdata, ydata, zdata ,'xy')
    ax.set_xlabel("X")
    ax.set_ylabel("Y", rotation=0, labelpad=20)
    ax.set_xticks(ticks)
    ax.set_xlim(domain)



    plt.show()





def getData():
    return Dataset.getDebugDataset()

def getGraphData(dataset):
    graphData = [[],[],[]]

    ft = FeatureTransformer(dataset.data)
    
    #for featureVector in ft.featureVectors:
    #    ft._removeLowerBody(featureVector)
    #processed = deepcopy(ft.featureVectors)

    # translate
    for featureVector in ft.featureVectors:
        ft._translate(featureVector)
    processed = deepcopy(ft.featureVectors)

    for j in range(0, len(processed[0])):
        graphData[0].append(processed[0][j])

    return graphData

if __name__ == "__main__":
    main()













