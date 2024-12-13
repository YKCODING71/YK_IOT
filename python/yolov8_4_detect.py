#pip install ultralytics
#pip install --upgrade pip
3

import cv2
from ultralytics import YOLO
# Load the YOLOv8 model
model = YOLO(r'best2.pt')
#model = YOLO('yolov8s.pt')
cap = cv2.VideoCapture(0)
while True:
    ret, img= cap.read()
    #img = cv2.flip(img, 1)
    results = model(img)

    for i in results:       #box                
        for box in i.boxes: #'xyxy':box좌표, 'cls':클래스id,'conf':신뢰도 
            class_id = int(box.cls[0])  
            confidence = box.conf[0]
            print(f"Class ID: {class_id}, Confidence: {confidence:.2f}")
            if class_id==0:
                print("ID0 찾았다.")            
            elif class_id==1:
                print("ID1 찾았다.")    
                    
                
    annotated_frame = results[0].plot()
    cv2.imshow('Webcam', annotated_frame)
    if cv2.waitKey(1) == ord('q'):
        break
    
cap.release()
cv2.destroyAllWindows()