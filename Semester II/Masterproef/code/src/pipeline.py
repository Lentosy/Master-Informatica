from sklearn.svm import SVC
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
import pandas as pd
import numpy as np

from constants import PERSONS, ACTIONS

FOLDER = "data/"

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

#def load_trainingset():
#    trainingset = Dataset() # trainingset is a n * k matrix with n = # samples (frames) and k = # features (175)
#    for i in range(1, len(ACTIONS)):
#        try:
#            joints = pd.read_csv(FOLDER + f"{PERSONS[0]}\\{ACTIONS[i]}\\joints.txt", header = None, sep = ';')
#            labels = pd.read_csv(FOLDER + f"{PERSONS[0]}\\{ACTIONS[i]}\\labels.txt")
#                
#            trainingset.target.extend(labels.values)
#            trainingset.data.extend(joints.values)
#        except FileNotFoundError as fnfe:
#            print(fnfe)
#    return trainingset
#
#def load_validationset():
#    validationset = Dataset()
#    try:
#        joints = pd.read_csv(FOLDER + f"{PERSONS[0]}\\{ACTIONS[len(ACTIONS) - 2]}\\joints.txt", header = None, sep = ';')
#        labels = pd.read_csv(FOLDER + f"{PERSONS[0]}\\{ACTIONS[len(ACTIONS) - 2]}\\labels.txt")
#        validationset.target.extend(labels.values)
#        validationset.data.extend(joints.values)
#    except FileNotFoundError as fnfe:
#        print(fnfe)
#
#    return validationset
#
#
#
#trainingset = load_trainingset()
#validationset = load_validationset()
#
#for name, clf in zip(names, classifiers):
#    clf.fit(trainingset.data, trainingset.target)
#    res = clf.predict(validationset.data)
#    positive, negative = (0, 0)
#    for i in range(0, len(res)):
#        if(res[i] == validationset.target[i]):
#            positive += 1
#        else:
#            negative += 1
#        
#    print(f"[{name}]: correct = {positive/len(res) * 100}%, false = {negative/len(res) * 100}%")
#