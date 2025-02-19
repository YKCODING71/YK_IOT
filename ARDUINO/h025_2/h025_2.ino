#define SWACT 0
long dTime = 100;
long lTime = 0;
long nowTime=0;

int button = 2;
int ledStatus = 0;

int A_IA = 10;
int A_IB = 9;
int DCspeed = 0;

int RED = 5;
int GREEN = 6;
int BLUE = 11;

int count = 0;

void setup(){
  pinMode(button,INPUT_PULLUP);
  Serial.begin(115200);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
  pinMode(A_IA,OUTPUT);
  pinMode(A_IB,OUTPUT);
  analogWrite(A_IA,0);
  analogWrite(A_IB,0);
  color(0,0,255);
}

void loop(){
  nowTime= millis();
  
  if(swchk(button)== 1){ 
    count += 1;
    if (count==1){
      DCspeed = 100;
      color(0,255,0);
    }
    else if(count == 2){
      DCspeed = 200;
      color(255,0,0);
    }
    else if(count == 3){
      DCspeed = 0;
      count = 0;
      color(0,0,255);
    }
    motor(DCspeed);
    Serial.print(DCspeed);
    Serial.print('\t');
    Serial.println(count);
  }  
}

void color(int r, int g, int b){
  analogWrite(RED,r);
  analogWrite(GREEN,g);
  analogWrite(BLUE,b);
  delay(1000);
}

void motor(int data){
  analogWrite(A_IA,0);
  analogWrite(A_IB,data);
}

//-------------------------------------------

int swchk(int bt){
  int st = 0;
  if(digitalRead(bt) == SWACT){
    if((nowTime-lTime)>dTime) st = 1;
    else st = 0;
    lTime = nowTime;  
  }
  return st;
}
