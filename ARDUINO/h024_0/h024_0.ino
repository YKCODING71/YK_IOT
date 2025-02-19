int A_IA = 10;   
int A_IB = 9;
int A_speed = 0;
void setup() {
  Serial.begin(115200);
  analogWrite(A_IA,A_speed);
  analogWrite(A_IB,0);
}

void loop() {
  if (Serial.available()>0){
    char c = Serial.read();
    
    if(c=='f')A_speed = 128;
    else if( c=='s')A_speed = 0;
    
    analogWrite(A_IA,A_speed);
    analogWrite(A_IB,0);
  }  
 }

 
