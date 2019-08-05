import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from math import sqrt, floor
from screeninfo import get_monitors

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.projections as proj

from cv2wrapper import highgui, imgproc

import numpy as np
from numpy import linspace
from numpy.fft import fft


from GraphManager import GraphManager
from dataset import Dataset
from domain.constants import JOINTS
from transform_features import FeatureTransformer




def viewFrame(event):
    if(event.inaxes != potentialAx): # only allow figure showing on potential graph
        return

    framenum = floor(event.xdata)

    frame = highgui.openImage(f'data/{PERSON}/frame{framenum}.jpg')
    previousff = highgui.openImage(f'data/{PERSON}/frame{framenum - 2}.jpg')
    previousf = highgui.openImage(f'data/{PERSON}/frame{framenum - 1}.jpg')
    nextf  = highgui.openImage(f'data/{PERSON}/frame{framenum + 1}.jpg')
    nextff  = highgui.openImage(f'data/{PERSON}/frame{framenum + 2}.jpg')

    (maxW, maxH) = (get_monitors()[1].width, get_monitors()[1].height)

    d = (
        int(frame.shape[1] * (maxW // 6)/maxW), 
        int(frame.shape[0] * (maxW // 6)/maxW)
    )

    frame = imgproc.resize(frame, d)
    previousff = imgproc.resize(previousff, d)
    previousf = imgproc.resize(previousf, d)
    nextf = imgproc.resize(nextf, d)
    nextff = imgproc.resize(nextff, d)
    imgproc.addBorder(frame, None)

    highgui.showImagesHorizontally(f'Frame {framenum - 2} - {framenum + 2}', previousff, previousf, frame , nextf, nextff)
    

PERSON = 'BERT'
def main():
    datasets = [Dataset(['BERT']), Dataset(['DEMING'])]

    for i in range(0, len(datasets)):
        ft = FeatureTransformer(datasets[i].data)
        ft.preProcessing()
    
    gm = GraphManager(cols=1, rows=4)

    potentials = []
    for i in range(0, len(datasets)):
        potentials.append(getPotentials(datasets[i]))

    global potentialAx
    potentialAx = gm.getNextAx()
    plotPotential(potentials[0], potentialAx, visualizeSegmentation=True, targets=datasets[0].target)
    
    plotFFT(potentials[0][51:84], gm.getNextAx(), title='51-84 (RH_MOVE_FORWARD)')
    plotFFT(potentials[1][58:104], gm.getNextAx(), title='58-104 (RH_MOVE_FORWARD)')
 
    gm.addEvent('button_release_event', viewFrame)
    gm.adjustSubplots(hspace=0.6)
    gm.show(fullscreen=True)


def getPotentials(dataset):
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

def plotFFT(potentials, ax, title=None):
    # Number of samplepoints
    N = len(potentials)
    # sample spacing
    T = 1.0 / 30.0
    
    mean = sum(potentials)/len(potentials)
    # remove DC bias by subtracting the mean of the values from every other value
    y = [e - mean for e in potentials]
    yf = fft(y)

    # The result of fft are complex numbers [z1, z2, ..., zn]
    #  this array is symmetrical (last half is negative of first half) so it gives no new information, this part is discarded
    xf = linspace(0.0, 1.0/(2.0*T), N//2)  

    ax.bar(xf, 2.0/N * np.abs(yf[:N//2]), width= 0.1)
    ax.set( xlabel='Frequency (Hz)',
            ylabel='Potential',
            title=title)


def plotPotential(energies, ax, visualizeSegmentation = False, targets = None):
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
                if gtActionStarted == True and (target == 0 or target != targets[i - 1]):
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