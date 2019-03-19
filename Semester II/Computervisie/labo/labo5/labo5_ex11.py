import cv2
import sys
import os.path
import numpy
import math

def checkFileArg():
    try:
        sys.argv[1]
    except IndexError:
        print("One parameter required: the path of an image. (rays.png)")
        exit(-1)
    
    if (not os.path.isfile(sys.argv[1])):
        print("'" + fullPath + "' is not an existing file.")
        exit(-1)


def main():
    checkFileArg()

    fullPath = sys.argv[1]
    filepath, filename = os.path.split(fullPath)
    cv2.namedWindow(filename)
    image = cv2.imread(fullPath)
    
    res = getLines(image, 50, 200)
    cv2.imshow(filename, res)


    cv2.waitKey()
    filename, extension = filename.split(".")
    savePath = filepath + "\\" + filename + "EX11." + extension
    print("Saving as: " + savePath)
    cv2.imwrite(savePath, res)

def getLines(image, min_thres, max_thres):
    result = image.copy()
    edges = cv2.Canny(cv2.cvtColor(image, cv2.COLOR_BGR2GRAY), 50, 200, None, 5, True)
    lines = cv2.HoughLines(edges, 1, numpy.pi/180, 110, None, 0, 0)
    for i in range(0, len(lines)):
        rho = lines[i][0][0]
        theta = lines[i][0][1]
        a = math.cos(theta)
        b = math.sin(theta)
        x0 = a*rho
        y0 = b*rho
        pt1 = (int(x0 + 1000*(-b)), int(y0 + 1000*(a)))
        pt2 = (int(x0 - 1000*(-b)), int(y0 - 1000*(a)))
        cv2.line(result, pt1, pt2, (0,0,0), 2, cv2.LINE_AA)
    return result
if __name__ == '__main__':
    main()