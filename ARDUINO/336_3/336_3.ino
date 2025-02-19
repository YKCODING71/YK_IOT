const int led[6] = { 3, 5, 6, 9, 10, 11 };
const int analogPin = A0;

void setup() {
  
}

void loop() {
  int sensorInput = analogRead(analogPin);

  for(int n=0;n<=5;n++) {
    int sLow = 171 * n;     
    int sHigh = 171 * (n + 1);
      
    if(sensorInput/171>=1+n)      // 171*(1+n) 이상이면
      analogWrite(led[n], 255);
    else if(sensorInput/171>=0+n) // 171*(0+n) 이상이면
      analogWrite(led[n], map(sensorInput,sLow,sHigh, 0, 255));
  }
}
