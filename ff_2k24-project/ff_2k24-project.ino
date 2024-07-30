#include <Wire.h> 
#include <hd44780.h>          // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h>  // i2c expander i/o class header

hd44780_I2Cexp lcd;

// Define ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  lcd.backlight();   // turn on LCD backlight

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Clears the LCD screen
  lcd.clear();
     lcd.setCursor(0,0);
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the time it takes for the ultrasonic signal to bounce back
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance
  int distance = duration * 0.034 / 2;

  // Print distance to serial monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  // Print distance to LCD based on different ranges
  if (distance < 30) {
    lcd.print("karuna");
  } else if (distance < 60) {
    lcd.print("srujana");
  } else if (distance < 120) {
    lcd.print("sai kiran");
  } else if (distance < 180) {
    lcd.print("saketh");
  } else {
    lcd.print("kiran kumar");
  }

  // Wait for a moment before taking another reading
  delay(1000);
}
