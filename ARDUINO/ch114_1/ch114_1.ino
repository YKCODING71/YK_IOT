#include <WiFi.h>
#include <WebSocketsServer.h>

#define ssid      "ConnectValue_A401_2G"  // Wi-Fi SSID 정의
#define password "CVA401!@#$"             // Wi-Fi 비밀번호 정의

WebSocketsServer webSocket = WebSocketsServer(80);  // 80번 포트로 WebSocket 서버 설정

// WebSocket 이벤트 처리 함수
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  
  switch(type) {
    case WStype_DISCONNECTED:                     // 연결이 끊어졌을 때
      Serial.printf("[%u] Disconnected!\n", num); // 연결 끊김 메시지 출력
      break;

    case WStype_CONNECTED:                        // 새로운 연결이 이루어졌을 때
      {
        IPAddress ip = webSocket.remoteIP(num);   // 연결된 클라이언트의 IP 주소 가져오기
        Serial.printf("[%u] Connection from ", num);  // 연결된 클라이언트 번호 출력
        Serial.println(ip.toString());            // IP 주소 출력
      }
      break;

    case WStype_TEXT:                             // 텍스트 메시지를 받았을 때
      Serial.printf("[%u] Text: %s\n", num, payload);  // 받은 텍스트 메시지 출력
      webSocket.sendTXT(num, payload);          // 받은 텍스트 메시지를 다시 클라이언트에 보내기
      break;

    case WStype_BIN:                           // 바이너리 메시지를 받았을 때 (처리 안 함)
    case WStype_ERROR:                         // 오류 발생 시 (처리 안 함)
    case WStype_FRAGMENT_TEXT_START:           // 텍스트 메시지 조각이 시작될 때 (처리 안 함)
    case WStype_FRAGMENT_BIN_START:            // 바이너리 메시지 조각이 시작될 때 (처리 안 함)
    case WStype_FRAGMENT:                      // 메시지 조각을 받을 때 (처리 안 함)
    case WStype_FRAGMENT_FIN:                  // 메시지 조각의 끝을 받을 때 (처리 안 함)
    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);                  // 시리얼 모니터 시작
  Serial.println("Connecting");
  WiFi.begin(ssid, password);            // Wi-Fi 네트워크에 연결 시작
  
  // Wi-Fi가 연결될 때까지 대기
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");                   // 연결 중임을 표시
  }
  
  Serial.println("Connected!");           // Wi-Fi 연결 완료 메시지 출력
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());         // ESP32의 IP 주소 출력
  
  webSocket.begin();                     // WebSocket 서버 시작
  webSocket.onEvent(onWebSocketEvent);    // WebSocket 이벤트 콜백 함수 설정
}

void loop() {
  webSocket.loop();                      // WebSocket 서버의 이벤트 루프 실행
}
