import cv2
import sys
import os.path
import numpy

#rainbowdiscs.png
try:
    fullPath = sys.argv[1]
except IndexError:
    print("One parameter required: the path of an image.")
    exit(-1)

if (not os.path.isfile(fullPath)):
    print("'" + fullPath + "' is not an existing file.")
    exit(-1)

filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)
image = cv2.imread(fullPath)

D = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 5))
dilation = cv2.dilate(image, D, iterations = 3)
E = cv2.getStructuringElement(cv2.MORPH_RECT , (3, 3))
erosion = cv2.erode(dilation, E, iterations = 3)

result = cv2.hconcat((image, dilation, erosion))
cv2.imshow(filename, result)
cv2.waitKey()



filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX7EROSION." + extension
print("Saving as: " + savePath)
cv2.imwrite(savePath, erosion)
savePath = filepath + "\\" + filename + "EX7DILATATION." + extension
print("Saving as: " + savePath)
cv2.imwrite(savePath, dilation)