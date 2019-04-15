import numpy as np
import sys, os
import pandas as pd
import matplotlib.pyplot as plot
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
from sklearn.naive_bayes import GaussianNB
from constants import PERSONS, ACTIONS

devnull = open(os.devnull, 'w')

names = ["Nearest Neighbors", "RBF SVM", "Random Forest", "AdaBoost",
         "Naive Bayes"]


# mogelijkheden: per actie een andere classifier trainen
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
    listPrecisions = [] # used to make a graph 
    listRecalls = []
    for name, clf in zip(names, classifiers):
        clf.fit(trainingset.data, trainingset.target)
        res = clf.predict(validationset.data)
        TP, FP, FN, TN = (0, 0, 0, 0)
        for i in range(0, len(res)):
            if(validationset.target[i] == 1):
                if(res[i] == 1):
                    TP += 1
                else:
                    FN += 1
            elif(validationset.target[i] == 0):
                if(res[i] == 1):
                    FP += 1
                else:
                    TN += 1    
        try:
            precision = round(TP/(TP + FP), 4) * 100 # given a positive prediction from the classifier: how likely is it to be correct?
            recall = round(TP/(TP + FN), 4) * 100    # given a positive example, how likely will the classifier correctly detect it?
            listPrecisions.append(precision)
            listRecalls.append(recall)
        except:
            listPrecisions.append(0)
            listRecalls.append(0)
    
    plot.plot(listPrecisions, label = 'precision')
    plot.plot(listRecalls, label = 'recall')
    plot.legend()
    plot.xticks(np.arange(5), names)
    plot.xlabel('classifier')
    plot.ylabel('percentage')
    plot.show()


for i in range(1, len(PERSONS) + 1):
    testPersons = PERSONS[:i - 1] + PERSONS[i:]
    validationPerson = PERSONS[i - 1]
    trainingset = load_trainingset(testPersons)
    validationset = load_validationset(validationPerson)
    #print(f"Training set: {testPersons}\nValidation set: {validationPerson}")
    plot.clf()
    plot.title(validationPerson)
    fitAndPredict(trainingset, validationset)