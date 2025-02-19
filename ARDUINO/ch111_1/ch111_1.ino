#include <ArduinoWebsockets.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

#define M1_B    22
#define M1_A    23
#define M2_B    12
#define M2_A    14

void go_forward(){
  Serial.println("forward");
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, HIGH);
}

void go_backward(){
  Serial.println("backward");
  digitalWrite(M1_A, HIGH);
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_A, HIGH);
  digitalWrite(M2_B, LOW);
}

void turn_right(){
  Serial.println("right");
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, HIGH);
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, HIGH);
}

void turn_left(){
  Serial.println("left");
  digitalWrite(M1_A, HIGH);
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_A, HIGH);
  digitalWrite(M2_B, LOW);
}

void stop(){
  Serial.println("stop");
  digitalWrite(M1_A, LOW);
  digitalWrite(M1_B, LOW);
  digitalWrite(M2_A, LOW);
  digitalWrite(M2_B, LOW);
  delay(200);
}


void setup() {
  Serial.begin(115200);
  SerialBT.begin("KAIROS 1"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(M1_A, OUTPUT);
  pinMode(M1_B, OUTPUT);
  pinMode(M2_A, OUTPUT);
  pinMode(M2_B, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.println(c);
    if(c == 'f'){
      SerialBT.println("forward");
      go_forward();
    }else if(c == 'b'){
      SerialBT.println("backward");
      go_backward();
    }else if(c == 'l'){
      SerialBT.println("turn left");
      turn_left();
    }else if(c == 'r'){
      SerialBT.println("turn right");
      turn_right(); 
    }else if(c == 'p'){
      stop();
    }
  }
}
