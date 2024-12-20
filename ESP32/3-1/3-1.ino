const int ledPin = 4;//led 핀 번호 설절
// setup함수는 리셋을 누르거나 보드에 전원을 공급할 때 한 번 실행됩니다.
void setup() {
  pinMode(ledPin, OUTPUT);//ledPin을 출력으로 설정
}
 
// loop 함수는 전원이 꺼질때까지 계속해서 실행됩니다.
void loop() {
  digitalWrite(ledPin, HIGH); //ledPin에 HIGH값 쓰기
  delay(1000);                    // 1초 기다리기
  digitalWrite(ledPin, LOW);  //ledPin에 LOW값 쓰기
  delay(1000);                    // 1초 기다리기
}