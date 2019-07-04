import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import csv
import numpy as np
import matplotlib
import matplotlib.projections as proj
import matplotlib.pyplot as plot
import sys
import mpl_toolkits.mplot3d
from copy import deepcopy
from transform_features import FeatureTransformer
from pykinect2 import PyKinectV2
from domain.constants import JOINTS, JOINT_CONNECTIONS
import dataset


def main():
    try:
        projection = sys.argv[1]
    except IndexError:
        print(proj.get_projection_names())
        exit(1)

    rawData = getData()
    graphData = getGraphData(rawData)
    plotData(graphData, projection)
    return 0

def connectpoints_xy(p1, p2):
    x1, x2 = p1[0], p2[0]
    y1, y2 = p1[1], p2[1]
    plot.plot([x1, x2], [y1, y2], 'k-')

def connectpoints_yz(p1, p2):
    y1, y2 = p1[1], p2[1]
    z1, z2 = p1[2], p2[2]
    plot.plot([y1, y2], [z1, z2], 'k-')

def connectpoints_xyz(p1, p2):
    x1, x2 = p1[0], p2[0]
    y1, y2 = p1[1], p2[1]
    z1, z2 = p1[2], p2[2]
    plot.plot([x1, x2], [y1, y2], [z1, z2], 'k-')

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
            xdata[(JOINTS[JOINT_CONNECTIONS[i][0]])],
            ydata[(JOINTS[JOINT_CONNECTIONS[i][0]])],
            zdata[(JOINTS[JOINT_CONNECTIONS[i][0]])],
        ]
        p2 = [
            xdata[(JOINTS[JOINT_CONNECTIONS[i][1]])],
            ydata[(JOINTS[JOINT_CONNECTIONS[i][1]])],
            zdata[(JOINTS[JOINT_CONNECTIONS[i][1]])],
        ]
        fun(p1, p2)


def plotData(graphData, projection):
    fig = plot.figure()
    size = 20
    domain = [-1, 1]
    ticks = [-1, -0.5, 0, 0.5, 1]

    rows = 2 # change this when scaling works

    if projection == 'rectilinear':
        for i in range(0, rows):
            xdata, ydata, zdata = ([], [], [])
            for k in range(0, 25):
                    xdata.append(graphData[i][k].point.x)
                    ydata.append(graphData[i][k].point.y)
                    zdata.append(graphData[i][k].point.z)

            ax = fig.add_subplot(rows, 2, (2*i) + 1, projection=projection)
            ax.scatter(xdata, ydata, [size for x in xdata],
                    label="skelet joints")


            connectjoints(xdata, ydata, zdata ,'xy')
            



            ax.set_xlabel("X")
            ax.set_ylabel("Y", rotation=0, labelpad=20)
            ax.set_xticks(ticks)
            ax.set_xlim(domain)
            ax.set_ylim(domain)


            ax = fig.add_subplot(rows, 2, 2*i + 2, projection=projection)
            ax.scatter(ydata, zdata, [size for x in xdata],
                    label="skelet joints")


            connectjoints(xdata, ydata, zdata ,'yz')
            ax.set_xlabel("Y")
            ax.set_ylabel("Z", rotation=0, labelpad=20)
            ax.set_xticks(ticks)
            ax.set_xlim(domain)
            ax.set_ylim(domain)

    if projection == '3d':
        for i in range(0, rows):
            xdata, ydata, zdata = ([], [], [])
            for k in range(0, 25):
                    xdata.append(graphData[i][k].point.x)
                    ydata.append(graphData[i][k].point.y)
                    zdata.append(graphData[i][k].point.z)

            ax = fig.add_subplot(rows, 1, i + 1, projection=projection)
            ax.scatter(xdata, ydata, zdata,
                    label="skelet joints")

            connectjoints(xdata, ydata, zdata ,'xyz')
            ax.set_xticks(ticks)
            ax.set_yticks(ticks)
            ax.set_zticks(ticks)
            ax.set_xlabel("X")
            ax.set_ylabel("Y", rotation=0, labelpad=20)
            ax.set_zlabel("Z", rotation=0, labelpad=20)
            ax.set_xlim(domain)
            ax.set_ylim(domain)
            ax.view_init(130, -90)


    fig.legend(labels=('Skelet joints', 'Heup joint', 'Hoofd joint'), loc='upper left')
    fig.title = "Preprocessingfase"
    fig.set_figheight(10)
    fig.set_figwidth(10)



    plot.show()





def getData():
    return dataset.Dataset(['DEBUG']).data

def getGraphData(rawData):
    graphData = [[],[],[]]
    ft = FeatureTransformer(rawData)
    # translat
    for featureVector in ft.featureVectors:
        ft._translate(featureVector)
    processed = deepcopy(ft.featureVectors)

    for j in range(0, 25):
        graphData[0].append(processed[0][j])

    # rotate
    for featureVector in ft.featureVectors:
        ft._rotate(featureVector)
    processed = deepcopy(ft.featureVectors)
    for j in range(0, 25):
        graphData[1].append(processed[0][j])

    # scale
    for featureVector in ft.featureVectors:
        ft._scale(featureVector)
    processed = deepcopy(ft.featureVectors)
    for j in range(0, 25):
        graphData[2].append(processed[0][j])

    return graphData

if __name__ == "__main__":
    main()













