#include <Wire.h>
#include <Adafruit_SSD1306.h>
 
Adafruit_SSD1306 oled(123, 64, &Wire, -1);
 
void setup() {
 oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3D for 128x64

 oled.clearDisplay();
 
  // 텍스트 출력
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,27);
  oled.println("Hello CodingArray!");
  oled.display();
  delay(2000);
  oled.clearDisplay();
   
  // 텍스트 반전 표시
  oled.setTextColor(BLACK, WHITE); // 'inverted' text
  oled.setCursor(0,27);
  oled.println("Hello CodingArray!");
  oled.display();
  delay(2000);
  oled.clearDisplay();
   
  // 글꼴 크기 조정
  oled.setTextColor(WHITE); 
  oled.setCursor(0,23);
  oled.setTextSize(3);
  oled.println("Hello!");
  oled.display();
  delay(2000);
  oled.clearDisplay();
   
  // 숫자 표시
  oled.setTextSize(1);
  oled.setCursor(0,27);
  oled.println(123456789);
  oled.display();
  delay(2000);
  oled.clearDisplay();
   
  // 숫자에 대한 포멧 지정
  oled.setCursor(0,28);
  oled.print("0x"); 
  oled.print(0xFF, HEX);
  oled.print("(HEX) = ");
  oled.print(0xFF, DEC);
  oled.println("(DEC)");
  oled.display();
  delay(2000);
  oled.clearDisplay();
   
  // ASCII 기호표시
  oled.setCursor(0,24);
  oled.setTextSize(3);
  oled.write(3); // 3 <-: 하트모양
  oled.display();
  delay(2000);
  oled.clearDisplay();
   
  // 전체화면 스크롤링
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.println("Full");
  oled.println("Screen");
  oled.println("Scrolling!");
  oled.display();
  oled.startscrollright(0x00, 0x07);
  delay(2000);
  oled.stopscroll();
  delay(1000);
  oled.startscrollleft(0x00, 0x07);
  delay(2000);
  oled.stopscroll();
  delay(1000);
  oled.startscrolldiagright(0x00, 0x07);
  delay(2000);
  oled.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  oled.stopscroll();
  oled.clearDisplay();
   
  // 특정부분 스크롤링
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.println("Scroll");
  oled.println("Some part");
  oled.println("Of the screen.");
  oled.display();
  oled.startscrollright(0x00, 0x00);
}
 
void loop() {
}
 
 
