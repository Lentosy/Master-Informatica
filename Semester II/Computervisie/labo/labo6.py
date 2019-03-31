#
# 1. The image gets subdivided into 16 x 16 blocks
#
#        <--  16 px --> 
#    ▲   .____________.  .____________.  .____________.  .____________.  
#    |   |            |  |            |  |            |  |            | 
#    16  |            |  |            |  |            |  |            | 
#    px  |            |  |            |  |            |  |            |   .......... 
#    |   |            |  |            |  |            |  |            | 
#    ▼   |____________|  |____________|  |____________|  |____________| 
#        
#        .____________.  .____________.  .____________.  .____________.  
#        |            |  |            |  |            |  |            | 
#        |            |  |            |  |            |  |            | 
#        |            |  |            |  |            |  |            |   .......... 
#        |            |  |            |  |            |  |            | 
#        |____________|  |____________|  |____________|  |____________| 
#              
#              .               .                .              .
#              .               .                .              .
#              .               .                .              .
#              .               .                .              .
#              .               .                .              .
#
# 2. Each subdivision gets a feature vector consisting of 12 features. The feature values are determined by various DoG filters
#
#        .____________.  
#        |            |
#        |            |
#        |            |  -> [f1 | f2 | f3 | ... | f11 | f12]
#        |            | 
#        |____________|
#
# 
# 3. These feature vectors get passed along to a Random Forest Classifier for training and predicting
#
#
import cv2
import numpy
import math
import matplotlib.pyplot as plt
from collections import namedtuple
from sklearn.ensemble import RandomForestClassifier
from Modules import optcheck, highgui, imgproc

ANGLES = range(0, 180, 30)  # the different angles for the DoG filters
BLOCK_STEP_SIZE = 16
IMAGES = [f'Images\\road{x}' for x in range(1, 4 + 1)]  # the path to the road images, without extension (1 to 4 inclusive) 


def getFeatureVectors(image):
    """ Returns a two dimensional list where each element is a list of 12 features. 
    Such a list corresponds to the feature vector of a given block.
    Iterating this list gives the blocks from top left to bottom right order
    """
    # construct the 12 DoG Filters
    DoGFilters = []
    for angle in ANGLES:  # angle = [0, 30, 60, 90, 120, 150]
        DoGFilters.append(imgproc.getDoGFilter(size=75, sigmabig=25,
                                               sigmasmall=1, angle=angle))
        DoGFilters.append(imgproc.getDoGFilter(size=25, sigmabig=5,
                                               sigmasmall=1, angle=angle))


    # Get the responses when filtering the image with each of the 12 DoGFilters
    responses = []
    for DoGFilter in DoGFilters:
        responses.extend(
            [cv2.filter2D(src=image, ddepth=-1, kernel=DoGFilter)]
        )

    # build up the feature vector for each 16 x 16 block. The concatenation of the
    # feature vectors of the blocks becomes the feature vector of the image
    (height, width) = (image.shape)[0:2]
    featureVectors = [] 
    for i in range(0, height, BLOCK_STEP_SIZE):
        for j in range(0, width, BLOCK_STEP_SIZE):
            featureVectorBlock = [] # the feature vector of each block contains 12 values (one for each filter)
            for response in responses:
                # gather the 16 x 16 block
                block = response[i:i + BLOCK_STEP_SIZE, j:j + BLOCK_STEP_SIZE]
                # get the maximum response value of this block
                featureVectorBlock.append(numpy.amax(block))
            featureVectors.extend([featureVectorBlock])
    return featureVectors


def getRoadMarkings(image):
    """
    returns a one dimensional list indicating wether or not a pixel is a
    roadmarking (1) or not (0).
    """
    (height, width) = (image.shape)[0:2]
    roadmarkings = []
    for i in range(0, height, BLOCK_STEP_SIZE):
        for j in range(0, width, BLOCK_STEP_SIZE):
            # check if the maximum value of a 16 x 16 block equals to 255 (a white pixel)
            # the result of that boolean expression gives either 1 or 0, indicating a road marker or not
            roadmarkings.append(numpy.amax(image[i:i + BLOCK_STEP_SIZE, j:j + BLOCK_STEP_SIZE]) == 255)
    return roadmarkings


