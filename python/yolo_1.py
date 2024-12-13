#pip install ultralytics
#pip install --upgrade pip

from ultralytics import YOLO
import cv2

# Load a COCO-pretrained YOLOv8n model
model = YOLO("yolov8n.pt")

# Display model information (optional)
model.info()

# Train the model on the COCO8 example dataset for 100 epochs
#results = model.train(data="coco8.yaml", epochs=100, imgsz=640)

# Run inference with the YOLOv8n model on the 'bus.jpg' image
results = model("bus.jpg")
results = model("b.jpg")

result_image = results[0].plot()  # 결과 이미지를 그립니다.

# Save the result image
cv2.imwrite("bus_detected.jpg", result_image)  # 결과를 'bus_detected.jpg'로 저장

# Display the result image in a window (optional)
cv2.imshow("YOLO Detection", result_image)
cv2.waitKey(0)  # 아무 키나 누를 때까지 대기
cv2.destroyAllWindows()  # 