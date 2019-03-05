import cv2
import sys
import os.path
import numpy

#shadow_box.png
try:
    fullPath = sys.argv[1]
except IndexError:
    print("One parameter required: the path of an image. (shadow_box.jpg)")
    exit(-1)

if (not os.path.isfile(fullPath)):
    print("'" + fullPath + "' is not an existing file.")
    exit(-1)


filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)
image = cv2.imread(fullPath)
cv2.imshow(filename, image)


src = numpy.array([[0, 0], [0, 0], [0, 0], [0, 0]], numpy.float32) 
dst = numpy.array([[100, 200], [200, 200], [200, 500], [100, 500]], numpy.float32) # predefined coördinates of the rectangle

def onMouse(event, x, y, flags, userdata):
    global mouseClicks, image, filename
    if(cv2.EVENT_LBUTTONDOWN == event and mouseClicks < 4):  
        src[mouseClicks] = [x, y]
        mouseClicks += 1
    if(mouseClicks == 4):
        mouseClicks += 1 # increase one more time so this function will basically do nothing anymore
        
        M = cv2.getPerspectiveTransform(src, dst) # Get the transformation matrix
        warped = cv2.warpPerspective(image, M, (-1, -1)) # warp the image
        result = cv2.hconcat((image, warped)) # concatenate the original image and warped image
        cv2.imshow(filename, result) # show original and warped image

        # Saving the warped image
        filename, extension = filename.split(".")
        savePath = filepath + "\\" + filename + "EX9." + extension
        print("Saving as: " + savePath)
        cv2.imwrite(savePath, warped)


mouseClicks = 0 
cv2.setMouseCallback(filename, onMouse, mouseClicks)
cv2.waitKey()

