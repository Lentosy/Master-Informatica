import cv2

def convertToGrayscale(src):
    return cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)

def binaryThreshold(src, ratio):
    retval, dst = cv2.threshold(src, ratio * 255, 255, cv2.THRESH_BINARY)
    return dst



def unsharpMasking(src, kernelSize):
    blurredImage = cv2.GaussianBlur(src, (kernelSize, kernelSize), 0) # grote waarden gebruiken om te overdrijven
    diff = cv2.absdiff(src, blurredImage)
    unsharpImage = cv2.add(diff, src)
    return unsharpImage