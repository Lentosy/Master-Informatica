import time
import numpy as np
import sys, os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import pandas as pd
import matplotlib.pyplot as plot
import csv
from transform_features import FeatureTransformer
from classification_strategies import ClassificationStrategy, PerFrameClassification, SimpleBufferClassification
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

strategies = [PerFrameClassification, SimpleBufferClassification]


class Dataset(object):
    """
    This class represents a dataset that is compatible with the sklearn machine learning library
    The data list contains a feature vector for each sample.
    The target list contains the ground truth for each sample
    """
    def __init__(self, data, target):
        if(len(data) != len(target)):
            raise ValueError(f"The length of data and target are not the same (data = {len(data)}, target = {len(target)})")
        self.data = data
        self.target = target
    
    def __len__(self):
        """
        Provides an easy way to get the number of samples.
        """
        return len(self.data) # data and target attribute always have same length


def loadDataset(persons):
    """
    This returns a sklearn compatible dataset for the given persons. It can be used as either a training set or validation set.
    """
    data, target = ([], []) # create 2 empty lists

    for person in persons:
        for action in ACTIONS:
            folder = f"data\\{person}\\{action}"
            try:
                joints = pd.read_csv(f"{folder}\\joints.txt", header = None, sep = ';')
                labels = pd.read_csv(f"{folder}\\labels.txt", header = None)
                target.extend(labels.to_numpy().ravel())
                rawData = []
                with open(f"{folder}\\joints.txt") as dataFile:
                    csvReader = csv.reader(dataFile, delimiter=';')
                    for row in csvReader:
                        rawData.append(row)
                ft = FeatureTransformer(rawData)
                data.extend(ft.preProcessing())
            except FileNotFoundError as fnfe:
                devnull.write(str(fnfe))
    dataset = Dataset(data[:75], target[:75]) # dataset is a n * k matrix with n = # samples (frames) and k = # features (175)
    return dataset



def plotStrategy(strategy, precisions, recalls, f1scores):
    plot.title(f"Average precision/recall for each classifier ({str(strategy)})")
    plot.plot(precisions, label = 'precision', linestyle = (0, (1, 10)), marker='o')
    plot.plot(recalls, label = 'recall', linestyle = (0, (1, 10)), marker='o')
    plot.plot(f1scores, label = 'F1 score', linestyle = (0, (1, 10)), marker='o')
    plot.legend()
    plot.xticks(np.arange(5), names)
    plot.xlabel('classifier')
    plot.ylabel('percentage')
    axes = plot.gca()
    axes.set_ylim([0, 100])
    plot.show()


for classificationStrategy in strategies: # we want to compare each classification strategy
    start = time.time()
    avgPrecisions = [0] * len(classifiers)
    avgRecalls = [0] * len(classifiers)
    avgF1scores = [0] * len(classifiers)
    for i in range(1, len(PERSONS) + 1):
        testPersons = PERSONS[:i - 1] + PERSONS[i:]
        validationPerson = [PERSONS[i - 1]]
        trainingset = loadDataset(testPersons)
        validationset = loadDataset(validationPerson)
        (precisions, recalls, f1scores) = ([], [], []) 
        for classifier in classifiers:
            strategy = classificationStrategy(trainingset, validationset, classifier)
            strategy.perform()
            precisions.append(strategy.calculatePrecision())
            recalls.append(strategy.calculateRecall())
            f1scores.append(strategy.calculateF1Score())
        i = 0
        for p, a, f in zip(precisions, recalls, f1scores):
            avgPrecisions[i] += p
            avgRecalls[i] += a
            avgF1scores[i] += f
            i += 1
    avgPrecisions = [x / len(classifiers) for x in avgPrecisions]
    avgRecalls = [x / len(classifiers) for x in avgRecalls]
    avgF1scores = [x / len(classifiers) for x in avgF1scores]
    end = time.time()
    print(f"{strategy}: {end - start} seconds")
    plotStrategy(strategy, avgPrecisions, avgRecalls, avgF1scores)


