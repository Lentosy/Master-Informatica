import cv2
import sys
import os.path   

try:
    fullPath = sys.argv[1]
except IndexError:
    print("One parameter required: the path of an image.")
    exit(1)

if (not os.path.isfile(fullPath)):
    print("'" + fullPath + "' is not an existing file.")
    exit(2)

filepath, filename = os.path.split(fullPath) # seperate path and extension:  [/path/to/file].[extension]
cv2.namedWindow(filename)

# DEFAULT
image = cv2.imread(fullPath)
medianBlurredImage = cv2.medianBlur(image, 3)
result = cv2.hconcat((image, medianBlurredImage))
cv2.imshow(filename, result)
cv2.waitKey()

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "SALTANDPEPPERNOISE." + extension
print("Saving as: " + savePath)
cv2.imwrite(savePath, medianBlurredImage)