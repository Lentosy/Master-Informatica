import cv2
import sys
import os.path
import numpy


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

    N = 75 # moet oneven zijn
    sigmabig = 20
    sigmasmall = 1
    degrees = -15

    DoG = getDoGFilter(N, sigmabig, sigmasmall, degrees)

    #visualizeKernel('DoG filter', DoG)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    res = cv2.convertScaleAbs(cv2.filter2D(gray, cv2.CV_32F, DoG))
    cv2.imshow(filename, res)

    cv2.waitKey()
    filename, extension = filename.split(".")
    savePath = filepath + "\\" + filename + "EX10." + extension
    print("Saving as: " + savePath)
    cv2.imwrite(savePath, res)


def visualizeKernel(windowname, kernel):    
    minval, maxval, minloc, maxloc = cv2.minMaxLoc(kernel)
    d = numpy.maximum(abs(minval),maxval)
    result = (kernel * (0.5)/maxval) + 0.5    
    result = cv2.resize(result,(500, 500))
    cv2.namedWindow(windowname)
    cv2.imshow(windowname, numpy.uint8(result))
    cv2.waitKey()



def getDoGFilter(N, sigmabig, sigmasmall, angle):
    m = int((N - 1)/2)
    guassianColumnKernel = cv2.getGaussianKernel(N, sigmabig)
    gaussianRowKernel = numpy.transpose(cv2.getGaussianKernel(N, sigmasmall))
    squareMatrix = numpy.zeros((N, N))
    for i in range(0, N):
        squareMatrix[i][m] = guassianColumnKernel[i]

    gaussian2D = cv2.filter2D(squareMatrix, -1, gaussianRowKernel)
    
    dx, dy = (1, 0)
    DoG = cv2.Sobel(gaussian2D, -1, dx, dy)
    
    # voor hier is er nog iets fout
    rotationMatrix = cv2.getRotationMatrix2D((int(N/2), int(N/2)), angle, 1)
    DogKernel = cv2.warpAffine(DoG, rotationMatrix, (N, N))
    return DogKernel


if __name__ == '__main__':
    main()