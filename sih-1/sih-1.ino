#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put WiFi SSID & Password*/
const char* ssid = "TJ";   // Enter SSID here
const char* password = "*123#143*"; // Enter Password here

ESP8266WebServer server(80);
const int ldr = A0;
bool LED_automan = LOW;
bool LED_main = LOW;
bool LED_sw1 = LOW;
bool LED_sw2 = LOW;
bool LED_sw3 = LOW;
// IPAddress staticIP(192,168,138,2); // Set your desired static IP address
// IPAddress gateway(192,168, 138, 1);    // Set your gateway IP address
// IPAddress subnet(255, 255, 255, 0);   // Set your subnet mask
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  pinMode(ldr,INPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
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
  digitalWrite(D4,HIGH);
  delay(1000);
  digitalWrite(D4,LOW);
  server.on("/", handle_OnConnect);
  server.on("/manual", handle_man);
  server.on("/automatic", handle_auto);
  server.on("/main-on", handle_mainon);
  server.on("/main-off", handle_mainoff);
  server.on("/sw1-on", handle_sw1on);
  server.on("/sw1-off", handle_sw1off);
  server.on("/sw2-on", handle_sw2on);
  server.on("/sw2-off", handle_sw2off);
  server.on("/sw3-on", handle_sw3on);
  server.on("/sw3-off", handle_sw3off);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  if(LED_automan){
    int ldrdata = analogRead(ldr);
    if(ldrdata<200){
    digitalWrite(D0,HIGH);
    digitalWrite(D1,HIGH);
    digitalWrite(D2,HIGH);
    }
    else{
    digitalWrite(D0,LOW);
    digitalWrite(D1,LOW);
    digitalWrite(D2,LOW);
    }
    // delay(1000);
  }
  else{
    if(LED_sw1)
    {
      digitalWrite(D0, HIGH);}
    else
    {
      digitalWrite(D0, LOW);
    }
    if(LED_sw2)
    {
      digitalWrite(D0, HIGH);}
    else
    {
      digitalWrite(D0, LOW);
    }
      if(LED_sw3)
    {
      digitalWrite(D0, HIGH);}
    else
    {
      digitalWrite(D0, LOW);
    }
  }
}

void handle_OnConnect() {
  LED_automan = LOW;
  Serial.println("Automatic: ON");
  server.send(200, "text/html", updateWebpage(LED_automan));
}

void handle_man() {
  LED_automan = HIGH;
  Serial.println("Manual: ON");
  server.send(200, "text/html", updateWebpage(LED_automan));
}

void handle_auto() {
  LED_automan = LOW;
  Serial.println("Automatic: ON");
  server.send(200, "text/html", updateWebpage(LED_automan));
}
void handle_mainon() {
  LED_main = HIGH;
  LED_sw1 = HIGH;
  LED_sw2 = HIGH;
  LED_sw3 = HIGH;
  Serial.println("Main: ON");
  server.send(200, "text/html", updateWebpage(LED_main));
}

void handle_mainoff() {
  LED_main = LOW;
  LED_sw1 = LOW;
  LED_sw2 = LOW;
  LED_sw3 = LOW;
  Serial.println("Main: OFF");
  server.send(200, "text/html", updateWebpage(LED_main));
}
void handle_sw1on() {
  LED_sw1 = HIGH;
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LED_sw1));
}

void handle_sw1off() {
  LED_sw1 = LOW;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LED_sw1));
}
void handle_sw2on() {
  LED_sw2 = HIGH;
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LED_sw2));
}

void handle_sw2off() {
  LED_sw2 = LOW;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LED_sw2));
}
void handle_sw3on() {
  LED_sw3 = HIGH;
  Serial.println("LED: ON");
  server.send(200, "text/html", updateWebpage(LED_sw3));
}

