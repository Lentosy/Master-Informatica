import cv2
def openImage(src):
    return cv2.imread(src)

def showImage(windowname, src):
    cv2.imshow(windowname, src)
    cv2.waitKey()

def showImagesHorizontally(windowname, *srcList): 
    showImage(windowname, cv2.hconcat((srcList)))

def saveImage(src, savePath):
    cv2.imwrite(savePath, src)
