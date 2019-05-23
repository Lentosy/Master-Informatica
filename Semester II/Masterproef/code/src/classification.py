import sys, os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import csv
import pandas
import matplotlib.pyplot as plot
import numpy as np
import time 

from classification_strategies import ClassificationStrategy, PerFrameClassification, SimpleBufferClassification, WeightedBufferClassification
from constants import PERSONS, ACTIONS

from transform_features import FeatureTransformer

from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.ensemble import RandomForestClassifier, AdaBoostClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import GridSearchCV


class Dataset(object):
    """
    This class represents a dataset that is compatible with the sklearn machine learning library
    The data list contains a feature vector for each sample.
    The target list contains the ground truth for each sample
    """

    def __init__(self, persons: list):
        """
        This returns a sklearn compatible dataset for the given persons. It can be used as either a training set or validation set.
        """
        data, target = ([], []) # create 2 empty lists
        for person in persons:
            for action in ACTIONS:
                folder = f"..\\data\\{person}\\{action}"
                try:
                    joints = pandas.read_csv(f"{folder}\\joints.txt", header = None, sep = ';')
                    labels = pandas.read_csv(f"{folder}\\labels.txt", header = None)
                    target.extend(labels.to_numpy().ravel())
                    rawData = []
                    with open(f"{folder}\\joints.txt") as dataFile:
                        csvReader = csv.reader(dataFile, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
                        for row in csvReader:
                            rawData.append(row)
                    ft = FeatureTransformer(rawData)
                    data.extend(ft.preProcessing())
                except FileNotFoundError as fnfe:
                    pass
                    #sys.stdout.write(str(fnfe) + "\n")
        if(len(data) != len(target)):
            raise ValueError(f"The length of data and target are not the same (data = {len(data)}, target = {len(target)})")
        
        self.data = data
        self.target = target
    

    def __len__(self):
        """
        Provides an easy way to get the number of samples.
        """
        return len(self.data) # data and target attribute always have same length

class Classifier(object):
    """
    Wraps a sklearn classifier by composition and allows extra methods for performance measuring.
    """
    def __init__(self, sklearnClassifier):
        self.classifier = sklearnClassifier

    def classify(self, trainingSet, validationSet, strategy):
        self.classifier.fit(trainingSet.data, trainingSet.target)
        strategy.perform(validationSet, self.classifier)
        return strategy.getStatistics()




class ClassifierTester(object):
    def __init__(self):
        pass
    
    def test(self, classifier, trainingSet, validationSet, classificationStrategy):
        results = Classifier(classifier).classify(trainingSet, validationSet, classificationStrategy)
        return results
    
    def optimalize(self, classifier, parameters, trainingSet):
        optimalizedClassifier = GridSearchCV(estimator = classifier, param_grid = parameters, cv = 5, iid = True, scoring = 'recall_macro')
        optimalizedClassifier.fit(trainingSet.data, trainingSet.target)
        print(f"# Tuning hyper-parameters for recall")
        print()
        print("Best parameters set found on development set:")
        print()
        print(optimalizedClassifier.best_params_)
        print()
        print("Grid scores on development set:")
        print()
        means = optimalizedClassifier.cv_results_['mean_test_score']
        stds = optimalizedClassifier.cv_results_['std_test_score']
        for mean, std, params in zip(means, stds, optimalizedClassifier.cv_results_['params']):
            print("%0.3f (+/-%0.03f) for %r"
                % (mean, std * 2, params))
        return optimalizedClassifier


classifierNames = [
    #"Nearest Neighbors", 
    #"RBF SVM", 
    "Random Forest", 
    #"AdaBoost",
    #"Naive Bayes"
]

classifiers = [
    #KNeighborsClassifier(3),
    #SVC(gamma='scale', C=100),
    RandomForestClassifier(max_depth = 8, n_estimators = 10),
    #AdaBoostClassifier(),
    #GaussianNB(),
]

strategies = [SimpleBufferClassification()]

def plotStrategy(strategy : ClassificationStrategy, recalls: list, precisions: list, f1scores: list):
    plot.title(f"Average precision/recall for each classifier ({str(strategy)})")
    plot.plot(precisions, label = 'precision', linestyle = (0, (1, 10)), marker='o')
    plot.plot(recalls, label = 'recall', linestyle = (0, (1, 10)), marker='o')
    plot.plot(f1scores, label = 'F1 score', linestyle = (0, (1, 10)), marker='o')
    plot.legend()
    plot.xticks(np.arange(len(classifierNames)), classifierNames)
    plot.xlabel('classifier')
    plot.ylabel('percentage')
    axes = plot.gca()
    axes.set_ylim([0, 100])
    plot.show()


for classificationStrategy in strategies:
    print(f"Using strategy {str(classificationStrategy)}")
    statistics = [[0 for i in range(3)] for j in range(len(classifiers))]
    classifierIndex = 0
    for sklearnClassifier in classifiers: # classifiers will only contain random forest tree for now
        parameters = {'max_depth': [i for i in range(5, 10)]}
        print(f"----Cross validating {classifierNames[classifierIndex]}")
        for i in range(1, len(PERSONS) + 1): # Leave-One-Out cross validation

            trainingPersons = PERSONS[:i - 1] + PERSONS[i:]
            validationPerson = [PERSONS[i - 1]]
            print(f"--------{trainingPersons} {validationPerson}")
            trainingSet = Dataset(trainingPersons)
            validationSet = Dataset(validationPerson)
            classifierTester = ClassifierTester()
            optimalizedClassifier = classifierTester.optimalize(sklearnClassifier, parameters, trainingSet)
            start = time.time()
            results = classifierTester.test(optimalizedClassifier, trainingSet, validationSet, classificationStrategy)
            end = time.time()
            print(f"------------{end - start} seconds")
            print(f"------------{results}")
            for j in range(0, len(results)):
                statistics[classifierIndex][j] += results[j]
                
        for i in range(0, 3):
            statistics[classifierIndex][i] /= len(PERSONS) # divide by the amount of times we cross validate
        classifierIndex += 1
        
    

    plotStrategy(classificationStrategy, [s[0] for s in statistics], [s[1] for s in statistics], [s[2] for s in statistics])