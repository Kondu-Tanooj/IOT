#include <ESP8266WiFi.h>

const char* ssid = "Tj-mobile";
const char* password = "12345678";

const int irPin = D2;
volatile int totalCount = 0;
volatile bool lastState = LOW;

void IRAM_ATTR handleIRSensor() {
    // Check if the IR sensor has been triggered (rising edge)
    if (digitalRead(irPin) == HIGH && lastState == LOW) {
        totalCount++;
        Serial.println("Visitor entered. Total count: " + String(totalCount));
    }
    lastState = digitalRead(irPin);
}

void setup() {
    Serial.begin(9600);

    pinMode(irPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(irPin), handleIRSensor, RISING);

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void loop() {
    // Your loop code here
    delay(100);
}
