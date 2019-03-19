import cv2
import sys
import os
from Modules import optcheck, highgui

#whitenoise.png
fullPath = optcheck.getArgument(sys.argv)
filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)

image = cv2.imread(fullPath)

gaussianBlurredImage = cv2.GaussianBlur(image, (5, 5), 3)
highgui.showImagesHorizontally(filename, image, gaussianBlurredImage)


filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX2." + extension
highgui.saveImage(gaussianBlurredImage, savePath)