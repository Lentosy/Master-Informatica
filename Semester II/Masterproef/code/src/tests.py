from sklearn.metrics import classification_report
from sklearn.metrics import accuracy_score
from domain.constants import ACTIONS
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.lines as lines 
y_true = [0, 1, 2, 2, 2]
y_pred = [0, 0, 2, 2, 1]
target_names = [ACTIONS[2], ACTIONS[5], ACTIONS[9]]
report = classification_report(y_true, y_pred, target_names=target_names, digits=4, output_dict=True)

y_pos = np.arange(len(target_names))

precision = [report[key]['precision'] for key in target_names]
recall = [report[key]['recall'] for key in target_names]
f1score = [report[key]['f1-score'] for key in target_names]




n_groups = len(target_names)
fig, ax = plt.subplots()
index = np.arange(n_groups)
bar_width=0.35
opacity=0.8



ax.bar(index + 1/2 * bar_width, precision, bar_width, alpha=0.5, label='precision', color='b')
ax.bar(index + 3/2 * bar_width, recall, bar_width, alpha=0.5, label='recall', color='g')
ax.plot(index +  bar_width, f1score, '-o', color='red')
plt.xticks(index + bar_width, target_names)
plt.yticks(ticks=[0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0])

plt.title('Precision, recall and f1-scores per human gesture')
plt.xlabel('Gesture label')
plt.ylabel('Score')

plt.legend()
plt.tight_layout()
plt.show()


