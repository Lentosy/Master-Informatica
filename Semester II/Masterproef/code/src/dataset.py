
import sys
import csv
import pandas


from domain.constants import ACTIONS, JOINTS_NAMES
from domain.Joint import Joint, Point3D, Quaternion4D

class Dataset(object):
    """
    This class represents a dataset that is compatible with the sklearn machine learning library
    The data list contains a feature vector for each sample.
    The target list contains the ground truth for each sample
    """
    def __init__(self, persons: list):
        """
        This returns a sklearn compatible dataset for the given persons. It can be used as either a training set or testing set.
        """
        data, target = ([], []) # create 2 empty lists
        for person in persons:
            for action in ACTIONS:
                folder = f"..\\data_old\\{person}\\{action}"
                try:
                    labels = pandas.read_csv(f"{folder}\\labels.txt", header = None)
                    target.extend(labels.to_numpy().ravel())
                    frames = []

                    with open(f"{folder}\\joints.txt") as joints:
                        csvReader = csv.reader(joints, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
                        for row in csvReader:
                            joints = []
                            for i in range(0, 25):
                                joints.append(Joint(
                                    JOINTS_NAMES[i],
                                    Point3D(row[3*i], row[3*i + 1], row[3*i + 2]),
                                    Quaternion4D(row[75 + (4*i) + 3], row[75 + (4*i) + 0], row[75 + (4*i) + 1] ,row[75 + (4*i) + 2])
                                    ))
                            frames.append(joints)
                    #ft = FeatureTransformer(rawData)
                    data.extend(frames)
                except FileNotFoundError as fnfe:
                    pass
                   # sys.stdout.write(str(fnfe) + "\n")
        if(len(data) != len(target)):

            raise ValueError(f"The length of data and target are not the same (data = {len(data)}, target = {len(target)})")
            
        self.data = data
        self.target = target
        
    def __len__(self):
        """
        Provides an easy way to get the number of samples.
        """
        return len(self.data) # data and target attribute always have same length


    def flatten(self):
        for i in range(0, len(self)):
            flattened = []
            for j in range(0, len(self.data[i])):
                flattened.extend(self.data[i][j].flatten())
            self.data[i] = flattened