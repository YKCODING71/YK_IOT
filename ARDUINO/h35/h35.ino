int RED = 9;
int GREEN = 10;
int BLUE = 11;

void setup(){
  Serial.begin(115200);
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(BLUE,OUTPUT);
}

void loop(){
  if(Serial.available()){
    long num1 = Serial.parseInt();
    long num2 = Serial.parseInt();
    long num3 = num1+num2;

    Serial.print("num1 = ");
    Serial.println(num1);
    Serial.print("num2 = ");
    Serial.println(num2);
    Serial.print("num3 = ");
    Serial.println(num3);

    if(num3>=100){
      digitalWrite(RED,HIGH);
      digitalWrite(GREEN,LOW);
    }
    else if(num3 >=50){
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,HIGH);
    }
    else{
      digitalWrite(RED,LOW);
      digitalWrite(GREEN,LOW);
    }
  }
}
