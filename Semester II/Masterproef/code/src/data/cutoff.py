import cv2
import os
import re 



def rewrite(path, newnum):
    image = cv2.imread(path)
    newPath = path.split('frame')[0] + f"frame{newnum}.jpg"
    print(path , '->', newPath)
    cv2.imwrite(newPath, image)
    os.remove(path)   

p = re.compile('frame(\d*)')
offset = 30
for root, subdirs, files in os.walk(os.path.split(os.path.realpath(__file__))[0] + "\\BERT"):
    for file in sorted(files):
        match = p.search(file)
        number = int(match.group(1))
        rewrite(f"{root}\\{file}", number - offset)

            
            