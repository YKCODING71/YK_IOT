import cv2
import numpy as np

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # 빨간색의 범위를 정의합니다.
    lower_red = np.array([30, 80, 40])
    upper_red = np.array([40, 255, 255])

    red_mask = cv2.inRange(hsv_frame, lower_red, upper_red)

    red_objects = cv2.bitwise_and(frame, frame, mask=red_mask)
    
    contours, _ = cv2.findContours(red_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        if cv2.contourArea(contour) > 500:  # 작은 윤곽선은 무시 (필요에 따라 조정)
            (x, y), radius = cv2.minEnclosingCircle(contour)
            if radius > 5:  # 반지름이 5보다 큰 경우에만 표시
                cv2.circle(frame, (int(x), int(y)), int(radius), (0, 255, 0), 3)

                frame_width = frame.shape[1]  # 이미지 폭
                scaled_x = int(x / frame_width * 180)  # 전체 이미지 폭에 대한 비율 (0~180)까지 표현

                # 가로 좌표 출력
                print(f'가로좌표값 : {scaled_x}')

    cv2.imshow('Red Objects Tracking', frame)
    cv2.imshow('Mask', red_mask)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
