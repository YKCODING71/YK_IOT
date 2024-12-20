#python --version --> Python 3.11.8
#pip install opencv-python
#python.exe -m pip install --upgrade pip

import cv2
import numpy as np

fname = r'cat.jpg'

original = cv2.imread(fname, cv2.IMREAD_COLOR)
gray = cv2.imread(fname, cv2.IMREAD_GRAYSCALE)
unchange = cv2.imread(fname, cv2.IMREAD_UNCHANGED)

cv2.imshow('Original', original)
cv2.imshow('Gray', gray)
cv2.imshow('Unchange', unchange) #numpy

cv2.waitKey(0)
cv2.destroyAllWindows()
