import cv2
import sys
import os.path   
from Modules import highgui, imgproc, optcheck

#building.png
fullPath = optcheck.getArgument(sys.argv)
filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)

image = cv2.imread(fullPath)

grayScaleImage = imgproc.convertToGrayscale(image)

sobelImage = cv2.Sobel(grayScaleImage, -1, 0, 1)
highgui.showImagesHorizontally(filename, grayScaleImage, sobelImage)

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX5." + extension
highgui.saveImage(sobelImage, savePath)
