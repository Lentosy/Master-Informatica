import cv2
import sys
from Modules import imgproc, highgui, optcheck

filePath = optcheck.getArgument(sys.argv)
path, extension = filePath.split(".") # seperate path and extension:  [/path/to/file].[extension]
cv2.namedWindow(path)

# DEFAULT
defaultImage = cv2.imread(filePath)
highgui.showImage(path, defaultImage)


# GRAYSCALE
print("Converting to grayscale")
grayScaleImage = imgproc.convertToGrayscale(defaultImage)
highgui.showImage(path, grayScaleImage)

# THRESHOLD
print("Thresholding the grayscale image at 50% of the maximum intensity")
thresholdImage = imgproc.binaryThreshold(grayScaleImage, 0.5)
highgui.showImage(path, thresholdImage)


# WRITING
print("Saving grayscale and threshold images")
cv2.imwrite(path + "EX1GRAYSCALE." + extension, grayScaleImage)
cv2.imwrite(path + "EX1THRESHOLD." + extension, thresholdImage)
