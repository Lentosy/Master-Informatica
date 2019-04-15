def perFrameClassification(trainingset, validationset, classifier):
    """
    This is the simplest method as it classifies each frame individually.
    """
    classifier.fit(trainingset.data, trainingset.target)
    res = classifier.predict(validationset.data)
    precision, recall, F1score = (0, 0, 0)
    TP, FP, FN, TN = (0, 0, 0, 0)
    for i in range(0, len(res)):
        if(validationset.target[i] == 1):
            if(res[i] == 1):
                TP += 1
            else:
                FN += 1
        elif(validationset.target[i] == 0):
            if(res[i] == 1):
                FP += 1
            else:
                TN += 1    
        try:
            precision = round(TP/(TP + FP), 4) * 100 # given a positive prediction from the classifier: how likely is it to be correct?
            recall = round(TP/(TP + FN), 4) * 100    # given a positive example, how likely will the classifier correctly detect it?
            F1score = 2 * (precision * recall) / (precision + recall)
        except:
            pass
    return (precision, recall, F1score)



def simpleBufferClassification(trainingset, validationset, classifier):
    classifier.fit(trainingset.data, trainingset.target)
    for i in range(0, len(validationset), 30):
        frames = []
        for j in range(i, i + 30):
            frames.append(validationset.target[j])
        

    
