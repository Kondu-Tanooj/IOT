#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Swecha Router";
const char* password = "gv5*bgh5";

const char* serverAddress = "http://localhost:8000"; // Change port if necessary

int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  
  // Send data to the local web server
  sendToServer(sensorValue);
  
  delay(1000); // Adjust delay as per requirement
}

void sendToServer(int value) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;

    String data = "sensorValue=" + String(value);

    Serial.print("Sending data: ");
    Serial.println(data);

    http.begin(client, serverAddress);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int httpResponseCode = http.POST(data);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server response: " + response);
    } else {
      Serial.print("Error sending data. HTTP error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("Error: WiFi Disconnected");
  }
}


