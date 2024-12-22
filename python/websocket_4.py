import tkinter as tk
import websocket
import threading
import time

ws = websocket.WebSocket()
ws.connect("ws://192.168.45.78")
print("Connected to WebSocket server")

root = tk.Tk()
root.title("ESP32 웹소켓 통신")
root.geometry("400x300")  

temperature_text = tk.Text(root, height=5, width=40, wrap=tk.WORD)
temperature_text.place(x=50, y=180)  
label = tk.Label(root, text="온도/습도 데이터 수신")
label.place(x=120, y=20)

def send_signal(signal, message):
    #label.config(text=message)  # 메시지를 레이블에 출력
    ws.send(signal)              # WebSocket으로 메시지 전송
    response = ws.recv()         # 서버로부터 수신된 메시지
    add_temperature(response)
    
def add_temperature(temp_data):
    temperature_text.insert(tk.END, f"{temp_data}\n")
    lines = temperature_text.get("1.0", tk.END).strip().split('\n')
                                                #strip()공백제거, '\n'기준으로 나눈 수 반환
    if len(lines) > 5:                          # \n이 5줄이 넘으면, 첫줄삭제
        temperature_text.delete("1.0", "2.0")   # 첫 번째 줄 ~ 두번째줄직전까지 삭제
    
    #"Temp: 23.20C, Humidity: 50.40%"
    start = temp_data.find(":") + 2             # ':' 뒤의 숫자 시작 위치
    end = temp_data.find("C")                   # 'C'의 위치
    temperature = float(temp_data[start:end].strip())  #strip()공백 제거거
   
    if temperature >= 30:
        temperature_text.config(bg="red")

    else:
        temperature_text.config(bg="white")

    
def request_temperature_humidity_auto():
    while True:
        send_signal('3', "온습도 센서 데이터 요청 중...")
        time.sleep(2)                 

thread = threading.Thread(target=request_temperature_humidity_auto, daemon=True)
thread.start()
root.mainloop()

ws.close()