def visualizeMeans(features, roadmarkings):
    """
    Compares the mean values of each feature for blocks containing road
    markings and blocks containing no road markings.
    
    The features parameter should contain the 880 

    """

    values_per_filter_road = [[] for i in range(0, 12)]
    values_per_filter_non_road = [[] for i in range(0, 12)]

    for i in range(0, len(roadmarkings)):
        feature_vector = features[i]
        for j in range(0, len(feature_vector)):
            if(roadmarkings[i]): # 16 x 16 block is white
                values_per_filter_road[j].append(feature_vector[j])
            else:
                values_per_filter_non_road[j].append(feature_vector[j])

    mean_values_per_filter_road = []
    mean_values_per_filter_non_road = []

    for i in range(0, 12):
        mean_values_per_filter_road.append(numpy.average(values_per_filter_road[i]))
        mean_values_per_filter_non_road.append(numpy.average(values_per_filter_non_road[i]))

    plt.plot(mean_values_per_filter_road, label = "road mark blocks")
    plt.plot(mean_values_per_filter_non_road, label = "non-road mark blocks")
    plt.legend()
    plt.xlabel("filter index")
    plt.ylabel("mean of maximal response per block")
    plt.show()


def getOverlayedImage(image, predictions):
    """
    This function draws rectangles for each 16 x 16 block which the classifier
    thinks contains a road marking.
    """
    alpha = 0.5
    (heightOrigImage, widthOrigImage) = (image.shape)[0 : 2]
    predictionImage = numpy.zeros((heightOrigImage, widthOrigImage, 3), numpy.uint8)

    width = (image.shape[1]) / BLOCK_STEP_SIZE
    for i in range(0, len(predictions)):
        hasRoadMarking = predictions[i]
        if(hasRoadMarking):
            column = int(i % width)
            row = int(i // width)
            point1 = (column * BLOCK_STEP_SIZE, row * BLOCK_STEP_SIZE)
            point2 = (column * BLOCK_STEP_SIZE + BLOCK_STEP_SIZE, row * BLOCK_STEP_SIZE + BLOCK_STEP_SIZE)
            cv2.rectangle(img=predictionImage, pt1=point1, pt2=point2, color=(255, 255, 255), thickness=-1)
    
    cv2.addWeighted(src1=image, alpha=alpha,
                    src2=predictionImage,
                    beta=1-alpha, gamma=0,
                    dst=predictionImage)

    return predictionImage
    



def balanceTrainingset(features, labels):
    """
    Balances the trainingset so that it contains an equal amount of white and black blocks.
    """
    newFeatures = []
    newLabels = []
    nextMarker = 0 # change between adding a black block and a white block, so we get an equal amount of each at the end
    for i in range(0, len(labels)):
        if(labels[i] == nextMarker):
            newFeatures.extend([features[i]])
            newLabels.append(labels[i])
        nextMarker = (nextMarker + 1) % 2
    return newFeatures, newLabels


def evaluateClassifierPerformance(classifier):

    # apply 4-fold cross validation: image with index i will be used as testdata, the other images as trainingdata
    for i in range(1, len(IMAGES) + 1):
        trainingSet = IMAGES[:i - 1] + IMAGES[i:]
        testImage = IMAGES[i - 1]

        featureSet = []
        labelSet = []

        for imagePath in trainingSet:
            image = highgui.openImage(f"{imagePath}.png")
            image_blocks = highgui.openImage(f"{imagePath}_blocks.png")
            features = getFeatureVectors(image)
            labels = getRoadMarkings(image_blocks)
            (features, labels) = balanceTrainingset(features, labels)
            featureSet.extend(features)
            labelSet.extend(labels)
            
        classifier.fit(featureSet, labelSet)
        image = highgui.openImage(f"{testImage}.png") 
        image_blocks = highgui.openImage(f"{testImage}_blocks.png") 
        predictions = classifier.predict(getFeatureVectors(image))
        groundTruth = getRoadMarkings(image_blocks) 
        predictionImage = getOverlayedImage(image, predictions)
        highgui.saveImage(predictionImage, highgui.getSavePath(f"{testImage}.png", 'CLASSIFIER'))

        TP, FP, FN, TN = (0, 0, 0, 0)
        print(f"recall and precision considering {trainingSet} as the training data and {testImage} as the test data")
        for prediction, groundTruth in zip(predictions, groundTruth):
            if(groundTruth == 1):
                if(prediction == 1):
                    TP += 1
                else:
                    FN += 1
            elif(groundTruth == 0):
                if(prediction == 1):
                    FP += 1
                else:
                    TN += 1

        precision = TP/(TP + FP)  # given a positive prediction from the classifier, how likely is it to be correct?
        recall = TP/(TP + FN)     # given a positive example, will the classifier detect it?

        print(f"Precision: {round(precision, 4) * 100} \t Recall: {round(recall, 4) * 100}")

def main():
    randomForestClassifier = RandomForestClassifier(n_estimators=10)    
    evaluateClassifierPerformance(randomForestClassifier)

if __name__ == '__main__':
    main()