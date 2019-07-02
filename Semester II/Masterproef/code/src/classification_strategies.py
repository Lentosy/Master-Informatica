from constants import ACTIONS
from sklearn.metrics import recall_score, precision_score, f1_score, classification_report


class ClassificationStrategy(object):
    """
    A classification strategy implements a classification method. This strategy is independent of the chosen features.
    To evaluate the classifier, it's precision, recall and F1score are calculated. First, a list of precisions and recalls
    are generated from the confusion matrix for each action. The average precision, recall and f1score is then calculated for 
    the global performance of the classifier.
    """
    def __init__(self):
        self.report = {}
    
    def __str__(self):
        raise NotImplementedError("This is an abstract method. Implement this in a subclass")

    def getStatistics(self):
        """
        Returns the classifier report
        """
        return self.report

    def perform(self, validationset, classifier):
        raise NotImplementedError("This is an abstract method, implement this in a subclass.")




class PerFrameClassification(ClassificationStrategy):
    """
    This is the simplest method as it classifies each frame individually.
    """ 

    def __init__(self):
        ClassificationStrategy.__init__(self)

    def __str__(self):
        return "PerFrameClassification"


    def perform(self, validationset, classifier):
        predictions = classifier.predict(validationset.data)
        print(set(validationset.target) - set(predictions))
        self.report = classification_report(validationset.target, predictions, target_names=ACTIONS, digits=4, output_dict=True)
    




class SimpleBufferClassification(ClassificationStrategy):
    """
    This classification strategy forms groups of 30 frames in a buffer. The majority action gets calculated incrementally for each frame in this buffer.

    """
    def __init__(self, buffersize):
        ClassificationStrategy.__init__(self)
        self.bufferSize = buffersize

    def __str__(self):
        return f"SimpleBufferClassification (buffer={self.bufferSize})"

    def perform(self, validationset, classifier):

        iterations = (len(validationset) // self.bufferSize) # We need iterations to group frames by 'bufferSize' amount
        predictions = [] # the list of all the predictions
        
        for currentIteration in range(0, iterations): # one iteration holds 'bufferSize' frames
            bufferData =  [validationset.data[j] for j in range(currentIteration*self.bufferSize, (currentIteration+1)*self.bufferSize)]
            bufferPred = classifier.predict(bufferData)
            vote = self._getMajorityVote(bufferPred)
            for _ in range(0, self.bufferSize):
                predictions.append(vote)

        # last iteration, with less than 'bufferSize' frames
        if len(validationset) % self.bufferSize != 0:
            bufferData = [validationset.data[j] for j in range(iterations * self.bufferSize, len(validationset))]
            bufferPred = classifier.predict(bufferData)
            vote = self._getMajorityVote(bufferPred)
            for _ in range(0, len(bufferData)):
                predictions.append(vote)
        print(set(validationset.target) - set(predictions))
        self.report = classification_report(validationset.target, predictions, target_names=ACTIONS, digits=4, output_dict=True)




    def _getMajorityVote(self, predictions):
        frequency = dict(zip([i for i in range(len(ACTIONS))], [0 for i in range(len(ACTIONS))]))
        for prediction in predictions:
            frequency[max(0, prediction)] += 1 # sometimes the classifier returns 'unknown', or '-1' In that case we map those to 0.
        (maxKey, maxVal) = (-1, -1) #
        for (key, val) in iter(frequency.items()):
            if(val > maxVal):
                maxVal = val
                maxKey = key
        return maxKey

class WeightedBufferClassification(ClassificationStrategy):
    def __init__(self, buffersize):
        ClassificationStrategy.__init__(self)
        self.bufferSize = buffersize

    def __str__(self):
        return "WeightedBufferClassification"


    def perform(self, validationset, classifier):
        iterations = (len(validationset) // self.bufferSize) # We need iterations to group frames by 'bufferSize' amount
        predictions = [] # the list of all the predictions
        
        for currentIteration in range(0, iterations): # one iteration holds 'bufferSize' frames
            bufferData =  [validationset.data[j] for j in range(currentIteration*self.bufferSize, (currentIteration+1)*self.bufferSize)]
            bufferPred = classifier.predict(bufferData)
            vote = self._getWeightedVote(bufferPred)
            for _ in range(0, self.bufferSize):
                predictions.append(vote)

        # last iteration, with less than 'bufferSize' frames
        if len(validationset) % self.bufferSize != 0:
            bufferData = [validationset.data[j] for j in range(iterations * self.bufferSize, len(validationset))]
            bufferPred = classifier.predict(bufferData)
            vote = self._getWeightedVote(bufferPred)
            for _ in range(0, len(bufferData)):
                predictions.append(vote)
        print(set(validationset.target) - set(predictions))
        self.report = classification_report(validationset.target, predictions, target_names=ACTIONS, digits=4, output_dict=True)


    def _getWeightedVote(self, predictions):
        frequency = dict(zip([i for i in range(len(ACTIONS))], [0 for i in range(len(ACTIONS))]))
        for i in range(0, len(predictions)):
            frequency[max(0, predictions[i])] += 1 + i/2

        (maxKey, maxVal) = (-1, -1) #
        for (key, val) in iter(frequency.items()):
            if(val > maxVal):
                maxVal = val
                maxKey = key
        return maxKey   
