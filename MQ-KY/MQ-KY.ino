#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "SHAY";
const char* password = "jaishreeram";
const char* serverUrl = "http://ec2-18-61-42-55.ap-south-2.compute.amazonaws.com/firealarm";

const int KY026_PIN = A0;
void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read sensor data
  float ky026Value = analogRead(KY026_PIN); 

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    if (ky026Value <200) { 
      float fire = (1-(ky026Value/200));
      String urlWithParams = String(serverUrl) + "?uid=101" + "&value=" +"fire=" + String(fire);
      http.begin(client, urlWithParams);
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.print("KY-026 Value: ");
        Serial.println(ky026Value);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      http.end();
    }
  } else {
    Serial.println("WiFi Disconnected");
  }

  delay(5000);
}
