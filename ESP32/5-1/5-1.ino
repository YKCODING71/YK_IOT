#include <WiFi.h>        // WiFi 라이브러리를 포함합니다.
#include <WebServer.h>   // WebServer 라이브러리를 포함합니다.

const char* ssid = "PASCUCCI 2";             // 연결할 Wi-Fi의 SSID를 입력합니다.
const char* password = "PAS123456789";     // Wi-Fi의 비밀번호를 입력합니다.

WebServer server(80);                          // 포트 번호 80을 사용하여 WebServer 객체를 생성합니다.

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32!");   // "/" 경로에 대한 요청을 처리하는 핸들러 함수입니다.
}

void setup() {
  Serial.begin(115200);                         // 시리얼 통신을 초기화합니다.

  WiFi.begin(ssid, password);                    // Wi-Fi에 연결합니다.
  Serial.println("Connected to WiFi");           
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());                // Wi-Fi의 로컬 IP 주소를 출력합니다.

  server.begin();                                // 서버를 시작합니다.
}

void loop() {
  server.handleClient();                         // 클라이언트의 요청을 처리합니다.
}
