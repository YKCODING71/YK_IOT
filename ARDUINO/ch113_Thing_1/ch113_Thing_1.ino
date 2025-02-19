#include <WiFi.h>              // WiFi 연결을 위한 라이브러리 포함
#include "ThingSpeak.h"       // ThingSpeak 데이터 전송을 위한 라이브러리 포함
#include <DHT.h>              // DHT 센서를 위한 라이브러리 포함
#include <DHT_U.h>            // DHT 통합 라이브러리 포함

#define DHTPIN  4             // DHT 센서가 연결된 핀 번호 정의
#define DHTTYPE DHT11         // DHT 센서 타입 정의 (DHT11)

DHT dht(DHTPIN, DHTTYPE);       // DHT 센서 객체 생성

// WiFi 연결을 위한 SSID 및 비밀번호
char ssid[] = "ConnectValue_C401_2G";  
char pass[] = "CVC401!@#$";   

// WiFi 클라이언트 인스턴스 생성
WiFiClient client;

                                          // ThingSpeak 설정
unsigned long ChannelNumber = 1;          // ThingSpeak 채널 번호
const char * APIKey = "2QVMRN4EUOEC5KF8"; // ThingSpeak API 키

float t = 0;                        // 온도를 저장할 변수

void setup() {
  Serial.begin(115200);            // 시리얼 통신 초기화 (115200 보드레이트)
  while (!Serial);                 // 시리얼 포트가 연결될 때까지 대기

  dht.begin();                     // DHT 센서 초기화

  WiFi.mode(WIFI_STA);             // WiFi 모드를 스테이션(클라이언트)으로 설정
  ThingSpeak.begin(client);        // ThingSpeak 클라이언트 초기화
}

void loop() {
  int statusCode = 0;              // ThingSpeak의 응답 상태 코드를 저장할 변수

  // WiFi 연결 상태 확인
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println("ConnectValue_C401_2G"); // 연결 시도 중 SSID 출력

    // WiFi에 연결 시도
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass);      // SSID 및 비밀번호로 WiFi 연결 시작
      Serial.print(".");           // 연결 시도 중 점 출력
      delay(5000);                 // 5초 대기 후 재시도
    } 
    Serial.println("\nConnected"); // 연결 성공 메시지 출력
  }

  delay(5000);                     // 데이터를 읽기 전 5초 대기
  
  // DHT 센서로부터 온도 읽기
  t = dht.readTemperature();       // 섭씨 온도 읽기

  // ThingSpeak에 온도 데이터 전송
  int x = ThingSpeak.writeField(ChannelNumber, 1, t, APIKey); 

  // 데이터 전송 성공 여부 확인
  if (x == 200) {
    Serial.print("t : ");         // 온도 레이블 출력
    Serial.println(t);            // 온도 값 출력
  }
  else {
    Serial.println("업데이트 오류 코드 : " + String(x)); // 오류 메시지와 오류 코드 출력
  }
  
  delay(15000);                   // 다음 읽기 및 업데이트 전 15초 대기
}
