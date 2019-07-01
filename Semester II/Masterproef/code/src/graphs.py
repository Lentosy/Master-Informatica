import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import csv
import numpy as np
import matplotlib
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
ranges = [[-1, 1], [-1, 1], [-1, 1], [-1, 1]]
for i in range(0, frames):
    for j in range(0, 25):
        graphData[0][i].append(float(rawData[i][3*j]))
        graphData[0][i].append(float(rawData[i][3*j + 1]))
        graphData[0][i].append(float(rawData[i][3*j + 2]))


ft = FeatureTransformer(rawData)

for featureVector in ft.featureVectors:
    ft._translate(featureVector)
processed = ft.featureVectors

for i in range(0, frames):
    for j in range(0, 25):
        graphData[1][i].append(processed[i][3*j])
        graphData[1][i].append(processed[i][3*j + 1])
        graphData[1][i].append(processed[i][3*j + 2])

for featureVector in ft.featureVectors:
    ft._rotate(featureVector)
processed = ft.featureVectors
for i in range(0, frames):
    for j in range(0, 25):
        graphData[2][i].append(processed[i][3*j])
        graphData[2][i].append(processed[i][3*j + 1])
        graphData[2][i].append(processed[i][3*j + 2])

for featureVector in ft.featureVectors:
    ft._scale(featureVector)
processed = ft.featureVectors
for i in range(0, frames):
    for j in range(0, 25):
        graphData[3][i].append(processed[i][3*j])
        graphData[3][i].append(processed[i][3*j + 1])
        graphData[3][i].append(processed[i][3*j + 2])



fig = plot.figure()

plot_num = 1
for i in range(0, 4):
    for j in range(0, frames):
       
        ax = fig.add_subplot(4, 2, plot_num, projection=projection)
        plot_num += 1
        xdata, ydata, zdata = ([], [], [])
        for k in range(0, 75, 3):
            xdata.append(graphData[i][j][k])
            ydata.append(graphData[i][j][k+1])
            if(projection == '3d'):
                zdata.append(graphData[i][j][k+2])
            else:
                zdata.append(30) # when projecting onto 2d, zdata must be a constant value for each entry
        ax.scatter(xdata, ydata, zdata,
                label="skelet joints")

        ax.scatter(
                [xdata[(JOINTS[PyKinectV2.JointType_SpineBase])]],
                [ydata[(JOINTS[PyKinectV2.JointType_SpineBase])]],
                [zdata[(JOINTS[PyKinectV2.JointType_SpineBase])]], 
                label="heup joint")
        ax.scatter(
                [xdata[(JOINTS[PyKinectV2.JointType_Head])]],
                [ydata[(JOINTS[PyKinectV2.JointType_Head])]],
                [zdata[(JOINTS[PyKinectV2.JointType_Head])]],
                 label="head joint")
        ax.set_xlabel("X")
        ax.set_ylabel("Y", rotation=0, labelpad=20)
        #ax.set_zlabel("Z", rotation=0, labelpad=20)
        ax.set_xlim(ranges[i])
        ax.view_init(90, 270)
        plot.show()



fig.tight_layout(pad=0.0, w_pad=0, h_pad=0)

fig.legend(labels=('Skelet joints', 'Heup joint', 'Hoofd joint'), loc='upper left')
fig.title = "Preprocessingfase"
fig.set_figheight(10)
fig.set_figwidth(10)


#mng = plot.get_current_fig_manager()
#mng.resize(1366, 768)
#mng.full_screen_toggle()
plot.subplots_adjust(left=0.2, bottom=0.08, wspace=0.22, hspace=0.36)
plot.draw()
plot.show()
