import cv2


# Converts the src image to grayscale and returns the result.
def convertToGrayscale(src):
    return cv2.cvtColor(src, cv2.COLOR_BGR2GRAY)

def resize(src, dimension):
    return cv2.resize(src, dimension)



def addBorder(src, color):
    cv2.rectangle(img=src,
                   pt1=(0, 0), 
                   pt2=(src.shape[1], src.shape[0]),
                   color=(0, 255, 0),
                   thickness=5)