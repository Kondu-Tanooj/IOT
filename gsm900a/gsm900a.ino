#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

void setup() {
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}

void loop() {
  if (Serial.available() > 0)
    switch (Serial.read()) {
      case 's':
        //makeCall();
        mySerial.println("ATD8897720549;");
        delay(5000);
        mySerial.println("AT+CMGF=1");    // Sets the GSM Module in Text Mode
        delay(1000);  // Delay of 1 second
        mySerial.println("AT+CMGS=\"+919110523264\"\r"); // Replace x with the mobile number
        delay(1000);
        sendSMS("Motion detected!");
        break;

      case 'r':
        mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
        delay(1000);
        break;
    }
  if (mySerial.available() > 0)
    Serial.write(mySerial.read());
}

void sendSMS(String message) {
  mySerial.println(message);// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z for saying the end of SMS to the module
  delay(1000);
}