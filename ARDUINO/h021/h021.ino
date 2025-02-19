const int ledPin =  10;
int state = 0;
int tDelay= 1000;
long oldTime = 0;

void setup() { 
  pinMode(ledPin,OUTPUT);
}

void loop() {
  long now = millis();
  if(now-oldTime > tDelay){
    digitalWrite(ledPin, state ^=1);
    oldTime = now;
  }
}
