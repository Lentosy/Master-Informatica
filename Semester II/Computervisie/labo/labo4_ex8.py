import cv2
import numpy
from Modules import optcheck, highgui, imgproc

#shadow.png
imagepath = optcheck.getArguments()[0]
image = highgui.openImage(imagepath)

shear_factor = -0.2
M = numpy.float32([[1, shear_factor, 50], [0, 1, 0]])
shearImage = cv2.warpAffine(image, M, (-1, -1))

highgui.showImagesHorizontally("Shearing", image, shearImage)
highgui.saveImage(shearImage, highgui.getSavePath(imagepath, '8'))
