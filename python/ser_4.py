import tkinter as tk
import serial
import time


# ESP32 시리얼 연결
esp32 = serial.Serial('COM3', 115200)  
time.sleep(2)  

def send_signal(signal, message):
    if esp32:
        esp32.write(signal.encode())  
        data = esp32.readline().decode('utf-8').strip()     # 수신된 데이터 읽기
        label.config(text=f"esp32응답: {data}")         # 레이블에 수신된 데이터 표시
    else:
        label.config(text="ESP32 연결 실패")
        

root = tk.Tk()
root.title("ESP32 시리얼 통신")
root.geometry("320x200")  # 창 크기 설정

label = tk.Label(root, text="아래 버튼을 눌러보세요!")
label.place(x=120, y=20)   

btn_on = tk.Button(root, text="LED 켜기", command=lambda: send_signal('1', "LED 켜짐 신호 전송!"),
                   bg="green", fg="white")
btn_on.place(x=80, y=80)  

btn_off = tk.Button(root, text="LED 끄기", command=lambda: send_signal('2', "LED 꺼짐 신호 전송!"),
                    bg="red", fg="white")
btn_off.place(x=180, y=80) 

root.mainloop()


