#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define TRIG 11
#define ECHO 12

float xPos=0, yPos=0;
float senses[20][3];
int count = 0;
int side = 0;
int angle=0;

Adafruit_SSD1306 oled(128,64,&Wire, -1);

void setup(){
  oled.begin(SSD1306_SWITCHCAPVCC,0x3C);
  delay(2000);
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,OUTPUT);
  Serial.begin(115200);  
}

void loop(){
  if(angle == 0) side = 1;        //정방향
  else if(angle==180) side = -1;  //역방향
  graph(distance());
  angle += side; 
}

int distance(){
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  long duration = pulseIn(ECHO,HIGH,5900)/58;
  Serial.println(duration);
  return duration;
}

void graph(int value){ 
  oled.clearDisplay();
  oled.drawCircle(64,63,60,WHITE);
  oled.drawCircle(64,63,48,WHITE);
  oled.drawCircle(64,63,36,WHITE);
  oled.drawCircle(64,63,24,WHITE);
  oled.drawCircle(64,63,12,WHITE);

  xPos = 64 - cos(radians(180-angle))*60;
  yPos = 64 - sin(radians(180-angle))*60;
  oled.drawLine(64,63,xPos,yPos,WHITE);

  long x = 0, y = 0;
  if (value>0){
    x = 64-(cos(radians(180-angle)) * ((value*0.1)*60.0));
    y = 64-(sin(radians(180-angle)) * ((value*0.1)*60.0));
    senses[count][0] = x;
    senses[count][1] = y;
    senses[count][2] = 1;
    count += 1;
    if(count == 20)count = 0;
  }
  for(int i=0; i<20;i++){
    if(senses[i][2] == 0 || senses[i][2]>30){
      continue;
    }
    oled.drawCircle(senses[i][0],senses[i][1],3,WHITE);
    senses[i][2] += 1;
  }
  oled.display();
}
