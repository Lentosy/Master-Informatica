import cv2
import os
from Modules import highgui, imgproc, optcheck

def main():
    (image1_path, image2_path) = optcheck.getArguments()
    image1 = highgui.openImage(image1_path)
    image2 = highgui.openImage(image2_path)

    imgproc.detectORBFeatures(image1, 96)
    imgproc.detectORBFeatures(image2, 96)
    matches = imgproc.matchORBFeatures(image1, image2, 96, 48)
    highgui.showImagesHorizontally("ORB feature detection", matches)
    highgui.saveImage(matches, 'Images\matchesEX13.png')

    
if __name__ == '__main__':
    main()

