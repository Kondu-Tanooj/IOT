#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
char ssid[] = "Smart";         // your network SSID (name)
char password[] = "smart123";         // your network password

#define BOT_TOKEN "6606460842:AAE0qgeYi6JaIAq_ytuLx28JRdzQFAlN4Xk"         // Telegram Bot Token
const unsigned long BOT_MTBS = 1000;         // mean time between scan messages

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;         // last time messages scan has been done
bool Start = false;

//WiFiClientSecure client;
//UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);

#define l1 D0

void setup() {
  Serial.begin(9600);
  // Set WiFi to station mode and disconnect from an AP if it was Previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  pinMode(l1, OUTPUT);
  digitalWrite(l1, HIGH);
  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
  // Only required on 2.5 Beta
   pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);  
  secured_client.setInsecure();
  // longPoll keeps the request to Telegram open for the given amount of seconds if there are no messages
  // This hugely improves response time of the bot, but is only really suitable for projects
  // where the the initial interaction comes from Telegram as the requests will block the loop for
  // the length of the long poll
  bot.longPoll = 60;
}
void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    // If the type is a "callback_query", a inline keyboard button was pressed
    if (bot.messages[i].type ==  F("callback_query")) {
      String text = bot.messages[i].text;
      String chat_id = String(bot.messages[i].chat_id);
      Serial.print("Call back button pressed with text: ");
      Serial.println(text);
      if (text == F("lights-on")) {
        digitalWrite(l1, LOW);
        bot.sendMessage(chat_id, "All Fan's & Light's has been Switched ON");
      }
      else if (text == F("lights-off")) {
        digitalWrite(l1, HIGH);
        bot.sendMessage(chat_id, "All Fan's & Light's has been Switched OFF");
      }
    }
    else {
      String chat_id = String(bot.messages[i].chat_id);
      String text = bot.messages[i].text;
      String from_name = bot.messages[i].from_name;
      String keyboardJson;
      if (text == F("/lights")) {
        keyboardJson = F("[[{ \"text\" : \"LIGHTS ON\", \"callback_data\" : \"lights-on\" },{ \"text\" : \"LIGHTS OFF\", \"callback_data\" : \"lights-off\" }]]");
        bot.sendMessageWithInlineKeyboard(chat_id, "Control all Light's at once", "", keyboardJson);
      }
      else if (text == F("/start")) {
        bot.sendMessage(chat_id, "Hi " + from_name + ", I'm Smart Socket Controller. I'm here to assist you to Switch Lights ON/OFF.");
        bot.sendMessageWithInlineKeyboard(chat_id, "All Light's - /lights", "", keyboardJson);
      }
    }
  }
}
void loop()
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}