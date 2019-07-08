import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.projections as proj

from math import sqrt

from dataset import Dataset
from domain.constants import JOINTS, JOINTS_NAMES
from transform_features import FeatureTransformer


def main():
    
    dataset = Dataset.getDebugDataset()
    ft = FeatureTransformer(dataset.data)
    ft.preProcessing()
    plotTrajectories(dataset)
    


def plotTrajectories(dataset):
    fig = plt.figure()
    for i in range(0, len(JOINTS)):
        joints = [row[i] for row in dataset.data]
        plotTrajectoryForJoint(i, fig, joints)

    plt.subplots_adjust(hspace=0.5, wspace=0.5)
    
    plt.show()

def plotTrajectoryForJoint(joint_index, fig, joints):
    ax = fig.add_subplot(5, 5, joint_index + 1)
    ax.set_title(JOINTS_NAMES[joint_index])
    xdata = [joint.point.x for joint in joints]
    ydata = [joint.point.y for joint in joints]
    velocities = [0]
    for i in range(1, len(joints)):
        diff_x = joints[i].point.x - joints[i - 1].point.x
        diff_y = joints[i].point.y - joints[i - 1].point.y
        diff_z = joints[i].point.z - joints[i - 1].point.z
        d = sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z)
        velocities.append(d)
    

    plt.scatter(xdata, ydata, vmin=0, vmax=0.5, c=velocities)
    plt.colorbar()






if __name__ == '__main__':
    main()