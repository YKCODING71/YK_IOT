# 왼쪽 100*100위치에 반지름 30 파란 원을 그리고 그 원을 사람손이 감지되면 빨간원으로 바뀌기 tkinter창에서
import tkinter as tk
from PIL import Image, ImageTk
from ultralytics import YOLO
import cv2
from threading import Thread

# YOLOv8 모델 로드
model = YOLO("yolov8n.pt")

# tkinter 창 초기화
root = tk.Tk()
root.title("손 감지 상태")
root.geometry("800x600")

# 영상 표시를 위한 캔버스 생성
canvas = tk.Canvas(root, width=640, height=480)
canvas.pack()

# 상태 표시를 위한 레이블 생성
status_label = tk.Label(root, text="정상", font=("Arial", 24), fg="green")
status_label.pack(pady=10)

# 원의 초기 속성
circle_color = "blue"
circle_x, circle_y, circle_radius = 100, 100, 30  # 원의 중심과 반지름

# 감지 상태 업데이트 함수
def update_status(status):
    if status == "위험":
        status_label.config(text="위험", fg="red")
    else:
        status_label.config(text="정상", fg="green")

# OpenCV 웹캠 처리 함수
def webcam_detection():
    global circle_color
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
        frame = cv2.flip(frame, 1)
        # YOLO 모델로 객체 탐지 수행
        results = model(frame)

        # 손이 원의 영역에 들어오는지 확인
        hand_in_circle = False
        for result in results[0].boxes:
            cls = int(result.cls)  # 클래스 ID
            x1, y1, x2, y2 = map(int, result.xyxy[0])  # 탐지 박스 좌표

            # 손의 클래스 ID는 17로 가정
            if cls == 2:
                hand_x, hand_y = (x1 + x2) // 2, (y1 + y2) // 2  # 손의 중심 좌표
                distance = ((hand_x - circle_x) ** 2 + (hand_y - circle_y) ** 2) ** 0.5
                if distance <= circle_radius:
                    hand_in_circle = True
                    break

        # 원의 색상 변경 및 상태 업데이트
        if hand_in_circle:
            circle_color = "red"
            update_status("위험")
        else:
            circle_color = "blue"
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

# tkinter에서 원 그리기
def draw_circle():
    canvas.delete("circle")  # 기존 원 삭제
    canvas.create_oval(
        circle_x - circle_radius,
        circle_y - circle_radius,
        circle_x + circle_radius,
        circle_y + circle_radius,
        fill=circle_color,
        tags="circle",
    )
    root.after(50, draw_circle)  # 주기적으로 업데이트

# OpenCV를 별도 스레드에서 실행
thread = Thread(target=webcam_detection, daemon=True)
thread.start()

# 원 그리기 주기적 업데이트
draw_circle()

# tkinter 메인 루프 실행
root.mainloop()
