from ultralytics import YOLO
import cv2

# COCO 데이터셋으로 사전 학습된 YOLOv8n 모델 로드
model = YOLO("yolov8n.pt")

# 모델 정보 출력 (선택 사항)
model.info()

# 웹캠 열기 (기본 웹캠 사용)
cap = cv2.VideoCapture(0)  # 0번 카메라는 기본 웹캠
if not cap.isOpened():
    print("웹캠을 열 수 없습니다.")
    exit()

while True:
    # 웹캠에서 프레임 읽기
    ret, frame = cap.read()
    if not ret:
        print("프레임을 읽을 수 없습니다.")
        break

    # 화면 크기 가져오기
    height, width, _ = frame.shape

    # 왼쪽 절반 영역 정의
    left_rectangle = (0, 0, width // 2, height)

    # 탐지 상태 초기화
    is_person_detected = False

    # YOLO 모델로 객체 탐지 수행
    results = model(frame)

    # 탐지된 객체에서 사람이 왼쪽 절반에 있는지 확인
    for result in results[0].boxes:
        cls = int(result.cls)  # 클래스 ID
        x1, y1, x2, y2 = map(int, result.xyxy[0])  # 탐지 박스 좌표

        # 사람이 감지되고, 사각형 내부에 있는 경우
        if cls == 0 and x1 < width // 2:  # 사람이 왼쪽 절반에 있을 때
            is_person_detected = True
            break

    # 투명한 빨간색 사각형 추가
    overlay = frame.copy()  # 원본 프레임 복사
    if is_person_detected:
        # 빨간색으로 왼쪽 절반 채우기
        cv2.rectangle(overlay, (left_rectangle[0], left_rectangle[1]), 
                              (left_rectangle[2], left_rectangle[3]), 
                              (0, 0, 255), -1)  # 빨간색 채우기

        # 원본 프레임과 오버레이 합성 (투명도 50%)
        alpha = 0.5
        frame = cv2.addWeighted(overlay, alpha, frame, 1 - alpha, 0)

    # 왼쪽 절반에 테두리 그리기
    cv2.rectangle(frame, (left_rectangle[0], left_rectangle[1]), 
                         (left_rectangle[2], left_rectangle[3]), 
                         (255, 0, 0), 2)  # 파란색 테두리

    # 탐지 결과를 화면에 표시
    result_image = results[0].plot()  # 결과 이미지를 시각화합니다.

    # 탐지 결과를 화면에 표시
    cv2.imshow("YOLO Detection", result_image)
    cv2.imshow("YOLO Detection", frame)

    # 'q' 키를 누르면 종료
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 웹캠과 창 닫기
cap.release()
cv2.destroyAllWindows()
