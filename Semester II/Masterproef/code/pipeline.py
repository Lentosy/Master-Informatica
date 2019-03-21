from sklearn import datasets, svm
import pandas as pd
import constants

class Dataset():
    data = []
    target = []

def load_trainingset():
    trainingset = Dataset() # trainingset is a n * k matrix with n = # samples (frames) and k = # features (175)
    for i in range(0, len(constants.ACTIONS)):
        for j in range(1, 10):
            try:
                df = pd.read_csv(FOLDER + f"{constants.PERSONS[0]}_{constants.ACTIONS[i]}_{j}.txt", header = None, sep = ';')
                trainingset.target.extend(df.iloc[:][175].values)
                trainingset.data.extend(df.iloc[:][range(0, 175)].values)
            except FileNotFoundError as fnfe:
                print(fnfe)
    return trainingset

def load_validationset():
    validationset = Dataset()
    i = 10
    df = pd.read_csv(FOLDER + f"{constants.PERSONS[0]}_{constants.ACTIONS[9]}_{i}.txt", header = None, sep = ';')
    validationset.data.extend(df.iloc[:][range(0, 175)].values)    

    return validationset


FOLDER = "data/"

trainingset = load_trainingset()
validationset = load_validationset()

clf = svm.SVC(gamma = 0.001, C = 100.)
clf.fit(trainingset.data, trainingset.target)
print(clf.predict(validationset.data))
