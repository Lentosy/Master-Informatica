from constants import ACTIONS

class ClassificationStrategy(object):
    """
    A classification strategy implements a classification method. This strategy is independent of the chosen features.
    To evaluate the classifier, it's precision, recall and F1score is calculated. First, a list of precisions and recalls
    are generated from the confusion matrix for each action. The average precision, recall and f1score is then calculated for 
    the global performance of the classifier.
    """
    def __init__(self, trainingset, validationset, classifier):
        self.confusionMatrix = [] # The confusion matrix is represented by list in this order: [TP, FP, FN, TN]
        self.recalls = [0] * len(ACTIONS)
        self.precisions = [0] * len(ACTIONS)
        self.trainingset = trainingset
        self.validationset = validationset
        self.classifier = classifier
        self.classifier.fit(self.trainingset.data, self.trainingset.target)

    def calculateRecall(self): # given a positive prediction from the classifier: how likely is it to be correct?
        return sum(self.recalls) / len(ACTIONS)
    
    def calculatePrecision(self): # given a positive example, how likely will the classifier correctly detect it?
        return sum(self.precisions) / len(ACTIONS)

    def calculateF1Score(self): # harmonic mean of precision and recall
        f1score = 0
        for precision, recall in zip(self.precisions, self.recalls):
            f1score += (2 * (precision*recall) / (precision+recall))
        return f1score / len(ACTIONS)

    def perform(self):
        raise NotImplementedError("This is an abstract method. Implement this in a subclass")


class PerFrameClassification(ClassificationStrategy):
    """
    This is the simplest method as it classifies each frame individually.
    """ 

    def __init__(self, trainingset, validationset, classifier):
        ClassificationStrategy.__init__(self, trainingset, validationset, classifier)

    def perform(self):
        predictions = self.classifier.predict(self.validationset.data)
     
        for i in range(0, len(ACTIONS)):
            self.confusionMatrix = [0] * 4
            for j in range(0, len(predictions)):
                if(self.validationset.target[j] == i):
                    if(predictions[j] == i):
                        self.confusionMatrix[0] += 1
                    else:
                        self.confusionMatrix[2] += 1
                elif(self.validationset.target[j] != i):
                    if(predictions[j] == i):
                        self.confusionMatrix[1] += 1
                    else:
                        self.confusionMatrix[3] += 1
        
            try:
                (TP, FP, FN) = (self.confusionMatrix[0], self.confusionMatrix[1], self.confusionMatrix[3])
                self.precisions[i] = round(TP/(TP + FP), 4) * 100
                self.recalls[i] = round(TP/(TP + FN), 4) * 100   
            except ZeroDivisionError:
                pass




def simpleBufferClassification(trainingset, validationset, classifier):
    def getMajorityVote(list):
        frequency = dict(zip([i for i in range(len(ACTIONS))], [0 for i in range(len(ACTIONS))]))
        for l in list:
            frequency[max(0, l)] += 1
        (maxKey, maxVal) = (-1, -1)
        for (key, val) in iter(frequency.items()):
            if(val > maxVal):
                maxVal = val
                maxKey = key
        return maxKey

    bufferSize = 30
    iterations = (len(validationset) // bufferSize)
    print(iterations) 
    classifier.fit(trainingset.data, trainingset.target)
    precision, recall, F1score = (0, 0, 0)
    TP, FP, FN, TN = (0, 0, 0, 0)
    for currentIteration in range(0, iterations):
        bufferTarget = [validationset.target[j] for j in range(currentIteration*bufferSize, (currentIteration+1)*bufferSize)]
        bufferData =  [validationset.data[j] for j in range(currentIteration*bufferSize, (currentIteration+1)*bufferSize)]
        res = classifier.predict(bufferData) # let classifier classify the individual frames first
        majority = getMajorityVote(res)
        for x in range(0, bufferSize):
            if(bufferTarget[x] == 1):
                if(majority == 1):
                    TP += 1
                else:
                    FN += 1
            elif(bufferTarget[x] == 0):
                if(majority == 1):
                    FP += 1
                else:
                    TN += 1    
            try:
                precision = round(TP/(TP + FP), 4) * 100  # given a positive prediction from the classifier: how likely is it to be correct?
                recall = round(TP/(TP + FN), 4) * 100     # given a positive example, how likely will the classifier correctly detect it?
                F1score = 2 * (precision * recall) / (precision + recall)
            except:
                pass


    
    return (precision, recall, F1score)

