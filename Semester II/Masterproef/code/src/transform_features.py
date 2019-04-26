import csv


def transform_features(path):
    info = []
    with open(path) as dataFile:
        csvReader = csv.reader(dataFile, delimiter=';')
        for row in csvReader:
            spine_x = float(row[0])
            spine_y = float(row[1])
            spine_z = float(row[2])
            dat = []
            for i in range(0, 75, 3):
                dat.append(float(row[i + 0]) - spine_x)
                dat.append(float(row[i + 1]) - spine_y)
                dat.append(float(row[i + 2]) - spine_z)
            for i in range(75, len(row)):
                dat.append(float(row[i]))
            info.extend([dat])
    return info

