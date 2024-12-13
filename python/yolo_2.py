#
from ultralytics import YOLO
import cv2

# COCO 데이터셋으로 사전 학습된 YOLOv8n 모델 로드
model = YOLO("yolov8n.pt")

# 모델 정보 출력 (선택 사항)
model.info()

# COCO8 예제 데이터셋으로 100 에포크 동안 모델 학습 
results = model.train(data="coco8.yaml", epochs=100, imgsz=640) 

# 'bus.jpg' 이미지를 사용해 YOLOv8n 모델로 추론 수행
results = model("bus.jpg")

#------------------------------------------------------------
# 탐지 결과 시각화
result_image = results[0].plot()  # 결과 이미지를 시각화합니다.

# 탐지 결과를 이미지 파일로 저장
cv2.imwrite("bus_detected.jpg", result_image)  # 결과를 'bus_detected.jpg'로 저장합니다.

# 결과 이미지를 화면에 표시 (선택 사항)
cv2.imshow("YOLO Detection", result_image)  # 결과 이미지를 새 창에 표시합니다.
cv2.waitKey(0)  # 아무 키나 누를 때까지 대기합니다.
cv2.destroyAllWindows()  # 창을 닫습니다.
