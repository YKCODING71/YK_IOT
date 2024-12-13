#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

const char* ssid = "SK_WiFiGIGADCE8_2.4G";
const char* password = "AWA27@7107";

#define DHTPIN 18           // DHT 센서 핀
#define DHTTYPE DHT11       // DHT 센서 유형

DHT dht(DHTPIN, DHTTYPE);   // DHT 센서 객체 생성
AsyncWebServer server(80);  // 웹 서버 생성

// 온도 읽기 함수
String readTemperature() {
    float t = dht.readTemperature();
    return isnan(t) ? "--" : String(t);
}

// 습도 읽기 함수
String readHumidity() {
    float h = dht.readHumidity();
    return isnan(h) ? "--" : String(h);
}

// HTML 페이지
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; }
    h2 { font-size: 2.5rem; }
    p { font-size: 2rem; }
    .value { font-size: 2rem; color: #333; }
  </style>
</head>
<body>
  <h2>ESP32 DHT Server</h2>
  <p>온도: <span id="temperature" class="value">%TEMPERATURE%</span>&deg;C</p>
  <p>습도: <span id="humidity" class="value">%HUMIDITY%</span>%</p>
  <script>
    function updateData() {
      fetch('/temperature').then(res => res.text()).then(data => {  //데이터요청
        document.getElementById('temperature').textContent = data;  //표시
      });
      fetch('/humidity').then(res => res.text()).then(data => {
        document.getElementById('humidity').textContent = data;
      });
    }
    setInterval(updateData, 2000);                    //2초간격
    updateData();
  </script>
</body>
</html>
)rawliteral"; // 닫는 따옴표와 괄호 추가

// 변수 대체 처리 함수
String processor(const String& var) {
    if (var == "TEMPERATURE") return readTemperature();
    if (var == "HUMIDITY") return readHumidity();
    return String();
}

void setup() {
    Serial.begin(115200);
    dht.begin();

    // Wi-Fi 연결
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Wi-Fi 연결 중...");
    }
    Serial.println("Wi-Fi 연결 완료: " + WiFi.localIP().toString());

    // 서버 엔드포인트 설정
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/html", htmlPage, processor);
    });
    server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", readTemperature());
    });
    server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(200, "text/plain", readHumidity());
    });

    server.begin();
}

void loop() {
    // 메인 루프는 필요 없음 (AsyncWebServer 가 처리)
}