void handle_sw3off() {
  LED_sw3 = LOW;
  Serial.println("LED: OFF");
  server.send(200, "text/html", updateWebpage(LED_sw3));
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String updateWebpage(uint8_t LEDstatus) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head>\n";
  ptr += "<title>Automated Street Light System</title>\n";
  ptr += "<style>\n";
  ptr += ".center-horizontally{text-align: center;position: absolute;top: 0px;left: -500px;right: 0;bottom: 0;}\n";
  ptr += ".toggle-container {display: inline-block;position: relative;width: 200px;height: 40px;}\n";
  ptr += ".toggle-switch {position: absolute;top: 0;left: 0;right: 0;bottom: 0;background-color: hwb(88 20% 3%);border-radius: 100px;cursor: pointer;transition: background-color 0.3s;}\n";
  ptr += ".toggl-circle {position: absolute;height: 32px;width: 90px;left: 6px;right: 4px;top: 4px;background-color: white;border-radius: 100px;transition: transform 0.4s;}\n";
  ptr += ".toggle-label {position: absolute;top: 50%;transform: translateY(-50%);padding: 0 10px;font-size: 20px;}\n";
  ptr += ".toggle-label-left {left: 0;}\n";
  ptr += ".toggle-label-right {right: 0;}\n";
  ptr += ".toggle-container input:checked + .toggle-switch {background-color: hsl(29, 93%, 46%);}\n";
  ptr += ".toggle-container input:checked + .toggle-switch .toggl-circle {transform: translateX(100px);}\n";
  ptr += ".toggle-container input {display: none;}\n";
  ptr += ".manual-main-swicth{text-align: center;position: absolute;top: 130px;left: -400px;right: 0;bottom: 0;}\n";
  ptr += ".main-switch-container {display: inline-block;position: relative;width: 90px;height: 30px;}\n";
  ptr += ".main-toggle {position: absolute;top: 0;left: 0;right: 0;bottom: 0;background-color: hsl(0, 96%, 36%);border-radius: 50px;cursor: pointer;transition: background-color 0.3s;}\n";
  ptr += ".main-toggle-circle {position: absolute;height: 24px;width: 40px;left: 4px;right: 2px;top: 3px;background-color: white;border-radius: 100px;transition: transform 0.4s;}\n";
  ptr += ".main-switch-label {position: absolute;top: 50%;transform: translateY(-50%);padding: 0 9px;font-size: 18px;}\n";
  ptr += ".main-switch-label-left {left: 0;}\n";
  ptr += ".main-switch-label-right {right: 0;}\n";
  ptr += ".main-switch-container input:checked + .main-toggle {background-color: #2196F3;}\n";
  ptr += ".main-switch-container input:checked + .main-toggle .main-toggle-circle {transform: translateX(40px);}\n";
  ptr += ".main-switch-container input {display: none;}\n";
  ptr += ".street-1{position: absolute;left: 0px;}\n";
  ptr += ".street-2{position: absolute;left: 100px;}\n";
  ptr += ".street-3{position: absolute;left: 200px;}\n";
  ptr += ".switch-container {display: inline-block;position: relative;width: 80px;height: 30px;}\n";
  ptr += ".toggle {position: absolute;top: 0;left: 0;right: 0;bottom: 0;background-color: hsl(0, 96%, 36%);border-radius: 40px;cursor: pointer;transition: background-color 0.3s;}\n";
  ptr += ".toggle-circle {position: absolute;height: 24px;width: 38px;left: 4px;right: 2px;top: 3.3px;background-color: white;border-radius: 100px;transition: transform 0.4s;}\n";
  ptr += ".switch-label {position: absolute;top: 50%;transform: translateY(-50%);padding: 0 9px;font-size: 16px;}\n";
  ptr += ".switch-label-left {left: 0;}\n";
  ptr += ".switch-label-right {right: 0;}\n";
  ptr += ".switch-container input:checked + .toggle {background-color: #2196F3;}\n";
  ptr += ".switch-container input:checked + .toggle .toggle-circle {transform: translateX(35px);}\n";
  ptr += ".switch-container input {display: none;}\n";
  ptr += ".streets{text-align: center;position: absolute;top: 200px;left: 200px;right: 0;bottom: 0;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div class=\"project\">\n";
  ptr += "<div class=\"center-horizontally\">\n";
  ptr += "<h1>Automated Street Light System</h1>\n";
  ptr += "<label class=\"toggle-container\">\n";
 //automan
  if (LEDstatus == LED_automan && LEDstatus == LOW){
    ptr += "<input type=\"checkbox\" id=\"automan\" checked=\"checked\" onclick=\"window.location.href='/manual'\">\n";
  }
  else{
    ptr += "<input type=\"checkbox\" id=\"automan\" onclick=\"window.location.href='/automan'\">\n";
  }
  ptr += "<input type=\"checkbox\" id=\"automan\">\n";
  ptr += "<span class=\"toggle-switch\">\n";
  ptr += "<span class=\"toggl-circle\"></span>\n";
  ptr += "</span>\n";
  ptr += "<span class=\"toggle-label toggle-label-left\">Automatic</span>\n";
  ptr += "<span class=\"toggle-label toggle-label-right\">Manual</span>\n";
  ptr += "</label>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"manual-main-swicth\">\n";
  ptr += "<label class=\"main-switch-container\">\n";
  //main
    if (LEDstatus == LED_main && LEDstatus == LOW){
    ptr += "<input type=\"checkbox\" id=\"main\" checked=\"checked\" onclick=\"window.location.href='/main-on'\">\n";
  }
  else{
    ptr += "<input type=\"checkbox\" id=\"main\" onclick=\"window.location.href='/main-off'\">\n";
  }
  //ptr += "<input type=\"checkbox\" id=\"main\">\n";
  ptr += "<span class=\"main-toggle\">\n";
  ptr += "<span class=\"main-toggle-circle\"></span>\n";
  ptr += "</span>\n";
  ptr += "<span class=\"main-switch-label main-switch-label-left\">OFF</span>\n";
  ptr += "<span class=\"main-switch-label main-switch-label-right\">ON</span>\n";
  ptr += "</label>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"streets\">\n";
  ptr += "<div class=\"street-1\">\n";
  ptr += "<h2>Street-1</h2>\n";
  ptr += "<label class=\"switch-container\">\n";
  //sw1
  if (LEDstatus == LED_sw1 && LEDstatus == LOW){
    ptr += "<input type=\"checkbox\" id=\"switch1\" checked=\"checked\" onclick=\"window.location.href='/sw1-on'\">\n";
  }
  else{
    ptr += "<input type=\"checkbox\" id=\"switch1\" onclick=\"window.location.href='/sw1-off'\">\n";
  }
  //ptr += "<input type=\"checkbox\" id=\"switch1\">\n";
  ptr += "<span class=\"toggle\">\n";
  ptr += "<span class=\"toggle-circle\"></span>\n";
  ptr += "</span>\n";
  ptr += "<span class=\"switch-label switch-label-left\">OFF</span>\n";
  ptr += "<span class=\"switch-label switch-label-right\">ON</span>\n";
  ptr += "</label>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"street-2\">\n";
  ptr += "<h2>Street-2</h2>\n";
  ptr += "<label class=\"switch-container\">\n";
  //sw2
    if (LEDstatus == LED_sw2 && LEDstatus == LOW){
    ptr += "<input type=\"checkbox\" id=\"switch2\" checked=\"checked\" onclick=\"window.location.href='/sw2-on'\">\n";
  }
  else{
    ptr += "<input type=\"checkbox\" id=\"switch2\" onclick=\"window.location.href='/sw2-off'\">\n";
  }
  //ptr += "<input type=\"checkbox\" id=\"switch2\">\n";
  ptr += "<span class=\"toggle\">\n";
  ptr += "<span class=\"toggle-circle\"></span>\n";
  ptr += "</span>\n";
  ptr += "<span class=\"switch-label switch-label-left\">OFF</span>\n";
  ptr += "<span class=\"switch-label switch-label-right\">ON</span>\n";
  ptr += "</label>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"street-3\">\n";
  ptr += "<h2>Street-3</h2>\n";
  ptr += "<label class=\"switch-container\">\n";
  //sw3
    if (LEDstatus == LED_sw3 && LEDstatus == LOW){
    ptr += "<input type=\"checkbox\" id=\"switch3\" checked=\"checked\" onclick=\"window.location.href='/sw3-on'\">\n";
  }
  else{
    ptr += "<input type=\"checkbox\" id=\"switch3\" onclick=\"window.location.href='/sw3-off'\">\n";
  }
  //ptr += "<input type=\"checkbox\" id=\"switch3\">\n";
  ptr += "<span class=\"toggle\">\n";
  ptr += "<span class=\"toggle-circle\"></span>\n";
  ptr += "</span>\n";
  ptr += "<span class=\"switch-label switch-label-left\">OFF</span>\n";
  ptr += "<span class=\"switch-label switch-label-right\">ON</span>\n";
  ptr += "</label>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "<script>\n";
  ptr += "const automan = document.getElementById(\"automan\");\n";
  ptr += "const main = document.getElementById(\"main\");\n";
  ptr += "const switch1 = document.getElementById(\"switch1\");\n";
  ptr += "const switch2 = document.getElementById(\"switch2\");\n";
  ptr += "const switch3 = document.getElementById(\"switch3\");\n";
  ptr += "main.disabled = true;\n";
  ptr += "switch1.disabled = true;\n";
  ptr += "switch2.disabled = true;\n";
  ptr += "switch3.disabled = true;\n";
 ptr += "automan.addEventListener(\"change\", () => {";
  ptr += "if (!automan.checked) {";
  ptr += "main.checked = false;";
  ptr += "switch1.checked = false;";
  ptr += "switch2.checked = false;";
  ptr += "switch3.checked = false;";
  ptr += "main.disabled = true;";
  ptr += "switch1.disabled = true;";
  ptr += "switch2.disabled = true;";
  ptr += "switch3.disabled = true;";
  ptr += "}";
  ptr += "else if(automan.checked) {";
  ptr += "main.disabled = false;";
  ptr += "switch1.disabled = true;";
  ptr += "switch2.disabled = true;";
  ptr += "switch3.disabled = true;";
  ptr += "}";
  ptr += "});\n";
  ptr += "main.addEventListener(\"change\", () => {";
  ptr += "if (main.checked) {";
  ptr += "  switch1.disabled = false;";
  ptr += "  switch2.disabled = false;";
  ptr += "  switch3.disabled = false;";
  ptr += "  switch1.checked = true;";
  ptr += "  switch2.checked = true;";
  ptr += "  switch3.checked = true;";
  ptr += "} else {";
  ptr += "  switch1.disabled = true;";
  ptr += "  switch2.disabled = true;";
  ptr += "  switch3.disabled = true;";
  ptr += "  switch1.checked = false;";
  ptr += "  switch2.checked = false;";
  ptr += "  switch3.checked = false;";
  ptr += "}";
  ptr += "});\n";
  /*ptr += "switch1.addEventListener(\"change\",()=>{if(switch1.checked){window.location.href=\"/sw1-on\";}else{window.location.href=\"/sw1-off\";}});\n";
  ptr += "switch2.addEventListener(\"change\",()=>{if(switch2.checked){window.location.href=\"/sw2-on\";}else{window.location.href=\"/sw2-off\";}});\n";
  ptr += "switch3.addEventListener(\"change\",()=>{if(switch3.checked){window.location.href=\"/sw3-on\";}else{window.location.href=\"/sw3-off\";}});\n";*/
  ptr += "</script>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  /*ptr += "</head>\n";
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
  ptr += "</html>\n";*/
  return ptr;
}