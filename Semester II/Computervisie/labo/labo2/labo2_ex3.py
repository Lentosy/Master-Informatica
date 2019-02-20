import cv2
import sys
import os.path


# unsharp.png
try:
    fullPath = sys.argv[1]
except IndexError:
    print("One parameter required: the path of an image.")
    exit(1)

if (not os.path.isfile(fullPath)):
    print("'" + fullPath + "' is not an existing file.")
    exit(2)

filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)

image = cv2.imread(fullPath)

#unsharp mask procedure
blurredImage = cv2.GaussianBlur(image, (51, 51), 0) # grote waarden gebruiken om te overdrijven
diff = cv2.absdiff(image, blurredImage)
unsharpImage = cv2.add(diff, image)

result = cv2.hconcat((image, unsharpImage))
cv2.imshow(filename, result)
cv2.waitKey()

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX3." + extension
print("Saving as: " + savePath)
cv2.imwrite(savePath, unsharpImage)


