import cv2
import os
from Modules import highgui, imgproc, optcheck

def main():
    (image1_path, image2_path) = optcheck.getArguments()
    image1 = highgui.openImage(image1_path)
    image2 = highgui.openImage(image2_path)

    imgproc.detectCorners(image1)
    imgproc.detectCorners(image2)
    highgui.showImagesHorizontally("Corner feature detection", image1, image2)

    highgui.saveImage(image1, highgui.getSavePath(image1_path, '12'))
    highgui.saveImage(image2, highgui.getSavePath(image2_path, '12'))

    
if __name__ == '__main__':
    main()

