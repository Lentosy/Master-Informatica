import sys, os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1' # surpress pygame output
import csv
import matplotlib.pyplot as plot
import numpy as np
import time 

from classification_strategies import ClassificationStrategy, PerFrameClassification, SimpleBufferClassification, WeightedBufferClassification
from constants import PERSONS, ACTIONS
from dataset import Dataset

from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import GridSearchCV, cross_validate


class Classifier(object):
    """
    Wraps a sklearn classifier by composition and allows extra methods for performance measuring.
    """
    def __init__(self, sklearnClassifier):
        self.classifier = sklearnClassifier

    def classify(self, trainingset, testingset, strategy):
        self.classifier.fit(trainingset.data, trainingset.target)
        strategy.perform(testingset, self.classifier)
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



strategies = [WeightedBufferClassification()]

def plotStrategy(strategy : ClassificationStrategy, recalls: list, precisions: list, f1scores: list):
    plot.title(f"Average precision/recall for each classifier ({str(strategy)})")
    plot.plot(precisions, label = 'precision', linestyle = (0, (1, 10)), marker='o')
    plot.plot(recalls, label = 'recall', linestyle = (0, (1, 10)), marker='o')
    plot.plot(f1scores, label = 'F1 score', linestyle = (0, (1, 10)), marker='o')
    plot.legend()
    plot.xticks(np.arange(1), 'Random Forest Classifier')
    plot.xlabel('classifier')
    plot.ylabel('percentage')
    axes = plot.gca()
    axes.set_ylim([0, 100])
    plot.show()


# CROSS VALIDATION dient enkel om na te gaan hoe goed onze classifier zou zijn als hij een persoon ziet waarop niet getraind is.
# Het uiteindelijk model zal wel trainen op alle personen in de dataset

classifierTester = ClassifierTester()
classifier = RandomForestClassifier(max_depth = None, min_samples_split = 2, n_estimators = 27, max_features = 10)
for classificationStrategy in strategies:
    print(f"Using strategy {str(classificationStrategy)}")
    statistics = [0 for i in range(3)]
    for i in range(1, len(PERSONS) + 1): # Leave-One-Out cross validation
        trainingPersons = PERSONS[:i - 1] + PERSONS[i:]
        testingPerson = [PERSONS[i - 1]]
        print(f"\t{trainingPersons} {testingPerson}")
        trainingset = Dataset(trainingPersons)
        testingset = Dataset(testingPerson)
        results = Classifier(classifier).classify(trainingset, testingset, classificationStrategy)
        print(f"\t\t{results}")
        for j in range(0, len(results)):
            statistics[j] += results[j]

    
    for i in range(0, 3):
        statistics[i] /= len(PERSONS) # divide by the amount of times we cross validate

    print(statistics)
    


#for classificationStrategy in strategies:
#    print(f"Using strategy {str(classificationStrategy)}")
#    statistics = [[0 for i in range(3)] for j in range(len(classifiers))]
#    classifierIndex = 0
#    for sklearnClassifier in classifiers: # classifiers will only contain random forest tree for now
#        parameters = {'max_depth': [i for i in range(5, 10)]}
#        print(f"----Cross validating {classifierNames[classifierIndex]}")
#        for i in range(1, len(PERSONS) + 1): # Leave-One-Out cross validation
#
#            trainingPersons = PERSONS[:i - 1] + PERSONS[i:]
#            validationPerson = [PERSONS[i - 1]]
#            print(f"--------{trainingPersons} {validationPerson}")
#            trainingSet = Dataset(trainingPersons)
#            validationSet = Dataset(validationPerson)
#            classifierTester = ClassifierTester()
#            optimalizedClassifier = classifierTester.optimalize(sklearnClassifier, parameters, trainingSet)
#            start = time.time()
#            results = classifierTester.test(optimalizedClassifier, trainingSet, validationSet, classificationStrategy)
#            end = time.time()
#            print(f"------------{end - start} seconds")
#            print(f"------------{results}")
#            for j in range(0, len(results)):
#                statistics[classifierIndex][j] += results[j]
#                
#        for i in range(0, 3):
#            statistics[classifierIndex][i] /= len(PERSONS) # divide by the amount of times we cross validate
#        classifierIndex += 1
        
    

    #plotStrategy(classificationStrategy, [s[0] for s in statistics], [s[1] for s in statistics], [s[2] for s in statistics])