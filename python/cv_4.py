import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 빨간색의 범위를 정의합니다.
    lower_red = np.array([30, 80, 40])
    upper_red = np.array([40, 255, 255])
    # lower_red = np.array([177, 60, 100])
    # upper_red = np.array([180, 255, 255])

    red_mask = cv2.inRange(hsv_frame, lower_red, upper_red)

    red_objects = cv2.bitwise_and(frame, frame, mask=red_mask)
    
    contours, _ = cv2.findContours(red_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        (x, y), radius = cv2.minEnclosingCircle(contour) #원의 중심과 반지름값 반환
        cv2.circle(frame, (int(x), int(y)), int(radius), (0, 255, 0), 3)

    cv2.imshow('Red Objects Tracking', frame)
    cv2.imshow('mask', red_mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
