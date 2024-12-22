#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "PASCUCCI 2";             // 연결할 Wi-Fi의 SSID
const char* password = "PAS123456789";       // Wi-Fi의 비밀번호

WebSocketsServer webSocket = WebSocketsServer(80);  // 80번 포트로 WebSocket 서버 설정

// WebSocket 이벤트 처리 함수
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
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
      if (strcmp((char*)payload, "a") == 0) {
        webSocket.sendTXT(num, "hello");         // 클라이언트에 "hello" 메시지 전송
      } else if (strcmp((char*)payload, "b") == 0) {
        webSocket.sendTXT(num, "sleep");         // 클라이언트에 "sleep" 메시지 전송
      }
      break;

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

  Serial.println("\nConnected!");        // Wi-Fi 연결 완료 메시지 출력
  webSocket.begin();                     // WebSocket 서버 시작
  webSocket.onEvent(onWebSocketEvent);    // WebSocket 이벤트 콜백 함수 설정
}

void loop() {
  webSocket.loop();                      // WebSocket 서버의 이벤트 루프 실행
}
