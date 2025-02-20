const int tiltSensor = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
    pinMode(tiltSensor, INPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void setColor(int red, int green, int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}

void loop() {
    int tiltState = digitalRead(tiltSensor);

    if (tiltState == HIGH) { 
        setColor(255, 255, 0); // 노란색 (빨강+초록)
    } else {
        setColor(135, 206, 250); // 하늘색 (RGB 값: 연한 파랑)
    }
}
