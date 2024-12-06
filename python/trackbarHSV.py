#트랙바에서 선택한대로 색깔검출

import cv2
import numpy as np
#cap = cv2.VideoCapture(r"C:\KIROS\pro_\a1_deep\basic\yoloRcCar.mp4") 
cap = cv2.VideoCapture(0)
cap.set(3, 320)  # 프레임 너비
cap.set(4, 240)  # 프레임 높이

ch_hsv = np.array([0, 0, 0])  # 초기 HSV 값을 설정합니다.

def change_color(x):
  global ch_hsv
  r = cv2.getTrackbarPos("R", "Image")
  g = cv2.getTrackbarPos("G", "Image")
  b = cv2.getTrackbarPos("B", "Image")
  s = cv2.getTrackbarPos("S", "Image")
  v = cv2.getTrackbarPos("V", "Image")
  color = [b,g,r]
  image[:] = color

  pixel = np.uint8([[color]])
  hsv = cv2.cvtColor(pixel, cv2.COLOR_BGR2HSV)
  hsv = hsv[0][0]
  print("bgr: ", color)
  print("hsv: ", hsv)
  ch_hsv = [hsv[0],s,v]
  
  
image = np.zeros((600, 400, 3), np.uint8)
cv2.namedWindow("Image")

cv2.createTrackbar("R", "Image", 0, 255, change_color)
cv2.createTrackbar("G", "Image", 0, 255, change_color)
cv2.createTrackbar("B", "Image", 0, 255, change_color)
cv2.createTrackbar("S", "Image", 0, 255, change_color)
cv2.createTrackbar("V", "Image", 0, 255, change_color)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    lower = np.array([ch_hsv[0] - 10, ch_hsv[1], ch_hsv[2]])
    upper = np.array([ch_hsv[0] + 10, 255, 255])
    img_mask = cv2.inRange(hsv, lower, upper)
    
    img_result = cv2.bitwise_and(frame, frame, mask=img_mask)

    cv2.imshow('img_color', frame)
    cv2.imshow('img_mask', img_mask)
    cv2.imshow('img_result', img_result)
    cv2.imshow('Image', image)


    if cv2.waitKey(16) & 0xFF == 27:  # ESC 키를 누르면 종료
        break

cap.release()  
cv2.destroyAllWindows()
