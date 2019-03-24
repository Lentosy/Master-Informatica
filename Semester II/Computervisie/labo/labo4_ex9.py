import cv2
import numpy
from Modules import optcheck, highgui, imgproc

#shadow_box.png
imagePath = optcheck.getArguments()[0]
windowName = imagePath
image = highgui.openImage(imagePath)
cv2.imshow(windowName, image)



src = numpy.array([[0, 0], [0, 0], [0, 0], [0, 0]], numpy.float32) 
dst = numpy.array([[100, 200], [200, 200], [200, 500], [100, 500]], numpy.float32) # predefined coördinates of the rectangle

def onMouse(event, x, y, flags, userdata):
    global mouseClicks, image, windowName
    print("sure buddy")
    if(cv2.EVENT_LBUTTONDOWN == event and mouseClicks < 4):  
        src[mouseClicks] = [x, y]
        mouseClicks += 1
    if(mouseClicks == 4):
        mouseClicks += 1 # increase one more time so this function will basically do nothing anymore
        
        M = cv2.getPerspectiveTransform(src, dst) # Get the transformation matrix
        warped = cv2.warpPerspective(image, M, (-1, -1)) # warp the image
        result = cv2.hconcat((image, warped)) # concatenate the original image and warped image
        cv2.imshow(windowName, result) # show original and warped image

        # Saving the warped image
        highgui.saveImage(warped, highgui.getSavePath(imagepath, '9'))


mouseClicks = 0 
cv2.setMouseCallback(windowName, onMouse, mouseClicks)
cv2.waitKey()

