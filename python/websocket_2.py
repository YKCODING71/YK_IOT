import tkinter as tk
import websocket

ws = websocket.WebSocket()
ws.connect("ws://192.168.45.78")
print("Connected to WebSocket server")

root = tk.Tk()
root.title("ESP32 웹소켓 통신")
root.geometry("320x200")  # 창 크기 설정

label = tk.Label(root, text="아래 버튼을 눌러보세요!")
label.place(x=120, y=20)

def send_signal(signal, message):
    #label.config(text=message) # 메시지를 레이블에 출력
    ws.send(signal)             # WebSocket으로 메시지 전송
    response = ws.recv()        # 서버로부터 수신된 메시지
    label.config(text=f"수신된 메시지: {response}")  

btn_on = tk.Button(root, text="LED 켜기", command=lambda: send_signal('1', "LED 켜짐 신호 전송!"),
                   bg="green", fg="white")
btn_on.place(x=80, y=80)  

btn_off = tk.Button(root, text="LED 끄기", command=lambda: send_signal('2', "LED 꺼짐 신호 전송!"),
                    bg="red", fg="white")
btn_off.place(x=180, y=80)  

root.mainloop()
ws.close()
