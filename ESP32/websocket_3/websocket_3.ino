#include <WiFi.h>
#include <WebSocketsServer.h>
#include <DHT.h>

const int ledPin = 4; 
const int dhtPin = 18;  // DHT 센서 핀

const char* ssid = "SK_WiFiGIGADCE8_2.4G";             // 연결할 Wi-Fi의 SSID
const char* password = "AWA27@7107";                   // Wi-Fi의 비밀번호

WebSocketsServer webSocket = WebSocketsServer(80); // WebSocket 서버 포트: 80

#define DHT_TYPE DHT11

DHT dht(dhtPin, DHT_TYPE);

String getTemperatureHumidity() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  // 섭씨 온도

  if (isnan(humidity) || isnan(temperature)) {
    return "Failed to read from DHT sensor!";
  }

  return String("Temp: ") + temperature + "C, Humidity: " + humidity + "%";
}

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED: // 클라이언트가 연결된 경우
      Serial.println("Client connected!");
      break;

    case WStype_TEXT:  // 클라이언트가 메시지를 보낸 경우
      Serial.printf("Message from client: %s\n", payload);
      
      if (strcmp((char*)payload, "1") == 0) {
        digitalWrite(ledPin, HIGH);  // LED 켜기
      }
      else if (strcmp((char*)payload, "2") == 0) {
        digitalWrite(ledPin, LOW);   // LED 끄기
      }
      else if (strcmp((char*)payload, "3") == 0) {
        // '3' 요청이 들어오면 온습도 데이터 전송
        String tempHumidity = getTemperatureHumidity();
        webSocket.sendTXT(num, tempHumidity);  // 온습도 데이터를 클라이언트로 전송
      }
      break;

    default:
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to Wi-Fi...");
  
  pinMode(ledPin, OUTPUT);  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  dht.begin();        // DHT 센서 초기화

  webSocket.begin();  // WebSocket 서버 시작
  webSocket.onEvent(onWebSocketEvent); // WebSocket 이벤트 콜백 설정
}

void loop() {
  webSocket.loop();  // WebSocket 서버 동작
}
