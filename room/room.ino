#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
char ssid[] = "Tj-mobile";         // your network SSID (name)
char password[] = "12345678";         // your network password

#define BOT_TOKEN "6532790086:AAEj2PSrG2r_xpC1X5gvQzVQv-Al2r2p-pQ"         // Telegram Bot Token

const unsigned long BOT_MTBS = 1000;         // mean time between scan messages

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime;         // last time messages scan has been done
bool Start = false;

//WiFiClientSecure client;
//UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);

#define l1 D0
#define l2 D1
#define l3 D2
#define f1 D3
#define f2 D4
#define f3 D5
#define f4 D6

void setup() {
  Serial.begin(9600);
  // Set WiFi to station mode and disconnect from an AP if it was Previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  pinMode(l1, OUTPUT);
  digitalWrite(l1, HIGH);
  pinMode(l2, OUTPUT);
  digitalWrite(l2, HIGH);
  pinMode(l3, OUTPUT);
  digitalWrite(l3, HIGH);
  pinMode(f1, OUTPUT);
  digitalWrite(f1, HIGH);
  pinMode(f2, OUTPUT);
  digitalWrite(f2, HIGH);
  pinMode(f3, OUTPUT);
  digitalWrite(f3, HIGH);
  pinMode(f4, OUTPUT);
  digitalWrite(f4, HIGH);
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
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);  
  // Only required on 2.5 Beta
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
      if (text == F("l1-on")) {
        digitalWrite(l1, LOW);
        bot.sendMessage(chat_id, "Light-1 has been Switched ON");
      }
      else if (text == F("l1-off")) {
        digitalWrite(l1, HIGH);
        bot.sendMessage(chat_id, "Light-1 has been Switched OFF");
      }
      else if (text == F("l2-on")) {
        digitalWrite(l2, LOW);
        bot.sendMessage(chat_id, "Light-2 has been Switched ON");
      }
      else if (text == F("l2-off")) {
        digitalWrite(l2, HIGH);
        bot.sendMessage(chat_id, "Light-2 has been Switched OFF");
      }
      else if (text == F("l3-on")) {
        digitalWrite(l3, LOW);
        bot.sendMessage(chat_id, "Light-3 has been Switched ON");
      }
      else if (text == F("l3-off")) {
        digitalWrite(l3, HIGH);
        bot.sendMessage(chat_id, "Light-3 has been Switched OFF");
      }
       else if (text == F("f1-on")) {
        digitalWrite(f1, LOW);
        bot.sendMessage(chat_id, "Fan-1 has been Switched ON");
      }
      else if (text == F("f1-off")) {
        digitalWrite(f1, HIGH);
        bot.sendMessage(chat_id, "Fan-1 has been Switched OFF");
      }
      else if (text == F("f2-on")) {
        digitalWrite(f2, LOW);
        bot.sendMessage(chat_id, "Fan-2 has been Switched ON");
      }
      else if (text == F("f2-off")) {
        digitalWrite(f2, HIGH);
        bot.sendMessage(chat_id, "Fan-2 has been Switched OFF");
      }
      else if (text == F("f3-on")) {
        digitalWrite(f3, LOW);
        bot.sendMessage(chat_id, "Fan-3 has been Switched ON");
      }
      else if (text == F("f3-off")) {
        digitalWrite(f3, HIGH);
        bot.sendMessage(chat_id, "Fan-3 has been Switched OFF");
      }
      else if (text == F("f4-on")) {
        digitalWrite(f4, LOW);
        bot.sendMessage(chat_id, "Fan-4 has been Switched ON");
      }
      else if (text == F("f4-off")) {
        digitalWrite(f4, HIGH);
        bot.sendMessage(chat_id, "Fan-4 has been Switched OFF");
      }
      else if (text == F("fans-on")) {
        digitalWrite(f1, LOW);
        digitalWrite(f2, LOW);
        digitalWrite(f3, LOW);
        digitalWrite(f4, LOW);
        bot.sendMessage(chat_id, "All Fan's & Light's has been Switched ON");
      }
      else if (text == F("fans-off")) {
        digitalWrite(f1, HIGH);
        digitalWrite(f2, HIGH);
        digitalWrite(f3, HIGH);
        digitalWrite(f4, HIGH);
        bot.sendMessage(chat_id, "All Fan's & Light's has been Switched OFF");
      }
      else if (text == F("lights-on")) {
        digitalWrite(l1, LOW);
        digitalWrite(l2, LOW);
        digitalWrite(l3, LOW);
        bot.sendMessage(chat_id, "All Fan's & Light's has been Switched ON");
      }
      else if (text == F("lights-off")) {
        digitalWrite(l1, HIGH);
        digitalWrite(l2, HIGH);
        digitalWrite(l3, HIGH);
        bot.sendMessage(chat_id, "All Fan's & Light's has been Switched OFF");
      }
      else if (text == F("all-on")) {
        digitalWrite(l1, LOW);
        digitalWrite(l2, LOW);
        digitalWrite(l3, LOW);
        digitalWrite(f1, LOW);
        digitalWrite(f2, LOW);
        digitalWrite(f3, LOW);
        digitalWrite(f4, LOW);
        bot.sendMessage(chat_id, "All Fan's & Light's has been Switched ON");
      }
      else if (text == F("all-off")) {
        digitalWrite(l1, HIGH);
        digitalWrite(l2, HIGH);
        digitalWrite(l3, HIGH);
        digitalWrite(f1, HIGH);
        digitalWrite(f2, HIGH);
        digitalWrite(f3, HIGH);
        digitalWrite(f4, HIGH);
        bot.sendMessage(chat_id, "All Fan's & Light's has been Switched OFF");
      }
    }
    else {
      String chat_id = String(bot.messages[i].chat_id);
      String text = bot.messages[i].text;
      String from_name = bot.messages[i].from_name;
      String keyboardJson;
      if (text == F("/switches")) {
      keyboardJson = F("[[{ \"text\" : \"L1 ON\", \"callback_data\" : \"l1-on\" },{ \"text\" : \"L1 OFF\", \"callback_data\" : \"l1-off\" }],"
                     "[{ \"text\" : \"L2 ON\", \"callback_data\" : \"l2-on\" },{ \"text\" : \"L2 OFF\", \"callback_data\" : \"l2-off\" }],"
                     "[{ \"text\" : \"L3 ON\", \"callback_data\" : \"l3-on\"},{ \"text\" : \"L3 OFF\", \"callback_data\" : \"l3-off\" }],"
                     "[{ \"text\" : \"F1 ON\", \"callback_data\" : \"f1-on\" },{ \"text\" : \"F1 OFF\", \"callback_data\" : \"f1-off\" }],"
                     "[{ \"text\" : \"F2 ON\", \"callback_data\" : \"f2-on\" },{ \"text\" : \"F2 OFF\", \"callback_data\" : \"f2-off\" }],"
                     "[{ \"text\" : \"F3 ON\", \"callback_data\" : \"f3-on\" },{ \"text\" : \"F3 OFF\", \"callback_data\" : \"f3-off\" }],"
                     "[{ \"text\" : \"F4 ON\", \"callback_data\" : \"f4-on\" },{ \"text\" : \"F4 OFF\", \"callback_data\" : \"f4-off\" }]]");
      bot.sendMessageWithInlineKeyboard(chat_id, "Control Individual Swtiches", "", keyboardJson);
    }
      else if (text == F("/all_switches")) {
        keyboardJson = F("[[{ \"text\" : \"ALL ON\", \"callback_data\" : \"all-on\" },{ \"text\" : \"ALL OFF\", \"callback_data\" : \"all-off\" }]]");
        bot.sendMessageWithInlineKeyboard(chat_id, "Control all Switches at once", "", keyboardJson);
      }
      else if (text == F("/fans")) {
        keyboardJson = F("[[{ \"text\" : \"FANS ON\", \"callback_data\" : \"fans-on\" },{ \"text\" : \"FANS OFF\", \"callback_data\" : \"fans-off\" }]]");
        bot.sendMessageWithInlineKeyboard(chat_id, "Control all Fan's at once", "", keyboardJson);
      }
      else if (text == F("/lights")) {
        keyboardJson = F("[[{ \"text\" : \"LIGHTS ON\", \"callback_data\" : \"lights-on\" },{ \"text\" : \"LIGHTS OFF\", \"callback_data\" : \"lights-off\" }]]");
        bot.sendMessageWithInlineKeyboard(chat_id, "Control all Light's at once", "", keyboardJson);
      }
      else if (text == F("/start")) {
        bot.sendMessage(chat_id, "Hi " + from_name + ", I'm MVGR GLUG Controller. I'm here to assist you to Switch Fan's & Lights ON/OFF of MVGR GLUG Office.");
        bot.sendMessageWithInlineKeyboard(chat_id, "Individual Switches - /switches\nAll Switches - /all_switches\nAll Fan's - /fans\nAll Light's - /lights", "", keyboardJson);
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