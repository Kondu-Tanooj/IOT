
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trig =9;
const int echo =10;
long dur=0;
long dis=0;
void setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  // Additional setup code
}
void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  dur=pulseIn(echo,HIGH);
  dis=dur*0.034 /2;
  lcd.setCursor(0, 0);
  lcd.print("DISTANCE:-");
  delay(1000);

  lcd.setCursor(0, 1);
  lcd.print(dis);
  lcd.print("cm");
  delay(800);

  lcd.clear();
  
  
  // Additional LCD control code
}