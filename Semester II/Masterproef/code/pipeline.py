from sklearn.pipeline import Pipeline
from sklearn import svm
import csv

class Action:
    def __init__(self, target, data):
        self.target = target
        self.data = data

action = Action('RH_MOVE_FORWARD' , [])
with open('data\BERT_RH_MOVE_FORWARD_1.txt', 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter=';')
    for row in reader:
        action.data.extend([row])
        break


clf = svm.SVC(gamma=0.001, C = 100)

    
