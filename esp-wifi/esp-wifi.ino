#include<ESP8266WiFi.h>
const char* ssid = "Tj-mobile";
const char* password = "12345678";

void setup() {
    // Initialize serial communication
    Serial.begin(9600);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.println("Start Connection");
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.print("Device IP :");
    Serial.println((WiFi.localIP().toString()));
    Serial.print("Gateway IP :");
    Serial.println((WiFi.gatewayIP().toString().c_str()));
}

void loop() {
  // put your main code here, to run repeatedly:

}
