import tkinter as tk

def send_signal(signal, message):
    label.config(text=message)  # 메시지를 레이블에 출력

# tkinter 창 설정
root = tk.Tk()
root.title("ESP32 시리얼 통신")
root.geometry("320x200")  # 창 크기 설정

# 레이블 설정
label = tk.Label(root, text="아래 버튼을 눌러보세요!")
label.place(x=120, y=20)  # 창의 상단 중앙에 배치 (픽셀 좌표로 수정)

# LED 켜기 버튼
btn_on = tk.Button(root, text="LED 켜기", command=lambda: send_signal('1', "LED 켜짐 신호 전송!"),
                   bg="green", fg="white")
btn_on.place(x=80, y=80)  # 창의 왼쪽 중앙에 배치 (픽셀 좌표로 수정)

# LED 끄기 버튼
btn_off = tk.Button(root, text="LED 끄기", command=lambda: send_signal('2', "LED 꺼짐 신호 전송!"),
                    bg="red", fg="white")
btn_off.place(x=180, y=80)  # 창의 오른쪽 중앙에 배치 (픽셀 좌표로 수정)

# tkinter 메인 루프
root.mainloop()
