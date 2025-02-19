const unsigned int led[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int cnt = 0;

void setup() {
  for(int x=0;x<=7;x++) {
    pinMode(led[x], OUTPUT);
  }   
}

void loop() {
  for(int x=0;x<=7;x++) {
    for(int x=0;x<=7;x++) {
      digitalWrite(led[x], LOW);
    }
    for(int x=0;x<=7;x++){
      digitalWrite(led[x], 0x01&(cnt>>x));
    }
  }  
  ++cnt;
  delay(1000);
}
