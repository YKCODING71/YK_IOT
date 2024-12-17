import cv2
import numpy as np
import serial
import time

# 시리얼 포트 설정
ser = serial.Serial('COM3', 115200)  # COM 포트와 보드레이트를 ESP32 설정에 맞게 변경
time.sleep(2)  # ESP32 초기화 대기

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    if not ret:
        break

    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 색상 범위를 정의합니다.
    lower_red = np.array([170, 60, 100])
    upper_red = np.array([180, 255, 255])

    lower_green = np.array([40, 40, 40])
    upper_green = np.array([80, 255, 255])

    lower_blue = np.array([100, 150, 0])
    upper_blue = np.array([140, 255, 255])

    # 각 색상에 대한 마스크를 생성합니다.
    red_mask = cv2.inRange(hsv_frame, lower_red, upper_red)
    green_mask = cv2.inRange(hsv_frame, lower_green, upper_green)
    blue_mask = cv2.inRange(hsv_frame, lower_blue, upper_blue)

    red_area = cv2.countNonZero(red_mask)
    green_area = cv2.countNonZero(green_mask)
    blue_area = cv2.countNonZero(blue_mask)

    max_area = max(red_area, green_area, blue_area)
    
    # 색상 검출 여부를 확인합니다.
    color_value = ""
    if max_area == red_area:
        max_color = "R"
    elif max_area == green_area:
        max_color = "G"
    else:
        max_color = "B"
        
    # ESP32로 데이터 전송
    if max_color:
        ser.write(max_color.encode())  # 색상 값을 전송
        print(f"Sent to ESP32: {max_color}")
        time.sleep(0.1)  # 데이터 전송 후 잠시 대기

        # ESP32로부터 응답 받기
        if ser.in_waiting > 0:
            response = ser.readline().decode().strip()
            print(f"Received from ESP32: {response}")

    # 결과 출력
    cv2.putText(frame, f"Color: {max_color}", (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)


    red_objects = cv2.bitwise_and(frame, frame, mask=red_mask)
    green_objects = cv2.bitwise_and(frame, frame, mask=green_mask)
    blue_objects = cv2.bitwise_and(frame, frame, mask=blue_mask)
    cv2.imshow('Red Objects Tracking', red_objects)
    cv2.imshow('Green Objects Tracking', green_objects)
    cv2.imshow('Blue Objects Tracking', blue_objects)
    cv2.imshow('Original Frame', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
ser.close()
