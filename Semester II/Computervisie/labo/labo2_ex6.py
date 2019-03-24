import cv2
import sys
import os.path   
import numpy
from Modules import optcheck, highgui, imgproc

#blots.png
fullPath = optcheck.getArguments()[0]
filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)

image = cv2.imread(fullPath)

size = 15
kernel = numpy.zeros((size, size)) # de matrix zal de figuur uitsmeren naar rechtsonder
for i in range(0, 7):
    kernel[i][i] = 1/7

filteredImage = cv2.imread(fullPath)
cv2.filter2D(image, -1, kernel, filteredImage, (size - 1, size - 1))

highgui.showImagesHorizontally(filename, image, filteredImage)

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX6." + extension
highgui.saveImage(filteredImage, savePath)

