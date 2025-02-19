#include<TimerOne.h>

int LED = 13;
int state = 0;
int tValue = 0;
int tDelay=0;
void setup() {
  pinMode(LED,OUTPUT);
  Timer1.initialize(1000);   //초기화
  Timer1.attachInterrupt(t1msec);
  Serial.begin(115200);
}

void loop() {
  if(tDelay>=100){
    tDelay=0;
    digitalWrite(LED, state^=1 );
  }
}

void t1msec(){
  Serial.println(tValue);
  if(++tValue>=10){
    tValue=0;
    tDelay++; 
  }  
}
