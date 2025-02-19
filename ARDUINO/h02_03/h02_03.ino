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
  if(Serial.available()>0){
    String color = Serial.readStringUntil('\n');
    Serial.print("color = ");
    Serial.println(color);

    if((color == "RED")||(color == "red")){
      digitalWrite(RED,HIGH);
    }  
    else if((color =="GREEN")||(color == "green")){
      digitalWrite(GREEN,HIGH);
    }
    else if((color =="BLUE")||(color == "blue")){
      digitalWrite(BLUE,HIGH);
    }
    
    delay(1000);
    digitalWrite(RED,LOW);
    digitalWrite(GREEN,LOW);
    digitalWrite(BLUE,LOW);
  }
}
