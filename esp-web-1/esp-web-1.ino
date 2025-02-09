#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put WiFi SSID & Password*/
const char* ssid = "Swecha Router";   // Enter SSID here
const char* password = "gv5*bgh5"; // Enter Password here

ESP8266WebServer server(80);

bool LEDstatus = LOW;
void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(D4, OUTPUT);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);

  //connect to your local wi-fi network
  // WiFi.config(staticIP, gateway, subnet);
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
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledon() {
  LEDstatus = HIGH;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_ledoff() {
  LEDstatus = LOW;
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LEDstatus)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String updateWebpage(uint8_t LEDstatus){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html {font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #3498db;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  ptr +="<h3>Using Station(STA) Mode</h3>\n";
  
   if(LEDstatus){
    ptr +="<p>RED LED: OFF</p><a class=\"button button-off\" href=\"/ledoff\">ON</a>\n";
   }else{
    ptr +="<p>RED LED: ON</p><a class=\"button button-on\" href=\"/ledon\">OFF</a>\n";
   }

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}