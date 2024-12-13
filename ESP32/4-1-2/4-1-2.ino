#define RED_PIN 4   // 빨간색 핀
#define GREEN_PIN 15 // 초록색 핀
#define BLUE_PIN 2  // 파란색 핀

void setup() {
  // 핀 설정
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
 
  // 시리얼 통신 시작
  Serial.begin(115200);  // 시리얼 통신 시작 (115200 보드레이트)
 
  // 모든 핀을 HIGH로 설정하여 LED를 꺼진 상태로 초기화합니다.
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
 
  Serial.println("시리얼 통신을 통해 R, G, B, W, O 문자를 입력하여 LED 색상을 제어하세요.");
}

void loop() {
  // 시리얼 통신으로 받은 문자 읽기
  if (Serial.available()) {
    char receivedChar = Serial.read();  // 시리얼에서 받은 문자

    if (receivedChar == 'R') {
      // 빨강
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 255);
      Serial.println("빨강색");
    }
    else if (receivedChar == 'G') {
      // 초록
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 255);
      Serial.println("초록색");
    }
    else if (receivedChar == 'B') {
      // 파랑
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 0);
      Serial.println("파랑색");
    }
    else if (receivedChar == 'W') {
      // 백색
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
      Serial.println("백색");
    }
    else if (receivedChar == 'O') {
      // 끄기
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 255);
      Serial.println("LED 끄기");
    }
  }
  delay(100);  // 처리 속도를 적당히 조절
}

