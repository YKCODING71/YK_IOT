#include <WiFi.h>
#include <WebSocketsServer.h>

#define ssid  "ConnectValue_C401_2G"                // WiFi SSID 정의
#define password   "CVC401!@#$"                      // WiFi 비밀번호 정의
int a = 0;
WebSocketsServer webSocket = WebSocketsServer(80);  // 포트 80에서 WebSocket 서버 생성
const char* payload_str = 0;
// WebSocket 메시지를 수신했을 때 호출되는 함수
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  
  // WebSocket 이벤트 타입 확인
  switch(type) {

    // 클라이언트가 연결을 끊었을 때
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);  // 클라이언트 번호 출력
      break;

    // 새로운 클라이언트가 연결되었을 때
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);  // 클라이언트의 IP 주소 가져오기
        Serial.printf("[%u] Connection from ", num);  // 클라이언트 번호 출력
        Serial.println(ip.toString());  // 클라이언트 IP 주소 출력
      }
      break;

    // 클라이언트로부터 텍스트 메시지를 받았을 때
      case WStype_TEXT:
        Serial.printf("[%u] Text: %s\n", num, payload);  // 클라이언트 번호와 수신한 메시지 출력
        payload_str = reinterpret_cast<const char*>(payload);
        if (strstr(payload_str, "f") != nullptr) { //NULL'0'
                Serial2.write('f');
                Serial.write('f');
        }
    
      webSocket.sendTXT(num, payload);  // 받은 메시지를 클라이언트에게 다시 전송 (에코)
      //String payload_str = String((char*)payload);
      //String payload_str = String((char*)payload);
      //int a = payload_str.indexOf("hi");
      //Serial.println(a);
      //if(a!=-1) { Serial.println("good");}

      break;

    // 그 외의 경우: 아무것도 하지 않음
    case WStype_BIN:
    case WStype_ERROR:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
    default:

          break;
  }
}

void setup() {
  // 시리얼 통신 시작
  Serial.begin(115200);
  // WiFi 액세스 포인트에 연결
  Serial.println("Connecting");
  WiFi.begin(ssid, password);  // WiFi 연결 시도
  while ( WiFi.status() != WL_CONNECTED ) {  // 연결될 때까지 대기
    delay(500);  // 0.5초 대기
    Serial.print(".");  // 연결 진행 중 점 출력
  }
  // IP 주소 출력
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());  // 로컬 IP 주소 출력
  // WebSocket 서버 시작 및 콜백 함수 설정
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);  // WebSocket 이벤트 처리 함수 등록
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,16,17);
}

void loop() {
  // WebSocket 데이터 처리
  webSocket.loop();
 // 변수 'a'의 값에 따라 조건 실행

}
