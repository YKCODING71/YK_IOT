void setup(){
  Serial.begin(115200);
}

void loop(){
  int a = Serial.parseInt();
  int b = Serial.parseInt();

  int r1 = NumberCompare1(a,b);
  Serial.print("큰수 : ");
  Serial.println(r1);

  int r2 = NumberCompare2(a,b);
  Serial.print("작은수 : ");
  Serial.println(r2);
}

int NumberCompare1(int num1, int num2){
  if(num1>num2)
    return num1;
  else 
    return num2;  
}

int NumberCompare2(int num1, int num2){
  if(num1<num2)
    return num1;
  else 
    return num2;  
}
