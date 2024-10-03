#include "MotorControl.h"

// Motor and sensor variables
int distance = 0;
int speedMicroseconds = 1000; // Microsecond value for ESC control
Servo esc;                    // Servo object to control ESC
bool objectDetected = false;  // Flag to indicate if an object is detected

// Function to measure distance using the HC-SR04
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the duration of high signal on echo pin
  long duration = pulseIn(echoPin, HIGH, 30000);  // 30ms timeout for pulseIn to detect signal loss
  // Calculate distance in cm
  int distance = duration * 0.034 / 2;

  // If the distance is 0 or no echo is received, return a large value indicating no object
  if (duration == 0) {
    return -1;  // No object detected
  }
  return distance;
}

// Function to set motor speed and LEDs based on distance
void setMotorSpeed(int distance) {
  // Check if a valid distance is detected
  if (distance != -1) {
    objectDetected = true;  // Set object detected flag
    // Map distance to ESC PWM value in microseconds (1000-2000)
    speedMicroseconds = map(distance, 2, 100, 2000, 1000); // Closer distance -> higher speed
    speedMicroseconds = constrain(speedMicroseconds, 1000, 2000); // Ensure value is within 1000-2000 µs
    esc.writeMicroseconds(speedMicroseconds);                // Set motor speed using microseconds

    // Turn on LEDs based on the distance
    int numLEDs = map(distance, 2, 100, 5, 0);  // Map distance to number of LEDs on
    for (int i = 0; i < 5; i++) {
      if (i < numLEDs) {
        digitalWrite(ledPins[i], HIGH);  // Turn on LEDs based on distance
      } else {
        digitalWrite(ledPins[i], LOW);   // Turn off the remaining LEDs
      }
    }
  } else {
    // No object detected, set motor to minimum speed and turn off all LEDs
    objectDetected = false;
    resetMotorAndLEDs();
  }
}

// Function to reset motor and LEDs to initial state (e.g., upon disconnect or no object)
void resetMotorAndLEDs() {
  speedMicroseconds = 1000;     // Minimum throttle (1000 µs)
  esc.writeMicroseconds(speedMicroseconds);  // Set motor to minimum throttle
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);  // Turn off all LEDs
  }
  Serial.println("No object detected. Motor and LEDs reset.");
}

// Function to calibrate ESC using microsecond values
void calibrateESC() {
  // Attach the ESC to the designated pin
  esc.attach(escPin);

  // Calibrate the ESC with maximum and minimum throttle using microseconds
  esc.writeMicroseconds(2000);    // Maximum throttle (2000 µs)
  delay(2000);                    // Hold for 2 seconds
  esc.writeMicroseconds(1000);    // Minimum throttle (1000 µs)
  delay(2000);                    // Hold for 2 seconds
}
