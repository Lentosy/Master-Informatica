import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import csv
import numpy as np
import matplotlib.pyplot as plot
from transform_features import FeatureTransformer
from mpl_toolkits import mplot3d



rawData = []
with open(f"..\\data\\DEBUG\\joints.txt") as dataFile:
    csvReader = csv.reader(dataFile, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
    for row in csvReader:
        rawData.append(row)


graphData = [[[],[]], [[],[]], [[],[]], [[],[]]]
ranges = [[-300, 300], [-300, 300], [-2, 2], [-2, 2]]
for i in range(0, 2):
    for j in range(0, 75, 3):
        graphData[0][i].append(-float(rawData[i][j])) # negative so skeleton is standing upright
        graphData[0][i].append(-float(rawData[i][j+1]))
        graphData[0][i].append(float(rawData[i][j+2]))


ft = FeatureTransformer(rawData)

for featureVector in ft.featureVectors:
    ft._translateToOrigin(featureVector)
processed = ft.featureVectors

for i in range(0, 2):
    for j in range(0, 75, 3):
        graphData[1][i].append(-processed[i][j]) 
        graphData[1][i].append(-processed[i][j+1])
        graphData[1][i].append(processed[i][j+2])



for featureVector in ft.featureVectors:
    ft._scale(featureVector)
processed = ft.featureVectors
for i in range(0, 2):
    for j in range(0, 75, 3):
        graphData[2][i].append(-processed[i][j]) 
        graphData[2][i].append(-processed[i][j+1])
        graphData[2][i].append(processed[i][j+2])


for featureVector in ft.featureVectors:
    ft._rotate(featureVector)
processed = ft.featureVectors
for i in range(0, 2):
    for j in range(0, 75, 3):
        graphData[3][i].append(processed[i][j]) 
        graphData[3][i].append(processed[i][j+1])
        graphData[3][i].append(-processed[i][j+2])

fig, axes = plot.subplots(nrows=4, ncols=2)

for i in range(0, 4):
    for j in range(0, 2):
        xdata, ydata, zdata = ([], [], [])
        for k in range(3, 75, 3):
            xdata.append(graphData[i][j][k])
            ydata.append(graphData[i][j][k+1])
            zdata.append(graphData[i][j][k+2])
        
        axes[i][j].scatter(xdata, ydata, label="skelet joints")
        axes[i][j].scatter([graphData[i][j][0]],[graphData[i][j][1]], label="heup joint")
        axes[i][j].set_xlabel("X")
        axes[i][j].set_ylabel("Y", rotation=0, labelpad=20)
        axes[i][j].set_xlim(ranges[i])



axes[0][0].set_title("Frame 1 ruw skelet")
axes[0][1].set_title("Frame 2 ruw skelet")

axes[1][0].set_title("Frame 1 translatie")
axes[1][1].set_title("Frame 2 translatie")

axes[2][0].set_title("Frame 1 geschaald")
axes[2][1].set_title("Frame 2 geschaald")

axes[3][0].set_title("Frame 1 geroteerd")
axes[3][1].set_title("Frame 2 geroteerd")

fig.tight_layout(pad=0.0, w_pad=0, h_pad=0)

fig.legend(labels=('Skelet joints', 'Heup joint'), loc='upper left')
fig.title = "Preprocessingfase"
fig.set_figheight(10)
fig.set_figwidth(10)

plot.show()
