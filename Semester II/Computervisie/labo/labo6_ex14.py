# In  this  exercise  you  will  make  a  set  of  DoG  (differential  of  Gaussian)  filters,
#  using  the  code  from  Lab  5 exercise 10. You will use it to construct a feature vector for each 16x16 pixel block in an image.
# • Make DoG filters in 2 scales and 6 orientations.
# • Filter road1.png with each of the filters.  This gives you 12 response values per pixel.
# • Divide the image into 16 by 16 pixel blocks and compute for every filter the maximum absolute
#   valueof the response within each block.  This gives you 12 numbers per block.
# • Using the block labels in road1blocks.png, compare the mean value of each feature 
#   for blocks containing road markings, and blocks containing no road markings.
#   This should result in a plot similar to the one in Figure 1.

import cv2
import numpy
import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestClassifier
from Modules import optcheck, highgui, imgproc

ANGLES = range(0, 180, 30)
BLOCK_SIZE = (16, 16)
IMAGES = [f'Images\\road{x}' for x in range(1, 4 +1)]

def getFilters(image):
    DoGFilters = []
    for angle in ANGLES: # angle = [0, 30, 60, 90, 120, 150]
        DoGFilters.append(imgproc.getDoGFilter(size = 11, sigmabig = 2, sigmasmall = 1, angle = angle))
    for angle in ANGLES:
        DoGFilters.append(imgproc.getDoGFilter(size = 51, sigmabig = 7, sigmasmall = 3, angle = angle))
    
    responses = []
    for DoGFilter in DoGFilters:      
        responses.extend([cv2.filter2D(src = image, ddepth = -1, kernel = DoGFilter)])
    maxvalues = []
    for response in responses:
        maxvalues_response = []
        for i in range(0, 352, BLOCK_SIZE[0]):
            maxvalues_row = []
            for j in range(0, 640, BLOCK_SIZE[1]):
                block = response[i:i+16, j:j+16]
                maxvalues_row.append(numpy.amax(block))
            maxvalues_response.extend([maxvalues_row])
        maxvalues.extend([maxvalues_response])
    return maxvalues

def getRoadMarkings(img):
    roadmarkings = []
    for i in range(0, 352, BLOCK_SIZE[0]):
        markings_row = []
        for j in range(0, 640, BLOCK_SIZE[1]):
            markings_row.append(numpy.amax(img[i:i+16, j:j+16]))
        roadmarkings.extend([markings_row])
    return roadmarkings

def visualizeMeans(filters, roadmarkings):
    mean_values_road_per_filter = []
    mean_values_non_road_per_filter = []
    
    for f in filters:
        response_road_marked_blocks = []
        response_non_road_marked_blocks = []
        for i in range(0, len(roadmarkings)):
            for j in range(0, len(roadmarkings[i])):
                if(roadmarkings[i][j] == 255):
                    response_road_marked_blocks.append(f[i][j])
                else:
                    response_non_road_marked_blocks.append(f[i][j])
        mean_values_road_per_filter.append(numpy.mean(response_road_marked_blocks))
        mean_values_non_road_per_filter.append(numpy.mean(response_non_road_marked_blocks))
    
    plt.plot(mean_values_road_per_filter, label = "road mark blocks")
    plt.plot(mean_values_non_road_per_filter, label = "non-road mark blocks")
    plt.legend()
    plt.xlabel("filter index")
    plt.ylabel("mean of maximal response per block")
    plt.show()

def main():
    randomForestClassifier = RandomForestClassifier(n_estimators = 10, min_samples_leaf = 10)
    for imagePath in IMAGES:
        image = highgui.openImage(f"{imagePath}.png")
        image_blocks = highgui.openImage(f"{imagePath}_blocks.png")

if __name__ == '__main__':
    main()