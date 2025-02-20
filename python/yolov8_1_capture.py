import cv2
import os
#import time

def capture_image():
    image_count = 0
    cap = cv2.VideoCapture(0)
    save_directory = "img_capture"
c
    os.makedirs(save_directory, exist_ok=True)
    while True:
        ret, frame = cap.read()
        
        cv2.imshow("Webcam", frame)

        key = cv2.waitKey(1)
        if key == ord('c'):
            file_name = f'{save_directory}/img_{image_count}.jpg'
            cv2.imwrite(file_name, frame)
            print(f"Image saved. name:{file_name}")
            image_count += 1
        
        elif key == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()
    

capture_image()
