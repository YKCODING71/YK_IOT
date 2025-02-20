const int led[6] = { 3, 5, 6, 9, 10, 11 };
const int analogPin = A0;

void setup() {
  
}

void loop() {
  int sensorInput = analogRead(analogPin);

  if(sensorInput/171>=1+0)      
    analogWrite(led[0], 255);     // 171로 나눈 몫이 1이면 1구간 MAX
  else if(sensorInput/171>=0+0)   // 0구간이상(첫번째)
    analogWrite(led[0], int(sensorInput%171/171.0*255)); // map((0~171) --> (0~255))
                                  
  if(sensorInput/171>=1+1)        // 171로 나눈 몫이 2이면 2구간 MAX
    analogWrite(led[1], 255); 
  else if(sensorInput/171>=0+1)   // 1구간이상(두번째구간)
    analogWrite(led[1], int(sensorInput%171/171.0*255));
      

  if(sensorInput/171>=1+2)      // 171*3 이상이면
    analogWrite(led[2], 255);
  else if(sensorInput/171>=0+2) // 171*2 이상이면
    analogWrite(led[2], int(sensorInput%171/171.0*255));

  if(sensorInput/171>=1+3) // 171*4 이상이면
    analogWrite(led[3], 255);
  else if(sensorInput/171>=0+3) // 171*3 이상이면
    analogWrite(led[3], int(sensorInput%171/171.0*255));

  if(sensorInput/171>=1+4) // 171*5 이상이면
    analogWrite(led[4], 255);
  else if(sensorInput/171>=0+4) // 171*4 이상이면
    analogWrite(led[4], int(sensorInput%171/171.0*255));

  if(sensorInput/171>=1+5) // 171*6 이상이면
    analogWrite(led[5], 255);
  else if(sensorInput/171>=0+5) // 171*5 이상이면
    analogWrite(led[5], int(sensorInput%171/171.0*255));
}
