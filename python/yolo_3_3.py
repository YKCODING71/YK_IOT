import tkinter as tk
from PIL import Image, ImageTk
from ultralytics import YOLO
import cv2
from threading import Thread

# YOLOv8 모델 로드
model = YOLO("yolov8n.pt")

# tkinter 창 초기화
root = tk.Tk()
root.title("사람 감지 상태")
root.geometry("800x600")

# 영상 표시를 위한 캔버스 생성
canvas = tk.Canvas(root, width=640, height=480)
canvas.pack()

# 상태 표시를 위한 레이블 생성
status_label = tk.Label(root, text="정상", font=("Arial", 24), fg="green")
status_label.pack(pady=10)

# 감지 상태 업데이트 함수
def update_status(status):
    if status == "위험":
        status_label.config(text="위험", fg="red")
    else:
        status_label.config(text="정상", fg="green")

# OpenCV 웹캠 처리 함수
def webcam_detection():
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("웹캠을 열 수 없습니다.")
        root.quit()
        return

    while True:
        ret, frame = cap.read()
        if not ret:
            print("프레임을 읽을 수 없습니다.")
            break

        # 화면 크기 가져오기
        height, width, _ = frame.shape

        # 왼쪽 절반 영역 정의
        left_area_x = width // 2

        # YOLO 모델로 객체 탐지 수행
        results = model(frame)

        # 왼쪽 절반에 사람이 감지되는지 확인
        is_person_detected = False
        for result in results[0].boxes:
            cls = int(result.cls)  # 클래스 ID
            x1, y1, x2, y2 = map(int, result.xyxy[0])  # 탐지 박스 좌표

            if cls == 0 and x1 < left_area_x:  # 사람이 왼쪽 영역에 있을 때
                is_person_detected = True
                break

        # 상태 업데이트
        if is_person_detected:
            update_status("위험")

            # 빨간색 투명도 50%로 채우기
            overlay = frame.copy()
            cv2.rectangle(overlay, (0, 0), (left_area_x, height), (0, 0, 255), -1)
            frame = cv2.addWeighted(overlay, 0.5, frame, 0.5, 0)
        else:
            update_status("정상")

        # OpenCV 영상을 tkinter에서 표시 가능한 형식으로 변환
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        img = Image.fromarray(rgb_frame)
        imgtk = ImageTk.PhotoImage(image=img)

        # 캔버스에 이미지 업데이트
        canvas.create_image(0, 0, anchor=tk.NW, image=imgtk)
        canvas.imgtk = imgtk

        # tkinter GUI 업데이트
        root.update()

    cap.release()
    root.quit()

# OpenCV를 별도 스레드에서 실행
thread = Thread(target=webcam_detection, daemon=True)
thread.start()

# tkinter 메인 루프 실행
root.mainloop()
