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
  analogWrite(pinMotorLeftForward, constrain(power, 0, 255)); // Adjusted speed
}

void leftMotorBackward(int power) {
  digitalWrite(pinMotorLeftForward, LOW);
  analogWrite(pinMotorLeftBackward, constrain(power, 0, 255)); // Adjusted speed
}

void rightMotorForward(int power) {
  digitalWrite(pinMotorRightBackward, LOW);
  analogWrite(pinMotorRightForward, constrain(power, 0, 255)); // Adjusted speed
}

void rightMotorBackward(int power) {
  digitalWrite(pinMotorRightForward, LOW);
  analogWrite(pinMotorRightBackward, constrain(power, 0, 255)); // Adjusted speed
}

void stopMotors() {
  digitalWrite(pinMotorLeftForward, LOW);
  digitalWrite(pinMotorLeftBackward, LOW);
  digitalWrite(pinMotorRightForward, LOW);
  digitalWrite(pinMotorRightBackward, LOW);
}

void reverseAndTurn() {
  // Reverse both motors for a short time
  leftMotorBackward(30); // Faster reverse
  rightMotorBackward(30);
  delay(500); // Reverse duration

  // Decide turn direction based on side sensors
  if (isSensorActive(pinTCRTLeft)) {
    // Turn right
    rightMotorForward(25); 
    leftMotorBackward(30); 
    delay(700); 
  } else if (isSensorActive(pinTCRTRight)) {
    // Turn left
    leftMotorForward(25);
    rightMotorBackward(30); 
    delay(700);
  } else {
    // Default to right turn
    rightMotorForward(25); 
    leftMotorBackward(30); 
    delay(700);
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
    rightMotorForward(25);
    leftMotorBackward(30);
  } else if (frontActive && rightActive) {
    // Turn left
    leftMotorForward(30);
    rightMotorBackward(25);
  } else if (frontActive) {
    // Default turn when only front sensor is active
    rightMotorForward(25);
    leftMotorBackward(30);
  } else if (leftActive) {
    // Slight right correction
    leftMotorForward(25);
    rightMotorForward(30);
  } else if (rightActive) {
    // Slight left correction
    leftMotorForward(30);
    rightMotorForward(25);
  } else {
    // Move forward
    leftMotorForward(30);
    rightMotorForward(30);
  }

  // Non-blocking delay for responsiveness
  delay(50);
}
