import sys
import csv
import numpy as np
import time 
import matplotlib.pyplot as plt
from dataset import Dataset
from domain.constants import PERSONS, ACTIONS
from classification_strategies import ClassificationStrategy, PerFrameClassification, SimpleBufferClassification, WeightedBufferClassification
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import GridSearchCV, cross_validate
from transform_features import FeatureTransformer



class Classifier(object):
    """
    Wraps a sklearn classifier by composition and allows extra methods for performance measuring.
    """
    def __init__(self, sklearnClassifier):
        self.classifier = sklearnClassifier

    def classify(self, trainingset, testingset, strategy):
        self.classifier.fit(trainingset.data, trainingset.target)
        strategy.perform(validationset=testingset, classifier=self.classifier)
        return strategy.getStatistics()





strategies = [PerFrameClassification()]

# CROSS VALIDATION dient enkel om na te gaan hoe goed onze classifier zou zijn als hij een persoon ziet waarop niet getraind is.
# Het uiteindelijk model zal wel trainen op alle personen in de dataset

featureTransformer = FeatureTransformer()
classifier = RandomForestClassifier(max_depth = None, min_samples_split = 2, n_estimators = 27, max_features = 10)
for classificationStrategy in strategies:
    print(f"Using strategy {str(classificationStrategy)}")
    classStatistics = [[None] * len(ACTIONS)] * len(PERSONS)
    avgStatistics = [{} for i in range(0, len(PERSONS))]
   
    for i in range(1, len(PERSONS) + 1): # Leave-One-Subject-Out cross validation
        trainingPersons = PERSONS[:i - 1] + PERSONS[i:]
        testingPerson = [PERSONS[i - 1]]
        print(f"\t{trainingPersons} {testingPerson}")
        trainingset = Dataset(trainingPersons)
        testingset = Dataset(testingPerson)

        featureTransformer.setFeatureVectors(trainingset.data)
        featureTransformer.preProcessing()
        featureTransformer.setFeatureVectors(testingset.data)
        featureTransformer.preProcessing()

        trainingset.flatten()
        testingset.flatten()
        results = Classifier(classifier).classify(trainingset, testingset, classificationStrategy)
        for j in range(0, len(ACTIONS)):
            classStatistics[i - 1][j] = results[ACTIONS[j]]
        avgStatistics[i-1] = results['weighted avg']
    
    weights = []
    for i in range(0, len(avgStatistics)):
        weights.append(avgStatistics[i]['support'])
    weights = [w/sum(weights) for w in weights] # normalize weights

    globalPerformance = {
        'recall': 0,
        'precision': 0,
        'f1-score': 0
    }
    for i in range(0, len(avgStatistics)):
        for key in globalPerformance.keys():
            globalPerformance[key] += weights[i] * avgStatistics[i][key]

    #print(classStatistics)
    #print(globalPerformance)
    precision = []
    recall = []
    f1score = []
    for i in range(0, len(ACTIONS)):
        p = 0
        r = 0
        f = 0
        for j in range(0, len(PERSONS)):
            p += classStatistics[j][i]['precision']
            r += classStatistics[j][i]['recall']
            f += classStatistics[j][i]['f1-score']
        p /= len(PERSONS)
        r /= len(PERSONS)
        f /= len(PERSONS)
        precision.append(p)
        recall.append(r)
        f1score.append(f)
    

    n_groups = len(ACTIONS)
    fig, ax = plt.subplots()
    index = np.arange(n_groups)
    bar_width=0.35
    opacity=0.8

    ax.bar(index + 1/2 * bar_width, precision, bar_width, alpha=0.5, label='precision', color='b')
    ax.bar(index + 3/2 * bar_width, recall, bar_width, alpha=0.5, label='recall', color='g')
    ax.plot(index +  bar_width, f1score, '-o', label='f1-score', color='red')
    plt.xticks(index + bar_width, range(0, len(ACTIONS)))
    plt.yticks(ticks=[0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])

    plt.title(f"Precision, recall and f1-scores per human gesture - {classificationStrategy}")
    plt.xlabel('Gesture label')
    plt.ylabel('Score')
    plt.legend(loc='upper left')
    plt.tight_layout()
    plt.show()