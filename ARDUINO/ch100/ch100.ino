#include<TimerOne.h>

int LED = 13;
int state = 0;
void setup() {
  pinMode(LED,OUTPUT);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(t1sec);
}

void loop() {

}

void t1sec(){
  digitalWrite(LED, state^=1 );
}
