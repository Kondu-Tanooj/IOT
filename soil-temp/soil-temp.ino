#include <DHT11.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);// connect to A4 & A5
DHT11 dht11(2);// DHT11 connect to digital 2
int sensorPin = A0; // Define the analog pin for the moisture sensor to A0
int moistureValue;
void setup() {
  dht11.init();
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  pinMode(3,OUTPUT);// for motor (Relay Module) to digital 3
}

void loop() {
  moistureValue = analogRead(sensorPin);
  Serial.println("Moisture Value: ");
  Serial.println(moistureValue);
  if(moistureValue<500)
  {
   digitalWrite(3,HIGH);
  delay(1000);
  }
  else
  {
  digitalWrite(3,LOW ); //high to continue proving signal and water supply
  }
  int temperature = dht11.readTemperature();
  int humidity = dht11.readHumidity();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(temperature);
  lcd.print(" °C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");
  delay(1000);
}
// int pirPin = 2; // Connect the PIR sensor's output pin to digital pin 2
// int ledPin = 13; // Built-in LED on most Arduino boards

// void setup() {
//   pinMode(pirPin, INPUT); // Set the PIR sensor pin as an input
//   pinMode(ledPin, OUTPUT); // Set the LED pin as an output
//   Serial.begin(9600); // Initialize serial communication for debugging
// }

// void loop() {
//   int pirState = digitalRead(pirPin); // Read the PIR sensor's output
//   if (pirState == HIGH) {
//     // Motion detected
//     digitalWrite(ledPin, HIGH); // Turn on the LED
//     Serial.println("Motion detected!");
//     delay(1000); // Delay for 1 second
//   } else {
//     // No motion
//     digitalWrite(ledPin, LOW); // Turn off the LED
//   }
// }
