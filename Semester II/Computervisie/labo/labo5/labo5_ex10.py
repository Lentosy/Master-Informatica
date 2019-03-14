import cv2
import sys
import os.path
import numpy

#rays.png
try:
    fullPath = sys.argv[1]
except IndexError:
    print("One parameter required: the path of an image. (shadow.png)")
    exit(-1)

if (not os.path.isfile(fullPath)):
    print("'" + fullPath + "' is not an existing file.")
    exit(-1)

filepath, filename = os.path.split(fullPath)
cv2.namedWindow(filename)
image = cv2.imread(fullPath)


def visualizeArray(array):
    
    minval, maxval, minloc, maxloc = cv2.minMaxLoc(array)
    d = numpy.maximum(abs(minval),maxval)
        
    array /= d
    array /= 2
    array += 0.5

    print(array)
    cv2.imshow(filename, numpy.uint8(array))
    cv2.waitKey()


def getDoGFilter(image, N, sigma, degrees):
    m = int((N - 1)/2) # middle column index
    guassianKernelColumn = cv2.getGaussianKernel(N, sigma)
    squareMatrix = numpy.zeros((N, N))
    for i in range(0, N):
        squareMatrix[i][m] = guassianKernelColumn[i]
        
    guassianKernelRow = cv2.getGaussianKernel(N, 1) # kleinere sigmawaarde
    guassianKernelRow.transpose()
   
    gaussian2D = cv2.filter2D(squareMatrix, -1, guassianKernelRow)
 
    dx, dy = (1, 0)
    DoG = cv2.Sobel(gaussian2D, -1, dx, dy)
    
    # voor hier is er nog iets fout
    visualizeArray(gaussian2D)
    rows, cols, channels = image.shape

    rotationMatrix = cv2.getRotationMatrix2D((rows/2, cols/2), degrees, 1)
    cv2.warpAffine(DoG, rotationMatrix, (rows, cols))
    return DoG

N = 501 # moet oneven zijn
sigma = 4
degrees = -15

DoG = getDoGFilter(image, N, sigma, degrees)


gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
res = abs(cv2.filter2D(gray, -1, DoG))

cv2.imshow(filename, res)
cv2.waitKey()

filename, extension = filename.split(".")
savePath = filepath + "\\" + filename + "EX10." + extension
print("Saving as: " + savePath)
cv2.imwrite(savePath, res)
