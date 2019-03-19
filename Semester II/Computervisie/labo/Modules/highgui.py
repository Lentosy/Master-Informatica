import cv2

def showImage(windowname, image):
    cv2.imshow(windowname, image)
    cv2.waitKey()


def showImagesHorizontally(windowname, *images): 
    showImage(windowname, cv2.hconcat((images)))



def saveImage(image, savePath):
    print("Saving as: " + savePath)
    cv2.imwrite(savePath, image)