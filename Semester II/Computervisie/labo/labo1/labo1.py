import cv2
import sys
import os.path

try:
    filePath = sys.argv[1]
except IndexError:
    print("One parameter requested: the path of an image.")
    exit(1)

if (not os.path.isfile(filePath)):
    print("'" + filePath + "' is not an existing file.")
    exit(2)



path, extension = filePath.split(".") # seperate path and extension:  [/path/to/file].[extension]
# these variables are used later on to write the grayscale and threshold images, but also to create a relevant window name

windowName = (path.split("/"))[-1] # access last element when path is splitted on /, so we get the filename, without the extension: /path/to/[file]
cv2.namedWindow(windowName)

# DEFAULT
defaultImage = cv2.imread(filePath)
cv2.imshow(windowName, defaultImage)
cv2.waitKey()

# GRAYSCALE
grayScaleImage = cv2.cvtColor(defaultImage, cv2.COLOR_BGR2GRAY);
cv2.imshow(windowName, grayScaleImage)
cv2.waitKey()

# THRESHOLD
ret, thresholdImage = cv2.threshold(grayScaleImage, 127, 255, cv2.THRESH_BINARY)
cv2.imshow(windowName, thresholdImage)
cv2.waitKey()

# WRITING
cv2.imwrite(path + "GRAYSCALE." + extension, grayScaleImage)
cv2.imwrite(path + "THRESHOLD." + extension, thresholdImage)
