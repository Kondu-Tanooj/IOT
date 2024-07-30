#include <SoftwareSerial.h>
SoftwareSerial GSM(12, 13); // TX AND RX PINS

char phone_no[] = "+918897720549"; // REPLACE THIS NUMBER WITH YOUR NO(FOR ALERT)

void setup()
{
  Serial.begin(9600);
  GSM.begin(9600);
  Serial.println("Initializing....");
  initModule("AT", "OK", 1000);
}
void loop()
  {
    callUp(phone_no);
    delay (10000);
   ESP.deepSleep(0);
  }
void callUp(char *number) {
  GSM.print("ATD + "); GSM.print(number); GSM.println(";"); //THIS AT COMAND IS FOR MAKING CALLS
  delay(2000);
  GSM.println("ATH"); //TO CUT CALL
  delay(100);
}
void initModule(String cmd, char *res, int t) {
  while (1) {
    Serial.println(cmd);
    GSM.println(cmd);
    delay(100);
    while (GSM.available() > 0) {
      if (GSM.find(res)) {
        Serial.println(res);
        delay(t);
        return;
      } else {
        Serial.println("Error");
      }
    }
    delay(t);
  }
}