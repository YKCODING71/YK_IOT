#pip install pyserial

import serial
import time

# ESP32의 직렬 포트 설정 (사용자의 ESP32 포트에 맞게 설정)
ser = serial.Serial('COM3', 115200)  # 예시: COM6, ESP32의 직렬 포트 번호

# RGB 값 전송 (빨강, 초록, 파랑 값)
while True:
    # 예시로 빨강: 255, 초록: 0, 파랑: 0 (빨간색)
    ser.write(f"255,0,0\n".encode())  # 빨간색
    time.sleep(1)

    # 초록: 0, 파랑: 255 (파란색)
    ser.write(f"0,0,255\n".encode())  # 파란색
    time.sleep(1)

    # 빨강: 0, 초록: 255, 파랑: 0 (초록색)
    ser.write(f"0,255,0\n".encode())  # 초록색
    time.sleep(1)