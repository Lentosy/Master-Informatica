import pandas as pd
PATH = "data\\BERT\\EMERGENCY_STOP\\joints.txt"
joints = pd.read_csv(PATH, header = None, sep = ';')

spine_info = joints[joints.columns[0:3]]
print(spine_info)
