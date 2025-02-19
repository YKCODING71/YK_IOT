#include <ArduinoWebsockets.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void stop(){
  Serial.println("stop");
  delay(200);
}


void setup() {
  Serial.begin(115200);
  SerialBT.begin("KAIROS 1"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  if (SerialBT.available()) {
    char c = SerialBT.read();
    Serial.println(c);
  if (Serial.available()){
    char bt = Serial.read();
    SerialBT.write(bt);
  }
}
