
import sys
import csv
import pandas
from sklearn.feature_selection import VarianceThreshold
from transform_features import FeatureTransformer
from constants import ACTIONS

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
                    rawData = []
                    with open(f"{folder}\\joints.txt") as joints:
                        csvReader = csv.reader(joints, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
                        for row in csvReader:
                            rawData.append(row)
                    ft = FeatureTransformer(rawData)
                    data.extend(ft.preProcessing())
                except FileNotFoundError as fnfe:
                    pass
                    #sys.stdout.write(str(fnfe) + "\n")
        if(len(data) != len(target)):
            raise ValueError(f"The length of data and target are not the same (data = {len(data)}, target = {len(target)})")
        
        # remove features which have the same value for each sample. This is equivalent as removing the quaternions which do not actaully exist (see constants.py)
        sel = VarianceThreshold(threshold=0.) 
        sel.fit_transform(data)
        
        self.data = data
        self.target = target
        
    def __len__(self):
        """
        Provides an easy way to get the number of samples.
        """
        return len(self.data) # data and target attribute always have same length