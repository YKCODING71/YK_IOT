#define RED_PIN 4   // 빨간색 핀
#define GREEN_PIN 15 // 초록색 핀
#define BLUE_PIN 2  // 파란색 핀

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  Serial.begin(115200); // 컴퓨터와 통신
}

void loop() {
  if (Serial.available() > 0) {
    char received = Serial.read(); // 데이터 수신
    Serial.print("Received: ");
    Serial.println(received);

    if (received == 'R') {
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);

    } else if (received == 'G') {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 0);
    } else if (received == 'B') {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 255);
    }
    else{
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
    }
  }
}
