const int tiltSensor = 2;
const int led = 12;

void setup() {
    pinMode(tiltSensor, INPUT);
    pinMode(led, OUTPUT);
}

void loop() {
    int tiltState = digitalRead(tiltSensor);

    if (tiltState == HIGH) {
        digitalWrite(led, HIGH);
    } else {
        digitalWrite(led, LOW);
    }
}
