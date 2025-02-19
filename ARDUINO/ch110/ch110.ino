#include <SoftwareSerial.h>
SoftwareSerial my1(6,7);

void setup() {
  Serial.begin(115200);
  my1.begin(115200);
}

void loop() { 
  if (Serial.available()>0) {
    char a = Serial.read();
    my1.write(a);
  }
  if (my1.available()>0) {
    char a = my1.read();
    Serial.write(a);
  } 
}
