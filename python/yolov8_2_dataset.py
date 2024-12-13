#train 70%, test 20%, valid 10%

import os
import shutil
import random

# 경로 설정
ROOT_DIR = r"C:\mywork"
train_ratio = 0.7
test_ratio = 0.2
valid_ratio = 0.1


img_dir = os.path.join(ROOT_DIR, "img_capture")
lbl_dir = os.path.join(ROOT_DIR, "img_labels")

# 데이터 분할 폴더 경로
train_img_dir = os.path.join(ROOT_DIR, "train", "images")
train_lbl_dir = os.path.join(ROOT_DIR, "train", "labels")

test_img_dir = os.path.join(ROOT_DIR, "test", "images")
test_lbl_dir = os.path.join(ROOT_DIR, "test", "labels")

valid_img_dir = os.path.join(ROOT_DIR, "valid", "images")
valid_lbl_dir = os.path.join(ROOT_DIR, "valid", "labels")

# 필요한 폴더가 없다면 생성
for directory in [train_img_dir, train_lbl_dir, test_img_dir, test_lbl_dir, valid_img_dir, valid_lbl_dir]:
    os.makedirs(directory, exist_ok=True)

# 이미지 파일 리스트 가져오기
img_files = [f for f in os.listdir(img_dir) if f.endswith('.jpg')]

# 데이터 셔플링 (랜덤 분할을 위해)
random.shuffle(img_files)

# 데이터 분할 비율 설정 (예: 70% train, 20% test, 10% valid)


# 분할 인덱스 계산
total_imgs = len(img_files)
train_idx = int(total_imgs * train_ratio)
test_idx = train_idx + int(total_imgs * test_ratio)

# 데이터 분할
train_files = img_files[:train_idx]
test_files = img_files[train_idx:test_idx]
valid_files = img_files[test_idx:]

# 파일 복사 함수
def copy_files(img_files, img_dest_dir, lbl_dest_dir):
    move_nums = 0
    for img_file in img_files:
        try:
            # 이미지 파일 복사
            shutil.copy(os.path.join(img_dir, img_file), os.path.join(img_dest_dir, img_file))

            # 라벨 파일 복사 (이미지 파일명에서 확장자만 변경)
            label_file_name = img_file.replace('.jpg', '.txt')
            shutil.copy(os.path.join(lbl_dir, label_file_name), os.path.join(lbl_dest_dir, label_file_name))

            move_nums += 1
        except Exception as err:
            print(f"Error copying {img_file}: {err}")

    print(f'Total files moved: {move_nums}')
    print('========================================================================')

# 파일 복사 실행
copy_files(train_files, train_img_dir, train_lbl_dir)
copy_files(test_files, test_img_dir, test_lbl_dir)
copy_files(valid_files, valid_img_dir, valid_lbl_dir)