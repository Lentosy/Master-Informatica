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
cv2.imshow(filename, image)

#https://docs.opencv.org/4.0.1/da/d54/group__imgproc__transform.html#ga20f62aa3235d869c9956436c870893ae

#https://docs.opencv.org/4.0.1/da/d54/group__imgproc__transform.html#gaf73673a7e8e18ec6963e3774e6a94b87
def warp(event, x, y, flags, userdata):
    if(cv2.EVENT_LBUTTONUP == event):
        print("Clicked (" + str(x) + ", " + str(y) + ") [ " + str(flags) + " ]")

cv2.setMouseCallback(filename,warp)
cv2.waitKey()

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX8." + extension
print("Saving as: " + savePath)
cv2.imwrite(savePath, image)
