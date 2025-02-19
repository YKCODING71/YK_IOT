// 핀 설정
const int buttonPin = 2;     // 버튼이 연결된 핀
const int redPin = 9;        // 빨간색 LED 핀
const int greenPin = 10;     // 초록색 LED 핀
const int bluePin = 11;      // 파란색 LED 핀

// 변수 선언
int buttonState = 0;         // 버튼 상태
int lastButtonState = 0;     // 이전 버튼 상태
unsigned long lastDebounceTime = 0;  // 마지막 버튼 상태 변화 시간
unsigned long debounceDelay = 50;    // 디바운스 지연 시간 (50ms)

int colorState = 0;          // 현재 색 상태 (0 = 빨강, 1 = 초록, 2 = 파랑)

// setup 함수
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // 버튼 핀을 풀업 모드로 설정
  pinMode(redPin, OUTPUT);           // 빨간색 LED 핀을 출력 모드로 설정
  pinMode(greenPin, OUTPUT);         // 초록색 LED 핀을 출력 모드로 설정
  pinMode(bluePin, OUTPUT);          // 파란색 LED 핀을 출력 모드로 설정
  Serial.begin(115200);                // 디버깅을 위한 직렬 통신 시작
}

// loop 함수
void loop() {
  int reading = digitalRead(buttonPin);  // 버튼의 현재 상태를 읽어옴

  // 버튼 상태가 변화했을 때만 디바운스를 적용
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // 상태 변화 시간 갱신
  }

  // 디바운스 시간 이후에 버튼 상태를 확인
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;  // 버튼 상태 업데이트

      // 버튼이 눌렸을 때 (LOW 상태)
      if (buttonState == LOW) {
        // 색 상태를 변경하고 LED 색상 변경
        colorState = (colorState + 1) % 3;  // 0 -> 1 -> 2 순으로 반복

        // 색에 맞는 LED 켜기
        if (colorState == 0) {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          digitalWrite(bluePin, LOW);
          Serial.println("빨간색");
        } else if (colorState == 1) {
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, HIGH);
          digitalWrite(bluePin, LOW);
          Serial.println("초록색");
        } else if (colorState == 2) {
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, LOW);
          digitalWrite(bluePin, HIGH);
          Serial.println("파란색");
        }
      }
    }
  }

  lastButtonState = reading;  // 마지막 상태를 업데이트
}
