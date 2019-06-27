

import csv
import pandas
from sklearn.feature_selection import VarianceThreshold
from transform_features import FeatureTransformer
from constants import ACTIONS, PERSONS

unused_actions = [5, 8, 12] # indices of unused actions
frequency = {}

for person in PERSONS:
    frequency[person] = {}
    i = 0
    for action in ACTIONS:
        frequency[person][i] = 0
        if i in unused_actions:
            del frequency[person][i]
        i += 1


for person in PERSONS:
    for action in ACTIONS:
        folder = f"..\\data_c\\{person}\\{action}"
        try:
            with open(f"{folder}\\labels.txt") as labels:
                csvReader = csv.reader(labels, delimiter=';', quoting=csv.QUOTE_NONNUMERIC)
                for row in csvReader:
                    frequency[person][max(0, int(row[0]))] += 1
        except FileNotFoundError as fnfe:
            pass



minval = frequency['BERT'][0]
for person in frequency.keys():
    if min(frequency[person].values()) < minval:
        minval = min(frequency[person].values())

toDelete = frequency.copy()
for person in toDelete.keys():
    for action in toDelete[person].keys():
        toDelete[person][action] -= minval

print(frequency)
print(toDelete)

# EERST UITTESTEN OP KOPIE
# voor elke persoon
#   overloop elk joints.txt en labels.txt bestand
#   verwijder lijn als er nog een instantie verwijderd moet worden voor die persoon
#   decrementeer aantal te verwijderen instanties voor die persoon en die klasse



for person in PERSONS:
    for action in ACTIONS:

        folder = f"..\\data_c\\{person}\\{action}"
        try:
            labels = None
            joints = None
            with open(f"{folder}\\labels.txt", 'r') as f:
                labels = f.readlines()
            with open(f"{folder}\\joints.txt", 'r') as f:
                joints = f.readlines()
            
            for label in labels:
                label = label.strip('\n')
                frequency[person][label] -= 1

        except Exception:
            pass