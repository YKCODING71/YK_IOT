void setup(){
  Serial.begin(115200);
  
  Serial.print("char 크기 : ");
  Serial.println(sizeof(char));
  Serial.print("unsigned char 크기 : ");
  Serial.println(sizeof(unsigned char));
  Serial.print("byte 크기 : ");
  Serial.println(sizeof(byte));
  Serial.print("int 크기 : ");
  Serial.println(sizeof(int));
  Serial.print("float 크기 : ");
  Serial.println(sizeof(float));
  Serial.print("long 크기 : ");
  Serial.println(sizeof(long));
  Serial.print("unsigned long 크기 : ");
  Serial.println(sizeof(unsigned long));
  Serial.print("double 크기 : ");
  Serial.println(sizeof(double));
}
void loop(){

}
