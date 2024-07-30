#include <SoftwareSerial.h>
#include <Servo.h>

Servo servoMotor;
char t;
bool pump; // Initialize pump to true

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
  Serial.begin(9600);
}

void loop() {
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

  else if (t == 'W') { // turn led on or off)
    digitalWrite(5, HIGH);
    pump = true; // Set pump to true when water pump is turned on
  } else if (t == 'w') {
    digitalWrite(5, LOW);
    pump = false; // Set pump to false when water pump is turned off
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
  delay(100);

  if (pump == true) {
    int flameValue = analogRead(A0);
    // Adjust the flame threshold based on your sensor and environment
    if (flameValue > 200) {
      digitalWrite(5, HIGH);
      // Rotate the servo motor from 0 to 180 degrees
      for (int i = 0; i <= 180; i++) {
        servoMotor.write(i);
        delay(15); // Adjust the delay as needed
      }
      // Rotate the servo motor from 180 to 0 degrees
      for (int i = 180; i >= 0; i--) {
        servoMotor.write(i);
        delay(15); // Adjust the delay as needed
      }
    } else {
      digitalWrite(5, LOW);
      servoMotor.write(0);
      pump = false; // Set pump to false when flame condition is not met
    }
  }
}
