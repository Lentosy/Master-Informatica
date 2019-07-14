from math import sqrt
from domain.constants import ACTIONS, JOINTS
from sklearn.metrics import recall_score, precision_score, f1_score, classification_report, confusion_matrix


class VotingStrategy(object):
    def getVote(self, buffer):
        raise NotImplementedError("This is an abstract method. Implement this in a subclass")


class MajorityVote(VotingStrategy):
    def getVote(self, buffer):
        frequency = dict(zip([i for i in range(len(ACTIONS))], [0 for i in range(len(ACTIONS))]))
        for prediction in buffer:
            frequency[max(0, prediction)] += 1 # sometimes the classifier returns 'unknown', or '-1' In that case we map those to 0.
        (maxKey, maxVal) = (-1, -1) #
        for (key, val) in iter(frequency.items()):
            if(val > maxVal):
                maxVal = val
                maxKey = key
        return maxKey


class ClassificationStrategy(object):
    """
    A classification strategy implements a classification method. This strategy is independent of the chosen features.
    To evaluate the classifier, it's precision, recall and f1-score are calculated. First, a list of precisions and recalls
    are generated from the confusion matrix for each action. The average precision, recall and f1score is then calculated for 
    the global performance of the classifier.
    """
    def __init__(self):
        self.report = None
        self.confusionMatrix = None
    
    def __str__(self):
        raise NotImplementedError("This is an abstract method. Implement this in a subclass")

    def perform(self, testingset, classifier):
        raise NotImplementedError("This is an abstract method, implement this in a subclass.")





class PerFrameClassification(ClassificationStrategy):
    """
    This is the simplest method as it classifies each frame individually.
    """ 

    def __init__(self):
        ClassificationStrategy.__init__(self)

    def __str__(self):
        return "PerFrameClassification"


    def perform(self, testingset, classifier):
        predictions = []
        for i in range(0, len(testingset)): #simulate video recording by iterating each frame
            predictions.extend(classifier.predict([testingset.data[i]]))
        self.report = classification_report(testingset.target, predictions, target_names=ACTIONS, digits=4, output_dict=True)
        self.confusionMatrix = confusion_matrix(testingset.target, predictions)
    


class SlidingWindowClassification(ClassificationStrategy):
    """
    This classification strategy forms groups of 30 frames in a buffer. The majority action gets calculated incrementally for each frame in this buffer.
    """
    def __init__(self, buffersize):
        ClassificationStrategy.__init__(self)
        self.buffersize = buffersize
        self.votingStrategy = MajorityVote()

    def __str__(self):
        return f"SimpleBufferClassification (buffer={self.buffersize})"

    def perform(self, testingset, classifier):
        predictions = [] # the list of all the predictions

        for i in range(0, len(testingset) - self.buffersize):
            bufferData = [testingset.data[j] for j in range(i, i + self.buffersize)]
            bufferPred = classifier.predict(bufferData)
            vote = self.votingStrategy.getVote(bufferPred)
            predictions.append(vote)
        self.report = classification_report(testingset.target[:len(testingset) - self.buffersize], predictions, target_names=ACTIONS, digits=4, output_dict=True)
        self.confusionMatrix = confusion_matrix(testingset.target[:len(testingset) - self.buffersize], predictions)




class EnergyBasedSegmentationClassification(ClassificationStrategy):
    """
    This classification strategy segmentates action based on relative velocity on consecutive frames. A high change in velocity likely indicates a new action being performed.
    """
    def __init__(self, threshold):
        ClassificationStrategy.__init__(self)
        self.threshold = threshold
        self.votingStrategy = MajorityVote()
        self.buffersize = 10

    def __str__(self):
        return f"EnergyBasedSegmentationClassification"

    def perform(self, testingset, classifier):
        
        predictions = [0] # first frame has no relative energy
        segment = []
        actionStarted = False

        for i in range(1, len(testingset)):
            totalKineticEnergy = 0
            for joint_index in range(0, len(JOINTS)):
                #calculate velocity components
                velX = testingset.data[i - 1][3*joint_index] - testingset.data[i][3*joint_index]
                velY = testingset.data[i - 1][3*joint_index+1] - testingset.data[i][3*joint_index+1]
                velZ = testingset.data[i - 1][3*joint_index+2] - testingset.data[i][3*joint_index+2]
                #magnitude of velocity
                velocity = sqrt(velX * velX + velY * velY + velZ * velZ)
                totalKineticEnergy += JOINTS[joint_index]['weight'] * velocity * velocity # E = mv^2
            
            # The 1/2 can be factored out of the sum
            totalKineticEnergy *= 0.5
            print(i, totalKineticEnergy, end ='    ')
            if actionStarted == False:
                if totalKineticEnergy < self.threshold:
                    print("default action")
                    predictions.extend(classifier.predict([testingset.data[i]]))
                elif totalKineticEnergy >= self.threshold:
                    print("start action")
                    actionStarted = True
                    segment = [testingset.data[i]]
            elif actionStarted == True:
                segment.append(testingset.data[i]) 
                if totalKineticEnergy >= self.threshold:
                    print("add frame to segment")
                elif totalKineticEnergy < self.threshold:
                    print("stop action")
                    actionStarted = False
                    if len(segment):
                        classificationbuffer = classifier.predict(segment)
                        vote = self.votingStrategy.getVote(classificationbuffer)
                        predictions.extend([vote] * len(segment))
                    segment = []

        if len(segment):

            classificationbuffer = classifier.predict(segment)
            vote = self.votingStrategy.getVote(classificationbuffer)
            predictions.extend([vote] * len(segment))

        self.report = classification_report(testingset.target, predictions, target_names=ACTIONS, digits=4, output_dict=True)
        self.confusionMatrix = confusion_matrix(testingset.target, predictions)