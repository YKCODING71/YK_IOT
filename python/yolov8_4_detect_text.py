import cv2
from ultralytics import YOLO
from PIL import ImageFont, ImageDraw, Image
import numpy as np

# Load the YOLOv8 model
model = YOLO(r'best.pt')
cap = cv2.VideoCapture(0)

# 한글 폰트 설정 (폰트 파일 경로를 적어야 합니다. 예: 'path_to_font.ttf')
font_path = "C:\Windows\Fonts\malgun.ttf"  # 예시로, 다른 폰트를 사용할 수 있습니다.
font = ImageFont.truetype(font_path, 30)

while True:
    ret, img = cap.read()
    
    # Run the model to get results
    results = model(img)

    for i in results:  # box                
        for box in i.boxes:  # 'xyxy': box coordinates, 'cls': class id, 'conf': confidence
            class_id = int(box.cls[0])
            confidence = box.conf[0]
            print(f"Class ID: {class_id}, Confidence: {confidence:.2f}")
            
            Color = 'cyan'
            
            # Annotating based on class_id
            if class_id == 0:
                label = "양품"
            elif class_id == 1:
                label = "불량품"
                Color = 'magenta'
            else:
                label = "알 수 없음"

            # Get the box coordinates
            x1, y1, x2, y2 = map(int, box.xyxy[0])

            # Convert the image to PIL format for drawing text
            img_pil = Image.fromarray(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
            draw = ImageDraw.Draw(img_pil)
            
            # Draw rectangle
            draw.rectangle([x1, y1, x2, y2], outline= Color, width=3)
            
            # Draw the label with Korean text
            draw.text((x1, y1 - 30), label, font=font, fill=Color)

            # Convert back to OpenCV format
            img = cv2.cvtColor(np.array(img_pil), cv2.COLOR_RGB2BGR)

    # Show the annotated frame
    cv2.imshow('Webcam', img)

    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
