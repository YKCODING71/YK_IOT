#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "PASCUCCI 2";             // 연결할 Wi-Fi의 SSID
const char* password = "PAS123456789";       // Wi-Fi의 비밀번호

WebSocketsServer webSocket = WebSocketsServer(80); // WebSocket 서버 포트: 80

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: // 클라이언트가 연결된 경우
      Serial.println("Client connected!");
      break;

    case WStype_TEXT: // 클라이언트가 메시지를 보낸 경우
      Serial.printf("Message from client: %s\n", payload);
      webSocket.sendTXT(num, payload); // 클라이언트로 에코 메시지 전송
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to Wi-Fi...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();                 // WebSocket 서버 시작
  webSocket.onEvent(onWebSocketEvent); // WebSocket 이벤트 콜백 설정
}

void loop() {
  webSocket.loop(); // WebSocket 서버 동작
}
