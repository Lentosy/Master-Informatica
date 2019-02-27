import cv2
import sys
import os.path
import numpy

#shadow.png
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

shear_factor = -0.2
M = numpy.float32([[1, shear_factor, 50], [0, 1, 0]])
shearImage = cv2.warpAffine(image, M, (-1, -1))
result = cv2.hconcat((image, shearImage))
cv2.imshow(filename, result)
cv2.waitKey()

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX8." + extension
print("Saving as: " + savePath)
cv2.imwrite(savePath, shearImage)
