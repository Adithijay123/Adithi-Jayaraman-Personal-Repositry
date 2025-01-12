// LED control pins
int pinLED1 = 18; // Left TCRT LED
int pinLED2 = 19; // Front TCRT LED
int pinLED3 = 20; // Right TCRT LED

// TCRT sensor pins
int pinTCRT1 = 27; // Left TCRT
int pinTCRT2 = 28; // Front TCRT
int pinTCRT3 = 26; // Right TCRT

// Motor control pins
int pinMotor1a = 0;
int pinMotor1b = 1;
int pinMotor2a = 2;
int pinMotor2b = 3;

// Detection threshold
int detectionThreshold = 900; // Adjust based on sensor readings

// LED control functions
void setLED(int pin, bool state) {
  digitalWrite(pin, state);
}

// TCRT sensor read function
int readTCRT(int pin) {
  return analogRead(pin);
}

// Motor control functions
void leftMotorForward(int power) {
  digitalWrite(pinMotor1a, LOW);
  analogWrite(pinMotor1b, power);
}

void rightMotorForward(int power) {
  digitalWrite(pinMotor2a, LOW);
  analogWrite(pinMotor2b, power);
}

void leftMotorStop() {
  digitalWrite(pinMotor1a, LOW);
  digitalWrite(pinMotor1b, LOW);
}

void rightMotorStop() {
  digitalWrite(pinMotor2a, LOW);
  digitalWrite(pinMotor2b, LOW);
}

void moveForward() {
  leftMotorForward(50); // Adjust power as needed
  rightMotorForward(50); // Adjust power as needed
}

void stopMotors() {
  leftMotorStop();
  rightMotorStop();
}

// State definitions
enum State {
  MOVE_FORWARD,
  TURN_LEFT,
  TURN_RIGHT,
  STOP
};

// Current state
State currentState = MOVE_FORWARD;

void setup() {
  // Initialize LEDs
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);

  // Initialize TCRT sensor pins
  pinMode(pinTCRT1, INPUT);
  pinMode(pinTCRT2, INPUT);
  pinMode(pinTCRT3, INPUT);

  // Initialize motor control pins
  pinMode(pinMotor1a, OUTPUT);
  pinMode(pinMotor1b, OUTPUT);
  pinMode(pinMotor2a, OUTPUT);
  pinMode(pinMotor2b, OUTPUT);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int leftSensor = readTCRT(pinTCRT1);
  int frontSensor = readTCRT(pinTCRT2);
  int rightSensor = readTCRT(pinTCRT3);

  // Determine obstacle detection
  bool leftObstacle = (leftSensor < detectionThreshold);
  bool frontObstacle = (frontSensor < detectionThreshold);
  bool rightObstacle = (rightSensor < detectionThreshold);

  // Control LEDs based on sensor detection
  setLED(pinLED1, leftObstacle);
  setLED(pinLED2, frontObstacle);
  setLED(pinLED3, rightObstacle);

  // Debugging: Print sensor values and obstacle status
  Serial.print("Left: ");
  Serial.print(leftObstacle);
  Serial.print(", Front: ");
  Serial.print(frontObstacle);
  Serial.print(", Right: ");
  Serial.println(rightObstacle);

  // State machine logic
  switch (currentState) {
    case MOVE_FORWARD:
      if (frontObstacle || (leftObstacle && rightObstacle)) {
        currentState = STOP;
      } else if (rightObstacle) {
        currentState = TURN_LEFT;
      } else if (leftObstacle) {
        currentState = TURN_RIGHT;
      } else {
        moveForward();
        Serial.println("Action: Move Forward");
      }
      break;

    case TURN_LEFT:
      if (frontObstacle || (leftObstacle && rightObstacle)) {
        currentState = STOP;
      } else if (!rightObstacle) {
        currentState = MOVE_FORWARD;
      } else {
        leftMotorForward(50);
        rightMotorStop();
        Serial.println("Action: Turn Left");
      }
      break;

    case TURN_RIGHT:
      if (frontObstacle || (leftObstacle && rightObstacle)) {
        currentState = STOP;
      } else if (!leftObstacle) {
        currentState = MOVE_FORWARD;
      } else {
        rightMotorForward(50);
        leftMotorStop();
        Serial.println("Action: Turn Right");
      }
      break;

    case STOP:
      if (!frontObstacle && (!leftObstacle || !rightObstacle)) {
        currentState = MOVE_FORWARD;
      } else {
        stopMotors();
        Serial.println("Action: Stop");
      }
      break;
  }
}
