import numpy as np
import matplotlib.pyplot as pyplot
import pandas as pd


i = 1
j = 1
data = pd.read_csv(f'joints/joints_s0{i}_e0{j}.txt', sep = ";", header = None)
columns = ['frame']
jointCoordinates = []
for c in range(1, 21):  #1 inclusive, 21 exclusive
    jointCoordinates.append(f'x{c}')
    jointCoordinates.append(f'y{c}')
    jointCoordinates.append(f'z{c}')

columns.extend(jointCoordinates)



centerHipIndex = 1
leftHipIndex = 13
rightHipIndex = 17

centerHipCoordinates = [centerHipIndex, centerHipIndex + 1, centerHipIndex + 2]
leftHipCoordinates   = [leftHipIndex  , leftHipIndex   + 1, leftHipIndex   + 2]
rightHipCoordinates  = [rightHipIndex , rightHipIndex  + 1, rightHipIndex  + 2]

#print(data[centerHipCoordinates])

# define centerHip as origin of sphere coordinates
for i in range(1, 61, 3):
    print(data[i, i + 1, i + 2])


