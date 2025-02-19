int NumberCompare(int num1, int num2);

void setup(){
  Serial.begin(115200);
}

void loop(){
  Serial.print("3과 4중에서 큰 수 : ");
  Serial.println(NumberCompare(3,4));
  Serial.print("7과 2중에서 큰 수 : ");
  Serial.println(NumberCompare(7,2));
  while(1);
}

int NumberCompare(int num1, int num2){
  if(num1>num2)
    return num1;
  else 
    return num2;  
}
