
from pandas import read_csv
from matplotlib import pyplot

def load_dataset():
    df = read_csv("data/BERT_RH_MOVE_FORWARD_1.txt", header=None, sep = ';')
    plot_subject(df)

def plot_subject(subject):
    pyplot.figure()
    for col in range(0, 25, 3):
        pyplot.subplot(subject.shape[1], 1, subject[col])
        pyplot.subplot(subject.shape[1], 1, subject[col+1])
        pyplot.subplot(subject.shape[1], 1, subject[col+2])

    pyplot.show()

load_dataset()