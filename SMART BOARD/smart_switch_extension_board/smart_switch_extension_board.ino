#include "thingProperties.h"

void setup() {
  pinMode(D0,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D8,OUTPUT);
  
  Serial.begin(9600);
    if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Disconnecting from Wi-Fi...");
    WiFi.disconnect();
  }

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(D5,HIGH);
  digitalWrite(D6,HIGH);
  digitalWrite(D7,HIGH);
  digitalWrite(D8,HIGH);
  delay(1000); 
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  
  
}
void onSwitch1Change()  {
  if (switch1)
  {
    digitalWrite(D0,LOW);
    digitalWrite(D5,HIGH);
    
  }
  else
  {
    digitalWrite(D0,HIGH);
    digitalWrite(D5,LOW);
  }
  
}
void onSwitch2Change()  {
  if (switch2)
  {
    digitalWrite(D1,LOW);
    digitalWrite(D6,HIGH);
  }
  else
  {
    digitalWrite(D1,HIGH);
    digitalWrite(D6,LOW);
  }
  
}
void onSwitch3Change()  {
  if (switch3)
  {
    digitalWrite(D2,LOW);
    digitalWrite(D7,HIGH);
    
  }
  else
  {
    digitalWrite(D2,HIGH);
    digitalWrite(D7,LOW);
  }
}
void onSwitch4Change()  {
  if (switch4)
  {
    digitalWrite(D3,LOW);
    digitalWrite(D8,HIGH);
  }
  else
  {
    digitalWrite(D3,HIGH);
    digitalWrite(D8,LOW);
  }
} 
