int MaxNum(int n1, int n2, int n3){
  if(n1>n2)
    return (n1>n3) ? n1 : n3;
  else
    return (n2>n3) ? n2 : n3;
}

int MinNum(int n1, int n2, int n3){
  if(n1<n2)
    return (n1<n3) ? n1 : n3;
  else
    return (n2<n3) ? n2 : n3;
}

void setup(){
  Serial.begin(115200);
}

void loop(){
  Serial.print("세 개의 정수 입력 : ");

  while(!Serial.available());
  int n1 = Serial.parseInt();
  int n2 = Serial.parseInt();
  int n3 = Serial.parseInt();

  Serial.print(n1);
  Serial.print(',');
  Serial.print(n2);
  Serial.print(',');
  Serial.println(n3);

  Serial.print("가장 큰 수 : ");
  Serial.println(MaxNum(n1,n2,n3));
  Serial.print("가장 작은 수 : ");
  Serial.println(MinNum(n1,n2,n3));

}
