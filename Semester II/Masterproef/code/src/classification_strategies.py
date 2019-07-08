from domain.constants import ACTIONS
from sklearn.metrics import recall_score, precision_score, f1_score, classification_report, confusion_matrix


class ClassificationStrategy(object):
    """
    A classification strategy implements a classification method. This strategy is independent of the chosen features.
    To evaluate the classifier, it's precision, recall and f1-score are calculated. First, a list of precisions and recalls
    are generated from the confusion matrix for each action. The average precision, recall and f1score is then calculated for 
    the global performance of the classifier.
    """
    def __init__(self):
        self.report = None
    
    def __str__(self):
        raise NotImplementedError("This is an abstract method. Implement this in a subclass")

    def getStatistics(self):
        """
        Returns the classifier report
        """
        return self.report

    def getConfusionMatrix(self):
        return self.confusion_matrix

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
        self.confusion_matrix = confusion_matrix(validationset.target, predictions)
    


class SlidingWindowClassification(ClassificationStrategy):
    """
    This classification strategy forms groups of 30 frames in a buffer. The majority action gets calculated incrementally for each frame in this buffer.
    """
    def __init__(self, buffersize):
        ClassificationStrategy.__init__(self)
        self.buffersize = buffersize

    def __str__(self):
        return f"SimpleBufferClassification (buffer={self.buffersize})"

    def perform(self, validationset, classifier):
        predictions = [] # the list of all the predictions

        for i in range(0, len(validationset) - self.buffersize):
            buffer_data = [validationset.data[j] for j in range(i, i + self.buffersize)]
            buffer_pred = classifier.predict(buffer_data)
            vote = self._getMajorityVote(buffer_pred)
            predictions.append(vote)
        self.report = classification_report(validationset.target[:len(validationset) - self.buffersize], predictions, target_names=ACTIONS, digits=4, output_dict=True)
        self.confusion_matrix = confusion_matrix(validationset.target[:len(validationset) - self.buffersize], predictions)

    def _getMajorityVote(self, buffer):
        frequency = dict(zip([i for i in range(len(ACTIONS))], [0 for i in range(len(ACTIONS))]))
        for prediction in buffer:
            frequency[max(0, prediction)] += 1 # sometimes the classifier returns 'unknown', or '-1' In that case we map those to 0.
        (maxKey, maxVal) = (-1, -1) #
        for (key, val) in iter(frequency.items()):
            if(val > maxVal):
                maxVal = val
                maxKey = key
        return maxKey