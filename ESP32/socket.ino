#include <WiFi.h>
#include <WebSocketsServer.h>

#define ssid  "ConnectValue_C401_2G"
#define password   "CVC401!@#$"

// Create a WebSocket server on port 80
WebSocketsServer webSocket = WebSocketsServer(80);

// Declare a variable to store received message
String receivedMessage = "";

// Called when receiving any WebSocket message
void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
  // Figure out the type of WebSocket event
  switch(type) {
    // Client has disconnected
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    // New client has connected
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connection from ", num);
        Serial.println(ip.toString());
      }
      break;

    // Text message received
    case WStype_TEXT:
      {
        // Convert payload to String
        String message = String((char*)payload);
        Serial.printf("[%u] Text: %s\n", num, message.c_str());
        
        // Store received message in the variable
        receivedMessage = message;
        
        // Example comparison
        if (receivedMessage == "f") {
          Serial2.write('f');             //arduino
          Serial.println("Received : f"); //python
        }  
         else if (receivedMessage == "s") {
          Serial2.write('f');             //arduino
          Serial.println("Received : f"); //python
        } 
        // Echo the text message back to the client
        webSocket.sendTXT(num, message);
      }
      break;

    // For everything else: do nothing
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
  // Start Serial port
  Serial.begin(115200);
  
  // Connect to access point
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print our IP address
  Serial.println("Connected!");
  Serial.print("My IP address: ");
  Serial.println(WiFi.localIP());
  
  // Start WebSocket server and assign callback
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
}

void loop() {
  // Look for and handle WebSocket data
  webSocket.loop();
}
