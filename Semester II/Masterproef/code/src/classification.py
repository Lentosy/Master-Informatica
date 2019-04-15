import numpy as np
import sys, os
import pandas as pd
import matplotlib.pyplot as plot
from classification_strategies import perFrameClassification, simpleBufferClassification
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
    SVC(gamma='scale', C=100),
    RandomForestClassifier(max_depth=5, n_estimators=10, max_features=1),
    AdaBoostClassifier(),
    GaussianNB(),
]

class Dataset(object):
    def __init__(self):
        self.data = []
        self.target = []
    
    def __len__(self):
        return len(self.data) # data and target attribute always have same length


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

def evaluateClassifiers(trainingset, validationset, strategy):
    listPrecisions = [] # used to make a graph 
    listRecalls = []
    listF1scores = []
    for clf in classifiers:
        precision, recall, F1score = strategy(trainingset, validationset, clf)
        listPrecisions.append(precision)
        listRecalls.append(recall)
        listF1scores.append(F1score)

    return listPrecisions, listRecalls, listF1scores

avgPrecisions = [0] * len(classifiers)
avgRecalls = [0] * len(classifiers)
avgF1scores = [0] * len(classifiers)

for i in range(1, len(PERSONS) + 1):
    testPersons = PERSONS[:i - 1] + PERSONS[i:]
    validationPerson = PERSONS[i - 1]
    trainingset = load_trainingset(testPersons)
    validationset = load_validationset(validationPerson)
    #print(f"Training set: {testPersons}\nValidation set: {validationPerson}")
    precisions, recalls, F1scores = evaluateClassifiers(trainingset, validationset, perFrameClassification)

    i = 0
    for p, a, f in zip(precisions, recalls, F1scores):
        avgPrecisions[i] += p
        avgRecalls[i] += a
        avgF1scores[i] += f
        i += 1
    

avgPrecisions = [x / len(classifiers) for x in avgPrecisions]
avgRecalls = [x / len(classifiers) for x in avgRecalls]
avgF1scores = [x / len(classifiers) for x in avgF1scores]

plot.title("Average precision/recall for each classifier")
plot.plot(avgPrecisions, label = 'precision', linestyle = (0, (1, 10)), marker='o')
plot.plot(avgRecalls, label = 'recall', linestyle = (0, (1, 10)), marker='o')
plot.plot(avgF1scores, label = 'F1 score', linestyle = (0, (1, 10)), marker='o')
plot.legend()
plot.xticks(np.arange(5), names)
plot.xlabel('classifier')
plot.ylabel('percentage')
plot.show()