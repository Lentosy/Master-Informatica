from sklearn.svm import SVC
from sklearn.datasets import make_moons, make_circles, make_classification
from sklearn.neural_network import MLPClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.gaussian_process import GaussianProcessClassifier
from sklearn.gaussian_process.kernels import RBF
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.discriminant_analysis import QuadraticDiscriminantAnalysis
import pandas as pd
import numpy as np
import sys, os

from constants import PERSONS, ACTIONS

devnull = open(os.devnull, 'w')

names = ["Nearest Neighbors", "RBF SVM", "Random Forest", "AdaBoost",
         "Naive Bayes"]


# mogelijkheden: per actie een andere classifier maken

classifiers = [
    KNeighborsClassifier(3),
    SVC(gamma=2, C=1),
    RandomForestClassifier(max_depth=5, n_estimators=10, max_features=1),
    AdaBoostClassifier(),
    GaussianNB(),
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
                devnull.write(str(fnfe))
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
            devnull.write(str(fnfe))
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



for i in range(1, len(PERSONS) + 1):
    testPersons = PERSONS[:i - 1] + PERSONS[i:]
    validationPerson = PERSONS[i - 1]
    trainingset = load_trainingset(testPersons)
    validationset = load_validationset(validationPerson)
    print(f"Training set: {testPersons}\nValidation set: {validationPerson}")
    fitAndPredict(trainingset, validationset)

