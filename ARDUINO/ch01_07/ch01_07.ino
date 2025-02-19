void setup() {
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()>0){
    char command=Serial.read();
    if(command == 'a'){
      Serial.println(command-32);
      Serial.write(command-32);
      Serial.println();
    }
  }
}
