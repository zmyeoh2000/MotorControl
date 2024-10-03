#include <MotorControl.h>

// Define pins
const int trigPin = D1;
const int echoPin = D2;
const int escPin = D3;
const int ledPins[] = {D4, D5, D6, D7, D8};
const int numLEDs = 5;

// Create an instance of MotorControl
MotorControl motorControl(trigPin, echoPin, escPin, ledPins, numLEDs);

void setup() {
  Serial.begin(9600);
  motorControl.begin();  // Initialize the MotorControl library
  Serial.println("Setup complete!");
}

void loop() {
  // Measure distance
  int distance = motorControl.getDistance();
  Serial.print("Distance: ");
  if (distance != -1) {
    Serial.print(distance);
    Serial.println(" cm");
  } else {
    Serial.println("No object detected");
  }

  // Set motor speed and LEDs based on distance
  motorControl.setMotorSpeed(distance);
  
  // Add a short delay
  delay(200);
}

