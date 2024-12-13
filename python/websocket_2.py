import tkinter as tk
import websocket

# WebSocket 서버 주소
ws = websocket.WebSocket()
ws.connect("ws://172.30.1.19")
print("Connected to WebSocket server")

# tkinter GUI 설정
root = tk.Tk()
root.title("WebSocket Client")

# 출력창
output_box = tk.Text(root, height=15, width=50, state="normal")
output_box.pack()

# 입력창
input_box = tk.Entry(root, width=50)
input_box.pack()

# 전송 버튼 클릭 시 동작
def on_send_click():
    # 1. 입력창에서 메시지를 가져옵니다.
    message = input_box.get()
    
    # 2. 만약 입력창에 메시지가 비어있지 않으면
    if message:
        try:
            # 3. 메시지를 WebSocket 서버로 전송합니다.
            ws.send(message)
            # 4. 전송한 메시지를 출력창에 보여줍니다.
            output_box.insert(tk.END, f"Me: {message}\n")
            
            # 5. 서버로부터 응답을 기다립니다.
            response = ws.recv()
            # 6. 서버에서 받은 응답을 출력창에 표시합니다.
            output_box.insert(tk.END, f"Server: {response}\n")
        
        except Exception as e:
            # 7. 예외가 발생하면 오류 메시지를 출력창에 표시합니다.
            output_box.insert(tk.END, f"Error: {e}\n")
        
        # 8. 입력창을 비웁니다. 새로운 메시지를 입력할 수 있게 합니다.
        input_box.delete(0, tk.END)

# 전송 버튼 설정
send_button = tk.Button(root, text="Send", command=on_send_click)
send_button.pack()

# 초기 메시지
output_box.insert(tk.END, "메시지를 입력하고 Send 버튼을 클릭하세요.\n")

# GUI 실행
root.mainloop()

# 종료 시 WebSocket 연결 닫기
ws.close()
print("연결이 종료되었습니다.")
