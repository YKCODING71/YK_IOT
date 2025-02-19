#define MOTOR_SP 100
#define INTERVAL 1000

int A_IA = 10;  // 첫 번째 모터의 I핀
int A_IB = 9;   // 첫 번째 모터의 B핀
int A_ENCODER = 2;  // 첫 번째 엔코더 핀

int B_IA = 5;  // 두 번째 모터의 I핀
int B_IB = 6;  // 두 번째 모터의 B핀
int B_ENCODER = 3;  // 두 번째 엔코더 핀

volatile int A_cnt = 0;  // 첫 번째 엔코더 카운터
volatile int B_cnt = 0;  // 두 번째 엔코더 카운터

int A_speed = 0;  // 첫 번째 모터 속도
int B_speed = 0;  // 두 번째 모터 속도

unsigned long oldTime = 0;
unsigned long newTime = 0;

void A_ISR() {
  A_cnt++;
}

void B_ISR() {
  B_cnt++;
}

void setup() {
  Serial.begin(115200);

  // 핀 모드 설정
  pinMode(A_ENCODER, INPUT_PULLUP);
  pinMode(B_ENCODER, INPUT_PULLUP);
  pinMode(A_IA, OUTPUT);
  pinMode(A_IB, OUTPUT);
  pinMode(B_IA, OUTPUT);
  pinMode(B_IB, OUTPUT);

  // 인터럽트 설정
  attachInterrupt(digitalPinToInterrupt(A_ENCODER), A_ISR, FALLING);  // 첫 번째 엔코더
  attachInterrupt(digitalPinToInterrupt(B_ENCODER), B_ISR, FALLING);  // 두 번째 엔코더
}

void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'f') {
      A_speed = 0;
      B_speed = 0;
    } else if (c == 's') {
      A_speed = 0;
      B_speed = 0;
    }
  }

  newTime = millis();
  if (newTime - oldTime > INTERVAL) {
    oldTime = newTime;

    // 인터럽트를 끄고 카운터 값 읽기
    noInterrupts();
    Serial.print("A_cnt : ");
    Serial.println(A_cnt);
    Serial.print("B_cnt : ");
    Serial.println(B_cnt);
    
    // 카운터 값 리셋
    A_cnt = 0;
    B_cnt = 0;

    // 모터 속도 설정
    analogWrite(A_IA, A_speed);
    analogWrite(A_IB, 0);
    analogWrite(B_IA, B_speed);
    analogWrite(B_IB, 0);

    interrupts();
  }
}
