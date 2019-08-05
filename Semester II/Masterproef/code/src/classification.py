import sys
import csv
import numpy as np
import time 
import matplotlib.pyplot as plt
from dataset import Dataset
from domain.constants import PERSONS, ACTIONS
from classification_strategies import ClassificationStrategy, PerFrameClassification, SlidingWindowClassification, EnergyBasedSegmentationClassification
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import GridSearchCV, cross_validate
from transform_features import FeatureTransformer


def main():
    featureTransformer = FeatureTransformer()   
    classifier = RandomForestClassifier(max_depth = None, min_samples_split = 2, n_estimators = 10, max_features = 10)
    classificationStrategy = EnergyBasedSegmentationClassification(threshold = 0.05)

    print(f"Using strategy {str(classificationStrategy)}")
    classStatistics = [[None] * len(ACTIONS)] * len(PERSONS) # recall, precision and f1-score for EACH class for EACH person
    avgStatistics = [{} for i in range(0, len(PERSONS))]     # contains average recall, precision and f1-score for EACH person
    avgConfusionMatrix = None                                # represents the average confusion matrix

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

        classifier.fit(trainingset.data, trainingset.target)
        classificationStrategy.perform(testingset, classifier)
        
        (results, cm) = (classificationStrategy.report, classificationStrategy.confusionMatrix)
        if(avgConfusionMatrix is None):
            avgConfusionMatrix = cm
        else:
            avgConfusionMatrix += cm
        
        for j in range(0, len(ACTIONS)):
            classStatistics[i - 1][j] = results[ACTIONS[j]]
        avgStatistics[i-1] = results['weighted avg']

    avgConfusionMatrix = avgConfusionMatrix / len(PERSONS)
    plotConfusionMatrix(avgConfusionMatrix,title=str(classificationStrategy))
    plotClassScores(classStatistics, title=str(classificationStrategy))
    plotGlobalScore(avgStatistics)
    mng = plt.get_current_fig_manager()

    mng.window.state('zoomed') 
    plt.show() 

def plotConfusionMatrix(confusionMatrix,
                          title=None,
                          cmap=plt.cm.get_cmap('Blues')):

    confusionMatrix = confusionMatrix.astype('float') / confusionMatrix.sum(axis=1)[:, np.newaxis]
    ax = plt.subplot(2, 2, 1)
    im = plt.matshow(confusionMatrix, 0, interpolation='nearest', cmap=cmap)
    ax.figure.colorbar(im, ax=ax)
    # We want to show all ticks...
    ax.set(xticks=np.arange(confusionMatrix.shape[1]),
           yticks=np.arange(confusionMatrix.shape[0]),
           # ... and label them with the respective list entries
           xticklabels=ACTIONS, yticklabels=ACTIONS,
           title=title,
           ylabel='True label',
           xlabel='Predicted label')

    # Rotate the tick labels and set their alignment.
    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
             rotation_mode="anchor")

    # Loop over data dimensions and create text annotations.

    fmt = '.2f'
    thresh = confusionMatrix.max() / 2.
    for i in range(confusionMatrix.shape[0]):
        for j in range(confusionMatrix.shape[1]):
            ax.text(j, i, format(confusionMatrix[i, j], fmt),
                    ha="center", va="center",
                    color="white" if confusionMatrix[i, j] > thresh else "black")

    


def plotClassScores(classStatistics, title):
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
    ax = plt.subplot(2, 2, 2)
    index = np.arange(n_groups)
    bar_width=0.35

    ax.bar(index + 1/2 * bar_width, precision, bar_width, alpha=0.5, label='precision', color='b')
    ax.bar(index + 3/2 * bar_width, recall, bar_width, alpha=0.5, label='recall', color='g')
    ax.plot(index +  bar_width, f1score, '-o', label='f1-score', color='red')
    plt.xticks(index + bar_width, range(0, len(ACTIONS)))
    plt.yticks(ticks=[0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])

    plt.title(f"Precision, recall and f1-scores per human gesture - {title}")
    plt.xlabel('Gesture label')
    plt.ylabel('Score')
    plt.legend()
    
def plotGlobalScore(avgStatistics):
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

    ax = plt.subplot(2, 2, 3)
    ax.axis('off')
    ax.axis('tight')


    for key in globalPerformance.keys():
        globalPerformance[key] = f"{round(globalPerformance[key] * 100,2)}%"

    table = ax.table(cellText=[list(globalPerformance.values())], colLabels=list(globalPerformance.keys()), loc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(11)



if __name__ == '__main__':
    main()