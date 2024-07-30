#include <SoftwareSerial.h>
#include <Servo.h>

Servo servoMotor;
char t;
void setup() {
  pinMode(13, OUTPUT);  //left1 forward
  pinMode(12, OUTPUT);  //left1 reverse
  pinMode(11, OUTPUT);  //right1 forward
  pinMode(10, OUTPUT);  //right1 reverse
  pinMode(9, OUTPUT);   //left2 farward
  pinMode(8, OUTPUT);   //left2  back
  pinMode(3, OUTPUT);   //right2 forward
  pinMode(6, OUTPUT);   //right2 back
  pinMode(5, OUTPUT);   //water pump
  pinMode(4, OUTPUT);   //servo
  pinMode(A0, INPUT);   // Flame sensor
  servoMotor.attach(4);
  Serial.begin(9600);
  digitalWrite(5, LOW);
}

void loop() {
int flameValue = analogRead(A0);
Serial.println(flameValue);
  if (Serial.available()) {
    t = Serial.read();
    Serial.println(t);
  }

  if (t == 'B') { // move  forward(all motors rotate in forward direction)
    digitalWrite(12, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(6, HIGH);
  }

  else if (t == 'F') { // move reverse (all  motors rotate in reverse direction)
    digitalWrite(13, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(3, HIGH);
  }

  else if (t == 'R') { // turn right (left side motors rotate in forward direction,  right side motors doesn't rotate)
    digitalWrite(13, HIGH);
    digitalWrite(3, HIGH);
  }

  else if (t == 'L') { // turn left (right side motors rotate in forward direction, left  side motors doesn't rotate)
    digitalWrite(10, HIGH);
    digitalWrite(8, HIGH);
  }
  else if (t == 'S') { // STOP (all motors stop)
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
  }
  else if (t == 'J'){
    int servalue = Serial.parseInt();
    servoMotor.write(servalue);
    }
  else if (t == 'X'){
  digitalWrite(5, HIGH);
  }
  else if (t == 'Y'){
  digitalWrite(5, LOW);
  }
  delay(100);
}