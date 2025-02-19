int RED = 11;
int GREEN = 10;
int BLUE = 9;

void color(int r, int g, int b);

void setup(){
  
}

void loop(){
  color(255,0,0);
  color(0,255,0);
  color(0,0,255);
  color(255,255,0);
  color(255,0,255);
  color(0,255,255);
  color(255,255,255);
}

void color(int r, int g, int b){
  analogWrite(RED,r);
  analogWrite(GREEN,r);
  analogWrite(BLUE,r);
  delay(1000);
}  
