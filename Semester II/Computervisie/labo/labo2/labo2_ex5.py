import cv2
import sys
import os.path   

#building.png
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

grayScaleImage = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

sobelImage = cv2.Sobel(grayScaleImage, -1, 0, 1)
#result = cv2.hconcat((image, sobelImage))
cv2.imshow(filename, sobelImage)
cv2.waitKey()

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX5." + extension
print("Saving as: " + savePath)
cv2.imwrite(savePath, sobelImage)
