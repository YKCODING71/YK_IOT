import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    if not ret:
        break

    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 색상 범위를 정의합니다.
    lower_red = np.array([170, 100, 100])
    upper_red = np.array([180, 255, 255])
    
    lower_green = np.array([40, 100, 100])
    upper_green = np.array([80, 255, 255])
    
    lower_blue = np.array([100, 100, 100])
    upper_blue = np.array([140, 255, 255])

    # 각 색상에 대한 마스크를 생성합니다.
    red_mask = cv2.inRange(hsv_frame, lower_red, upper_red)
    green_mask = cv2.inRange(hsv_frame, lower_green, upper_green)
    blue_mask = cv2.inRange(hsv_frame, lower_blue, upper_blue)

    # 각 색상에 해당하는 객체를 추출합니다.
    red_objects = cv2.bitwise_and(frame, frame, mask=red_mask)
    green_objects = cv2.bitwise_and(frame, frame, mask=green_mask)
    blue_objects = cv2.bitwise_and(frame, frame, mask=blue_mask)

    # 색상 검출 여부를 확인합니다.
    color_value = ""
    if np.any(red_mask > 0):
        color_value = "R"
    elif np.any(green_mask > 0):
        color_value = "G"
    elif np.any(blue_mask > 0):
        color_value = "B"
    else :
        color_value = "NO"

    # 결과 출력
    cv2.putText(frame, f"Color: {color_value}", (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)

    cv2.imshow('Red Objects Tracking', red_objects)
    cv2.imshow('Green Objects Tracking', green_objects)
    cv2.imshow('Blue Objects Tracking', blue_objects)
    cv2.imshow('Original Frame', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
