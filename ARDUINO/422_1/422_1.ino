const int ledPin = 13;
const int buttonPin = 2;

int led_state = LOW;
bool led_state_changed = false;

unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 50; 

void buttonPressed() {
  unsigned long currentTime = millis();
  if (currentTime - lastInterruptTime > debounceDelay) {
    led_state = (led_state == LOW) ? HIGH : LOW;
    led_state_changed = true;
    lastInterruptTime = currentTime;  
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);  
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, RISING);
}

void loop() {
  if (led_state_changed) {
    led_state_changed = false;
    digitalWrite(ledPin, led_state);
  }   
}
