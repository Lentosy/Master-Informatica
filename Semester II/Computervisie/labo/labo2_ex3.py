import cv2
import sys
import os.path
from Modules import highgui, imgproc, optcheck
# unsharp.png

fullPath = optcheck.getArguments()[0]
filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)

image = cv2.imread(fullPath)
unsharpImage = imgproc.unsharpMasking(image, 19)

highgui.showImagesHorizontally(filename, image, unsharpImage)

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX3." + extension
highgui.saveImage(unsharpImage, savePath)


