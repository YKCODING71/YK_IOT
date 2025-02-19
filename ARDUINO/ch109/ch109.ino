void setup() {
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,16,17);
}
void loop() { 
  if (Serial.available()>0) {
    char a = Serial.read();
    Serial2.write(a);
  }
  if (Serial2.available()>0){
    char a = Serial.read();
    Serial.write(a);
  }
}
