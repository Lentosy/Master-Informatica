
import sys
import csv
import pandas

from domain.constants import ACTIONS, JOINTS
from domain.Joint import Joint, Point3D, Quaternion4D

class Dataset(object):
    """
    This class represents a dataset that is compatible with the sklearn machine learning library
    The data list contains a feature vector for each sample.
    The target list contains the ground truth for each sample
    """

    @classmethod
    def __init__(self, persons: list):
        """
        This returns a sklearn compatible dataset for the given persons. It can be used as either a training set or testing set.
        """
        self.data = []
        self.target = []
        if persons is None:
            return

        for person in persons:
            folder = f"data\\{person}"
    
            try:
                labels = pandas.read_csv(f"{folder}\\labels.txt", header = None)
                self.target.extend(labels.to_numpy().ravel())
                frames = []
                with open(f"{folder}\\joints.txt") as joints:
                    csvReader = csv.reader(joints, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
                    for row in csvReader:
                        joints = []
                        for i in range(0, 25):
                            joints.append(Joint(
                                JOINTS[i]['name'],
                                JOINTS[i]['weight'],
                                Point3D(row[7*i], row[7*i + 1], row[7*i + 2]),
                                Quaternion4D(row[7*i + 6], row[7*i + 3], row[7*i + 4] ,row[7*i + 5])
                                )
                            )
                        frames.append(joints)
                self.data.extend(frames)
            except FileNotFoundError as fnfe:
                sys.stdout.write(str(fnfe) + "\n")
                    
        if(len(self.data) != len(self.target)):
            raise ValueError(f"The length of data and target are not the same (data = {len(data)}, target = {len(target)})")
    

    @classmethod
    def __getitem__(self, key):
        if isinstance(key, slice):
            raise ValueError("Slice not supported")
        else:
            return (self.data[key], self.target[key])

        
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


    @staticmethod
    def getDebugDataset():

        folder = f"data\\DEBUG"

        dataset = Dataset(None)
        frames = []
        with open(f"{folder}\\joints.txt") as joints:
            csvReader = csv.reader(joints, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
            for row in csvReader:
                joints = []
                for i in range(0, 25):
                    joints.append(Joint(
                        JOINTS[i]['name'],
                        JOINTS[i]['weight'],
                        Point3D(row[7*i], row[7*i + 1], row[7*i + 2]),
                        Quaternion4D(row[7*i + 6], row[7*i + 3], row[7*i + 4] ,row[7*i + 5])
                        )
                    )
                frames.append(joints)
        dataset.data.extend(frames)
        return dataset
        
        
        