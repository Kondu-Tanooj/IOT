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

  sendSensorDataToServer();
}

void loop() {
  // No need for continuous action in the loop
}

void sendSensorDataToServer() {
  HTTPClient http;
  WiFiClient client;

  http.begin(client,serverAddress);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  //int sensor1Data = 123456789123; // Example sensor data

  String data = "sensor1=" + String(123456789123);

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
