import cv2
import sys
import os.path

try:
    filePath = sys.argv[1]
except IndexError:
    print("One parameter required: the path of an image.")
    exit(1)

if (not os.path.isfile(filePath)):
    print("'" + filePath + "' is not an existing file.")
    exit(2)

path, extension = filePath.split(".") # seperate path and extension:  [/path/to/file].[extension]
cv2.namedWindow(path)

# DEFAULT
defaultImage = cv2.imread(filePath)
cv2.imshow(path, defaultImage)
cv2.waitKey()

# GRAYSCALE
print("Converting to grayscale")
grayScaleImage = cv2.cvtColor(defaultImage, cv2.COLOR_BGR2GRAY);
cv2.imshow(path, grayScaleImage)
cv2.waitKey()

# THRESHOLD
print("Thresholding the grayscale image at 50% of the maximum intensity")
ret, thresholdImage = cv2.threshold(grayScaleImage, 127, 255, cv2.THRESH_BINARY)
cv2.imshow(path, thresholdImage)
cv2.waitKey()

# WRITING
print("Saving grayscale and threshold images")
cv2.imwrite(path + "GRAYSCALE." + extension, grayScaleImage)
cv2.imwrite(path + "THRESHOLD." + extension, thresholdImage)
