#include <OneButton.h>

const int buttonPin = 2;   // The push button pin
const int light1Pin = 3;   // Pin for the first light
const int light2Pin = 4;   // Pin for the second light

bool lightsOn1 = false;     // Variable to store the state of lights
bool lightsOn2 = false;
bool lightsOn = false;     

OneButton button(buttonPin, true); // Initialize OneButton object with pullup enabled

void setup() {
  pinMode(light1Pin, OUTPUT);
  pinMode(light2Pin, OUTPUT);
  
  // Setup button
  button.attachLongPressStop(buttonClick);
  button.attachDoubleClick(Click);
  button.attachClick(SClick);
}

void loop() {
  // Update OneButton library
  button.tick();
}
void SClick() {
  // Toggle lights state
  lightsOn = !lightsOn;

  // Control lights based on the lightsOn state
  if (lightsOn) {
    digitalWrite(light1Pin, HIGH);
    digitalWrite(light2Pin, HIGH);
  } else {
    digitalWrite(light1Pin, LOW);
    digitalWrite(light2Pin, LOW);
  }
}
void buttonClick() {
  // Toggle lights state
  lightsOn1 = !lightsOn1;

  // Control lights based on the lightsOn state
  if (lightsOn1) {
    digitalWrite(light1Pin, HIGH);
  } else {
    digitalWrite(light1Pin, LOW);
  }
}
void Click() {
  // Toggle lights state
  lightsOn2 = !lightsOn2;

  // Control lights based on the lightsOn state
  if (lightsOn2) {
    digitalWrite(light2Pin, HIGH);
  } else {
    digitalWrite(light2Pin, LOW);
  }
}
