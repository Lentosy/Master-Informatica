from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
import pandas as pd
import numpy as np

from constants import PERSONS, ACTIONS

names = ["Nearest Neighbors", "RBF SVM", "Random Forest"]
classifiers = [
    KNeighborsClassifier(3),
    SVC(gamma = 'scale' , C = 100),
    RandomForestClassifier(max_depth = 5, n_estimators = 10, max_features = 1)
]

class Dataset(object):
    def __init__(self):
        self.data = []
        self.target = []

def load_trainingset(trainingPersons):
    trainingset = Dataset() # trainingset is a n * k matrix with n = # samples (frames) and k = # features (175)

    for person in trainingPersons:
        for action in ACTIONS:
            folder = f"data\\{person}\\{action}"
            try:
                joints = pd.read_csv(f"{folder}\\joints.txt", header = None, sep = ';')
                labels = pd.read_csv(f"{folder}\\labels.txt", header = None)
                trainingset.target.extend(labels.to_numpy().ravel())
                trainingset.data.extend(joints.to_numpy())
            except FileNotFoundError as fnfe:
                print(fnfe)
    return trainingset

def load_validationset(validationPerson):
    validationset = Dataset() 
    for action in ACTIONS:
        folder = f"data\\{validationPerson}\\{action}"
        try:
            joints = pd.read_csv(f"{folder}\\joints.txt", header = None, sep = ';')
            labels = pd.read_csv(f"{folder}\\labels.txt", header = None)
            validationset.target.extend(labels.to_numpy().ravel())
            validationset.data.extend(joints.to_numpy())
        except FileNotFoundError as fnfe:
            print(fnfe)
    return validationset

def fitAndPredict(trainingset, validationset):
    for name, clf in zip(names, classifiers):
        clf.fit(trainingset.data, trainingset.target)
        res = clf.predict(validationset.data)
        positive, negative = (0, 0)
        for i in range(0, len(res)):
            if(res[i] == validationset.target[i]):
                positive += 1
            else:
                negative += 1

        print(f"[{name}]: correct = {positive/len(res) * 100}%, false = {negative/len(res) * 100}%")

        
        
trainingset = load_trainingset([PERSONS[1], PERSONS[2]])
validationset = load_validationset(PERSONS[0])

fitAndPredict(trainingset, validationset)

