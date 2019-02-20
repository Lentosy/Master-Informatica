import cv2
import sys
import os.path   
import numpy

#blots.png
try:
    fullPath = sys.argv[1]
except IndexError:
    print("One parameter required: the path of an image.")
    exit(1)

if (not os.path.isfile(fullPath)):
    print("'" + fullPath + "' is not an existing file.")
    exit(2)

filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)

image = cv2.imread(fullPath)


matrix = numpy.zeros((15, 15)) # de matrix zal de figuur uitsmeren naar rechtsonder
for i in range(0, 7):
    matrix[i][i] = 1/7

filteredImage = cv2.imread(fullPath)
cv2.filter2D(image, -1, matrix, filteredImage, (14, 14))
result = cv2.hconcat((image, filteredImage))
cv2.imshow(filename, result)
cv2.waitKey()


filename, extension = filename.split(".")
cv2.imwrite(filepath + "\\" + filename + "EX6." + extension, filteredImage)
