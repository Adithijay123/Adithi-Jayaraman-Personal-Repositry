#include <Arduino.h>

// LED control pins
const int pinLEDLeft = 18;  // Left TCRT LED
const int pinLEDFront = 19; // Front TCRT LED
const int pinLEDRight = 20; // Right TCRT LED

// TCRT sensor pins
const int pinTCRTLeft = 26;  // Left TCRT
const int pinTCRTFront = 28; // Front TCRT
const int pinTCRTRight = 27; // Right TCRT

// Motor control pins
const int pinMotorLeftForward = 0;
const int pinMotorLeftBackward = 1;
const int pinMotorRightForward = 2;
const int pinMotorRightBackward = 3;

// Threshold for sensor activation
const int sensorThreshold = 950;

// LED control function
void setLED(int pin, bool state) {
  digitalWrite(pin, state);
}

// TCRT sensor read function
bool isSensorActive(int pin) {
  return analogRead(pin) <= sensorThreshold;
}

// Motor control functions
void leftMotorForward(int power) {
  digitalWrite(pinMotorLeftBackward, LOW);
  analogWrite(pinMotorLeftForward, constrain(power, 0, 100));
}

void leftMotorBackward(int power) {
  digitalWrite(pinMotorLeftForward, LOW);
  analogWrite(pinMotorLeftBackward, constrain(power, 0, 100));
}

void rightMotorForward(int power) {
  digitalWrite(pinMotorRightBackward, LOW);
  analogWrite(pinMotorRightForward, constrain(power, 0, 100));
}

void rightMotorBackward(int power) {
  digitalWrite(pinMotorRightForward, LOW);
  analogWrite(pinMotorRightBackward, constrain(power, 0, 100));
}

void stopMotors() {
  digitalWrite(pinMotorLeftForward, LOW);
  digitalWrite(pinMotorLeftBackward, LOW);
  digitalWrite(pinMotorRightForward, LOW);
  digitalWrite(pinMotorRightBackward, LOW);
}

void reverseAndTurn() {
  // Reverse both motors for a short time
  leftMotorBackward(30);
  rightMotorBackward(30);
  delay(500); // Reverse duration

  // Turn based on sensor states after reversing
  if (isSensorActive(pinTCRTLeft)) {
    // Turn right
    rightMotorForward(10);
    leftMotorBackward(30);
    delay(500); // Turn duration
  } else if (isSensorActive(pinTCRTRight)) {
    // Turn left
    leftMotorForward(30);
    rightMotorBackward(10);
    delay(500); // Turn duration
  }
  stopMotors();
}

void setup() {
  // Initialize LEDs
  pinMode(pinLEDLeft, OUTPUT);
  pinMode(pinLEDFront, OUTPUT);
  pinMode(pinLEDRight, OUTPUT);

  // Initialize TCRT sensor pins
  pinMode(pinTCRTLeft, INPUT);
  pinMode(pinTCRTFront, INPUT);
  pinMode(pinTCRTRight, INPUT);

  // Initialize motor control pins
  pinMode(pinMotorLeftForward, OUTPUT);
  pinMode(pinMotorLeftBackward, OUTPUT);
  pinMode(pinMotorRightForward, OUTPUT);
  pinMode(pinMotorRightBackward, OUTPUT);

  delay(300);
  setLED(pinLEDLeft, true);
  delay(1000);
  setLED(pinLEDFront, true);
  delay(1000);
  setLED(pinLEDRight, true);  
  delay(1000);
  setLED(pinLEDLeft, false);
  setLED(pinLEDFront, false);
  setLED(pinLEDRight, false);
}

void loop() {
  // Read sensor states
  bool leftActive = isSensorActive(pinTCRTLeft);
  bool frontActive = isSensorActive(pinTCRTFront);
  bool rightActive = isSensorActive(pinTCRTRight);

  // Update LEDs based on sensor states
  setLED(pinLEDLeft, leftActive);
  setLED(pinLEDFront, frontActive);
  setLED(pinLEDRight, rightActive);

  // Control logic
  if (frontActive && leftActive && rightActive) {
    reverseAndTurn(); // Handle dead-end
  } else if (frontActive && leftActive) {
    // Turn right
    rightMotorForward(20);
    leftMotorBackward(40);
  } else if (frontActive && rightActive) {
    // Turn left
    leftMotorForward(40);
    rightMotorBackward(20);
  } else if (frontActive) {
    // Default turn when only front sensor is active
    rightMotorForward(20);
    leftMotorBackward(40);
  } else if (leftActive) {
    // Slight right correction
    leftMotorForward(20);
    rightMotorForward(40);
  } else if (rightActive) {
    // Slight left correction
    leftMotorForward(40);
    rightMotorForward(20);
  } else {
    // Move forward
    leftMotorForward(40);
    rightMotorForward(40);
  }

  // Non-blocking delay for responsiveness
  delay(50);
}
