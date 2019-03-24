from Modules import imgproc, highgui, optcheck

def main():
    imagePath = optcheck.getArguments()[0]
    image = highgui.openImage(imagePath)
    result = imgproc.extractEdges(image, -15)
    highgui.showImage(imagePath, result)
    highgui.saveImage(result, highgui.getSavePath(imagePath, '10'))

if __name__ == '__main__':
    main()