#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Servo.h>

// Pin definitions
const int trigPin = D1;   // Trigger pin of the ultrasonic sensor
const int echoPin = D2;   // Echo pin of the ultrasonic sensor
const int escPin = D3;    // ESC control pin
const int ledPins[] = {D4, D5, D6, D7, D8};  // LED pins

// Motor and sensor variables
extern int distance;
extern int speedMicroseconds; // Microsecond value for ESC control
extern Servo esc;             // Servo object to control ESC
extern bool objectDetected;   // Flag to indicate if an object is detected

// Function declarations
int getDistance();
void setMotorSpeed(int distance);
void resetMotorAndLEDs();
void calibrateESC();

#endif // MOTORCONTROL_H
