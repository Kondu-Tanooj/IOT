#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "5a3eb993-9eb5-45f0-8233-1fc87b9f37c7";

const char SSID[]               = "POCO X4 Pro";    // Network SSID (name)
const char PASS[]               = "Anurag@1947";    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = "UO6SmFg1@hzHKzi6QyDBu#bUo";    // Secret device password

void onSwitch1Change();
void onSwitch2Change();

bool switch1;
bool switch2;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(switch1, READWRITE, ON_CHANGE, onSwitch1Change);
  ArduinoCloud.addProperty(switch2, READWRITE, ON_CHANGE, onSwitch2Change);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);


void setup() {
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  
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
  delay(500); 
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
    digitalWrite(D1,LOW);
    
  }
  else
  {
    digitalWrite(D1,HIGH);
  }
  
}
void onSwitch2Change()  {
  if (switch2)
  {
    digitalWrite(D2,LOW);
  }
  else
  {
    digitalWrite(D2,HIGH);
  }
  
}