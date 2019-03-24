from Modules import highgui, imgproc, optcheck

def main():
    imagePath = optcheck.getArguments()[0]
    image = highgui.openImage(imagePath)
    
    image = imgproc.detectLines(image, 100, 200)
    highgui.showImage("name", image)
    highgui.saveImage(image, highgui.getSavePath(imagePath, '11'))
 

if __name__ == '__main__':
    main()