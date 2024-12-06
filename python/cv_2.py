import cv2
import numpy as np

cap = cv2.VideoCapture(0)
cap.set(3, 320)  # 너비 설정
cap.set(4, 240)  # 높이 설정

while True:
    ret, frame = cap.read()

    if not ret:
        break

    # 프레임을 그레이스케일로 변환
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 원본, 그레이스케일, 변경되지 않은 이미지를 표시
    cv2.imshow('Original', frame)
    cv2.imshow('Gray', gray)

    if cv2.waitKey(1) & 0xFF == ord('q'):  # 'q' 키를 누르면 종료
        break

cap.release()
cv2.destroyAllWindows()
