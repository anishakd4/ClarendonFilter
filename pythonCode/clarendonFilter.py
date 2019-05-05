import cv2
import sys
import numpy as np

#read input image
image=cv2.imread("../assets/anish.jpg")

if image is None:
    print("can not find image")
    sys.exit()

#create a copy of input image to work on
clarendon = image.copy()

#split the channels
blueChannel, greenChannel, redChannel = cv2.split(clarendon)

#Interpolation values
originalValues = np.array([0, 28, 56, 85, 113, 141, 170, 198, 227, 255])
blueValues =     np.array([0, 38, 66, 104, 139, 175, 206, 226, 245, 255 ])
redValues =      np.array([0, 16, 35, 64, 117, 163, 200, 222, 237, 249 ])
greenValues =    np.array([0, 24, 49, 98, 141, 174, 201, 223, 239, 255 ])

#Creating the lookuptables
fullRange = np.arange(0,256)
#Creating the lookuptable for blue channel
blueLookupTable = np.interp(fullRange, originalValues, blueValues )
#Creating the lookuptables for green channel
greenLookupTable = np.interp(fullRange, originalValues, greenValues )
#Creating the lookuptables for red channel
redLookupTable = np.interp(fullRange, originalValues, redValues )

#Apply the mapping for blue channel
blueChannel = cv2.LUT(blueChannel, blueLookupTable)
#Apply the mapping for green channel
greenChannel = cv2.LUT(greenChannel, greenLookupTable)
#Apply the mapping for red channel
redChannel = cv2.LUT(redChannel, redLookupTable)

#merging back the channels
clarendon = cv2.merge([blueChannel, greenChannel, redChannel])

#convert to uint8
clarendon = np.uint8(clarendon)

#create windows to display images
cv2.namedWindow("image", cv2.WINDOW_AUTOSIZE)
cv2.namedWindow("clarendon", cv2.WINDOW_AUTOSIZE)

#display images
cv2.imshow("image", image)
cv2.imshow("clarendon", clarendon)

#press esc to exit the program
cv2.waitKey(0)

#close all the opened windows
cv2.destroyAllWindows()