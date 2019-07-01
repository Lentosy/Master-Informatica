import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import csv
import numpy as np
import matplotlib.projections as proj
import matplotlib.pyplot as plot
import sys
from mpl_toolkits.mplot3d import Axes3D
from transform_features import FeatureTransformer
from pykinect2 import PyKinectV2
from constants import JOINTS

print(proj.get_projection_names() )
# 3d, aitoff, hammer, lambert, mollweide, polar, rectilinear
try:
    projection = sys.argv[1]
except IndexError:
    print('oops')
    exit(1)

frames = 2
rawData = []
with open(f"..\\data\\DEBUG\\joints.txt") as dataFile:
    csvReader = csv.reader(dataFile, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
    for row in csvReader:
        rawData.append(row)


graphData = [[[],[]], [[],[]], [[],[]], [[],[]]]
ranges = [[-400, 400], [-400, 400], [-400, 400], [-2, 2]]
for i in range(0, frames):
    for j in range(0, 75, 3):
        graphData[0][i].append(-float(rawData[i][j])) # negative so skeleton is standing upright
        graphData[0][i].append(-float(rawData[i][j+1]))
        graphData[0][i].append(float(rawData[i][j+2]))


ft = FeatureTransformer(rawData)

for featureVector in ft.featureVectors:
    ft._translate(featureVector)
processed = ft.featureVectors

for i in range(0, frames):
    for j in range(0, 75, 3):
        graphData[1][i].append(-processed[i][j]) 
        graphData[1][i].append(-processed[i][j+1])
        graphData[1][i].append(processed[i][j+2])

for featureVector in ft.featureVectors:
    ft._rotate(featureVector)
processed = ft.featureVectors
for i in range(0, frames):
    for j in range(0, 75, 3):
        graphData[2][i].append(-processed[i][j]) 
        graphData[2][i].append(-processed[i][j+1])
        graphData[2][i].append(processed[i][j+2])

for featureVector in ft.featureVectors:
    ft._scale(featureVector)
processed = ft.featureVectors
for i in range(0, frames):
    for j in range(0, 75, 3):
        graphData[3][i].append(-processed[i][j]) 
        graphData[3][i].append(-processed[i][j+1])
        graphData[3][i].append(processed[i][j+2])



fig = plot.figure()

plot_num = 1
for i in range(0, 4):
    for j in range(0, frames):
       # ax = Axes3D(fig)
        ax = fig.add_subplot(4, 2, plot_num, projection=projection)
        plot_num += 1
        xdata, ydata, zdata = ([], [], [])
        for k in range(0, 75, 3):
            xdata.append(graphData[i][j][k])
            ydata.append(graphData[i][j][k+1])
            if(projection == '3d'):
                zdata.append(graphData[i][j][k+2])
            else:
                zdata.append(10) # when projecting onto 2d, zdata must be a constant value for each entry
        ax.scatter(xdata, ydata, zdata,
                label="skelet joints")
        ax.scatter(
                [xdata[(JOINTS[PyKinectV2.JointType_SpineBase] * 3) + 0]],
                [ydata[(JOINTS[PyKinectV2.JointType_SpineBase] * 3) + 1]],
                [zdata[(JOINTS[PyKinectV2.JointType_SpineBase] * 3) + 2]], 
                label="heup joint")
        ax.scatter(
                [xdata[(JOINTS[PyKinectV2.JointType_Head] * 3) + 0]],
                [ydata[(JOINTS[PyKinectV2.JointType_Head] * 3) + 1]],
                [zdata[(JOINTS[PyKinectV2.JointType_Head] * 3) + 2]],
                 label="head joint")
        ax.set_xlabel("X")
        ax.set_ylabel("Y", rotation=0, labelpad=20)
        #ax.set_zlabel("Z", rotation=0, labelpad=20)
        #ax.view_init(elev=100., azim=180)





fig.tight_layout(pad=0.0, w_pad=0, h_pad=0)

fig.legend(labels=('Skelet joints', 'Heup joint'), loc='upper left')
fig.title = "Preprocessingfase"
fig.set_figheight(10)
fig.set_figwidth(10)

plot.show()
