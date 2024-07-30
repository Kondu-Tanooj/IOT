#include <ESP8266WiFi.h>
void setup() {
  Serial.begin(9600);
  delay(100);
  const char* ssid = "Tj-mobile";
  const char* password = "12345678";
  WiFi.disconnect();
  delay(2000);
  //pinMode(D4, OUTPUT);
  // Connect to Wi-Fi
  Serial.println("Start Connection");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
}

void loop() {
  // Your code here
  // digitalWrite(D4, LOW);  // turn the LED on (HIGH is the voltage level)
  // delay(1000);                      // wait for a second
  // digitalWrite(D4, HIGH);   // turn the LED off by making the voltage LOW
  // delay(1000);  
}
