import cv2
import sys
import os.path   
from Modules import optcheck, highgui

#saltandpeppernoise.png

fullPath = optcheck.getArguments()[0]
filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)

image = cv2.imread(fullPath)
medianBlurredImage = cv2.medianBlur(image, 3)
highgui.showImagesHorizontally(filename, image, medianBlurredImage)


filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX4." + extension
highgui.saveImage(medianBlurredImage, savePath)