#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Swecha Router";
const char* password = "gv5*bgh5";
const char* serverAddress = "http://192.168.33.149/test/sensor_data.php";

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
  if (Serial.available() > 0) {
    String sensorData = Serial.readStringUntil('\n'); 
    if (sensorData.length() > 0) { // Check if sensorData is not empty
      sendSensorDataToServer(sensorData.toInt()); // Convert string to integer and send sensor data to server
    } else {
      Serial.println("Invalid sensor data");
    }
  }
}

void sendSensorDataToServer(int sensorData) {
  HTTPClient http;
  WiFiClient client;

  http.begin(client, serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String data = "sensor1=" + String(sensorData);

  int httpResponseCode = http.POST(data);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.println("Error on HTTP request");
  }

  http.end();
}
