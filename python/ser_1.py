import tkinter as tk

# 기본 창 생성
root = tk.Tk()
root.title("Place 레이아웃 예시")
root.geometry("320x200")  # 창 크기 설정 (너비x높이)

# 레이블 추가 (위치: (x=100, y=50) 절대 좌표)
label = tk.Label(root, text="여기는 절대 좌표")
label.place(x=100, y=50)

# 버튼 추가 (위치: 창의 50% 지점에 배치)
button = tk.Button(root, text="클릭하세요")
button.place(relx=0.5, rely=0.5, anchor="center")  # 창의 중심에 배치

# 이벤트 루프 실행
root.mainloop()
