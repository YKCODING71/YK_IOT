import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 빨간색의 범위를 정의합니다.
    #lower_red = np.array([177, 100, 100])
    #upper_red = np.array([180, 255, 255])
    lower_red = np.array([170, 60, 100])
    upper_red = np.array([180, 255, 255])

    red_mask = cv2.inRange(hsv_frame, lower_red, upper_red)

    red_objects = cv2.bitwise_and(frame, frame, mask=red_mask)

    cv2.imshow('Red Objects Tracking', red_objects)
    cv2.imshow('mask', red_mask)
    cv2.imshow('hsv', hsv_frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
