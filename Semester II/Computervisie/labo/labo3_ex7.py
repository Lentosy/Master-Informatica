import cv2
from Modules import optcheck, highgui, imgproc
#rainbowdiscs.png
imagePath = optcheck.getArguments()[0]
image = highgui.openImage(imagePath)

D = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 5))
dilation = cv2.dilate(image, D, iterations = 3)
E = cv2.getStructuringElement(cv2.MORPH_RECT , (3, 3))
erosion = cv2.erode(dilation, E, iterations = 3)

highgui.showImagesHorizontally("EX7", image, dilation, erosion)


highgui.saveImage(erosion, highgui.getSavePath(imagePath, '7EROSION'))
highgui.saveImage(dilation, highgui.getSavePath(imagePath, '7DILATION'))




