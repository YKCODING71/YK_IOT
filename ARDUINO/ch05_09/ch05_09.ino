int flame = A0;
int LED = 6;
int buzzer = 12;
int val=0;

void setup(){
  pinMode(buzzer,OUTPUT);
  pinMode(LED,OUTPUT);
  Serial.begin(9600);      
}

void loop(){
  val = analogRead(flame);  
  Serial.println(val);
   
  if(val>=100){
    digitalWrite(LED,HIGH);
    tone(buzzer,320,200);
    delay(400);
    digitalWrite(LED,LOW);
    noTone(buzzer);
  }
  else{
    digitalWrite(LED,LOW);
    noTone(buzzer);
  }
}
