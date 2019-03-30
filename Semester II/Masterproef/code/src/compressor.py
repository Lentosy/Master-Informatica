import cv2
import os

DIR = "data"

def compress(path):
    image = cv2.imread(path)
    newPath = path.split('.')[0] + ".jpg"
    cv2.imwrite(newPath, image)
    os.remove(path)    



for root, subdirs, files in os.walk(DIR):
    for file in files:
        if(file.endswith(".bmp")):
            print(f"Compressing {file}")
            compress(f"{root}\\{file}")