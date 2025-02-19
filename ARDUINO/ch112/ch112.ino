#include <ESP32Servo.h>
#include "BluetoothSerial.h"

#define SERVO1  26
#define SERVO2  27

Servo myservo1, myservo2, myservo3, myservo4;
BluetoothSerial SerialBT;

void servo_center(){
  myservo1.write(90);
  myservo2.write(90);
}

void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

  myservo1.setPeriodHertz(50);    // standard 50 hz servo
  myservo1.attach(SERVO1, 500, 2400);
  myservo2.setPeriodHertz(50); 
  myservo2.attach(SERVO2, 500, 2400);
  SerialBT.begin("KAIROS 1"); //Bluetooth device name
  Serial.begin(115200);
}

int angle1 = 90;
int angle2 = 90;

void loop() {
  if (SerialBT.available()) {
    char c = SerialBT.read();
    if(c == 'a'){
      Serial.println(c);
      myservo1.write(120);
    }else if(c =='w'){
      Serial.println(c);
      myservo1.write(90);
    }
  }
}
