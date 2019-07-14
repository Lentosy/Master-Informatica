import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.projections as proj

from math import sqrt

from dataset import Dataset
from domain.constants import JOINTS
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
    ax.set_title(JOINTS[joint_index]['name'])
    xdata = [joint.point.x for joint in joints]
    ydata = [joint.point.y for joint in joints]
    energies = [0] # first frame has no energy
    for i in range(1, len(joints)):
        diff_x = joints[i].point.x - joints[i - 1].point.x
        diff_y = joints[i].point.y - joints[i - 1].point.y
        diff_z = joints[i].point.z - joints[i - 1].point.z
        d = sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z)
        energies.append(0.5 * JOINTS[joint_index]['weight'] * d * d)
    

    plt.scatter(xdata, ydata, c=energies)
    plt.colorbar()






if __name__ == '__main__':
    main()