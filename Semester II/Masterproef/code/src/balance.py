

import csv
import pandas
from sklearn.feature_selection import VarianceThreshold
from transform_features import FeatureTransformer
from constants import ACTIONS, PERSONS



frequency = {
    0: 0,
    1: 0,
    2: 0,
    3: 0,
    4: 0,
    6: 0,
    7: 0,
    9: 0,
    10: 0,
    11: 0
}


for person in PERSONS:
    for action in ACTIONS:
        folder = f"..\\data\\{person}\\{action}"
        try:
            with open(f"{folder}\\labels.txt") as labels:
                csvReader = csv.reader(labels, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
                for row in csvReader:
                    frequency[max(0, int(row[0]))] += 1
        except FileNotFoundError as fnfe:
            pass
            #sys.stdout.write(str(fnfe) + "\n")

minVal = min(frequency.values())

toDelete = dict((key, 0) for key in frequency.keys())

for key in frequency.keys():
    toDelete[key] = frequency[key] - minVal

print(frequency, toDelete, sep = '\n')


# ?? ?? ?? 