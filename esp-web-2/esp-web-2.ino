#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put WiFi SSID & Password*/
const char* ssid = "Tj-mobile";   // Enter SSID here
const char* password = "12345678"; // Enter Password here

ESP8266WebServer server(80);

bool LEDstatus = LOW;
IPAddress staticIP(192,168,138,16); // Set your desired static IP address
IPAddress gateway(192,168, 138, 1);    // Set your gateway IP address
IPAddress subnet(255, 255, 255, 0);   // Set your subnet mask
void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(D4, OUTPUT);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);

  //connect to your local wi-fi network
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  //check NodeMCU is connected to Wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}
void loop() {
  server.handleClient();
  
  if(LEDstatus)
  {
    digitalWrite(D4, HIGH);}
  else
  {
    digitalWrite(D4, LOW);}
}

void handle_OnConnect() {
  LEDstatus = LOW;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledon() {
  LEDstatus = HIGH;
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledoff() {
  LEDstatus = LOW;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String updateWebpage(uint8_t LEDstatus) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".toggle-container {display: block; width: 80px; margin: 0px auto 35px;}\n";
  ptr += ".toggle-label {color: #888; font-size: 14px;}\n";
  ptr += ".toggle-switch {position: relative; display: inline-block; width: 40px; height: 20px; background-color: #ccc; border-radius: 20px;}\n";
  ptr += ".toggle-slider {position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0; background-color: #2196F3; border-radius: 20px; transition: 0.4s;}\n";
  ptr += ".toggle-slider:before {position: absolute; content: \"\"; height: 16px; width: 16px; left: 2px; bottom: 2px; background-color: white; border-radius: 50%; transition: 0.4s;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP8266 Web Server</h1>\n";
  ptr += "<h3>Using Station(STA) Mode</h3>\n";
  ptr += "<div class=\"toggle-container\">\n";
  ptr += "<p class=\"toggle-label\">RED LED</p>\n";
  ptr += "<label class=\"toggle-switch\">\n";
  if (LEDstatus) {
    ptr += "<input type=\"checkbox\" checked=\"checked\" onclick=\"window.location.href='/ledoff'\">\n";
  } else {
    ptr += "<input type=\"checkbox\" onclick=\"window.location.href='/ledon'\">\n";
  }
  ptr += "<span class=\"toggle-slider\"></span>\n";
  ptr += "</label>\n";
  ptr += "</div>\n";

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
