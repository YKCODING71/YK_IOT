#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "images.h"           // 이미지 파일을 포함하는 헤더 파일

#define SCREEN_WIDTH 128      // OLED 디스플레이의 너비 (픽셀 단위)
#define SCREEN_HEIGHT 32      // OLED 디스플레이의 높이 (픽셀 단위)

#define OLED_RESET -1         // 리셋 핀 번호 # (아두이노 리셋 핀을 공유하는 경우 -1)
#define SCREEN_ADDRESS 0x3C   //128x64의 경우 0x3D, 128x32의 경우 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

   if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  
  }

  display.display();
  delay(2000);  

  display.clearDisplay();       // 디스플레이 지우기

  display.drawBitmap(
    0,
    0,
    epd_bitmap_s1, 32, 32, 1);  

  display.drawBitmap(
    32,
    0,
    epd_bitmap_s2, 32, 32, 1);  

  display.drawBitmap(
    64,
    0,
    epd_bitmap_s3, 32, 32, 1);  

  display.drawBitmap(
    96,
    0,
    epd_bitmap_s4, 32, 32, 1);  

  display.display();
}

void loop() {
}