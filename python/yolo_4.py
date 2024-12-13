from ultralytics import YOLO
import cv2

# COCO 데이터셋으로 사전 학습된 YOLOv8n 모델 로드
model = YOLO("yolov8n.pt")

# 모델 정보 출력 (선택 사항)
model.info()

# 웹캠 열기 (기본 웹캠 사용)
cap = cv2.VideoCapture(0)  # 0번 카메라는 기본 웹캠입니다. 다른 카메라는 1, 2로 변경 가능합니다.

while True:
    # 웹캠에서 프레임 읽기
    ret, frame = cap.read()

    # YOLO 모델로 객체 탐지 수행
    results = model(frame)  # 모델은 이미지가 아니라 프레임을 입력받습니다.

    # 탐지 결과 시각화
    result_image = results[0].plot()  # 결과 이미지를 시각화합니다.

    # 탐지 결과를 화면에 표시
    cv2.imshow("YOLO Detection", result_image)

    # 'q' 키를 누르면 실시간 영상 탐지를 종료합니다.
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 웹캠과 창을 닫습니다.
cap.release()
cv2.destroyAllWindows()
