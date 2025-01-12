#include <Servo.h>
#include <NewPing.h>

// Pin Definitions
#define ECHO_PIN     A3       // Ultrasonic sensor echo pin
#define TRIGGER_PIN  A5       // Ultrasonic sensor trigger pin
#define LEFTLEG      5        // Left leg servo pin
#define RIGHTLEG     9        // Right leg servo pin
#define LEFTFOOT     7        // Left foot servo pin
#define RIGHTFOOT    11       // Right foot servo pin
#define HEAD         3        // Head servo pin

// Constants
#define MAX_DISTANCE 400      // Maximum ultrasonic sensor range in cm
int Min_DISTANCE = 10;        // Minimum distance threshold in cm

// Ultrasonic and Servo Objects
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo Lleg, Rleg, Lfoot, Rfoot, Head;

// Servo Centers (neutral positions)
int Hcenter = 90;             // Head center position
int RLcenter = 90;            // Right leg center
int RFcenter = 90;            // Right foot center
int LLcenter = 90;            // Left leg center
int LFcenter = 90;            // Left foot center

// Movement Parameters
int tAngle = 20;              // Tilt angle for forward movement
int uAngle = 25;              // Tilt angle for turning
int sAngle = 25;              // Spare variable (unused here)
int Speed = 50;               // Delay for servo movement (in ms)

// State Definitions
enum State {
  INIT,                       // Initialization state
  IDLE,                       // Waiting state
  SCAN_CENTER,                // Scanning forward
  SCAN_LEFT,                  // Scanning left
  SCAN_RIGHT,                 // Scanning right
  FORWARD,                    // Moving forward
  TURN_LEFT,                  // Turning left
  TURN_RIGHT                  // Turning right
};

State currentState = INIT;    // Initial state

// Function Prototypes
void Dance();                 // Dance function (if needed later)
void Forward(byte steps, byte speed); // Move forward
void TurnLeft(byte steps, byte speed); // Turn left
void TurnRight(byte steps, byte speed); // Turn right
int GetSonar();               // Get distance from ultrasonic sensor
void CenterServos();          // Reset servos to center positions
void TiltRightUp(byte ang, byte sp); // Tilt right leg up
void TiltRightDown(byte ang, byte sp); // Tilt right leg down
void TiltLeftUp(byte ang, byte sp); // Tilt left leg up
void TiltLeftDown(byte ang, byte sp); // Tilt left leg down

// Setup Function
void setup() {
  Serial.begin(19200);        // Initialize serial communication
  Serial.println("Biped Catbot setup is running.");

  // Attach Servos
  Lleg.attach(LEFTLEG);
  Rleg.attach(RIGHTLEG);
  Lfoot.attach(LEFTFOOT);
  Rfoot.attach(RIGHTFOOT);
  Head.attach(HEAD);

  CenterServos();             // Center all servos
  delay(500);

  currentState = IDLE;        // Transition to idle state
  Serial.println("Biped Catbot is ready.");
}

// Main Loop
void loop() {
  switch (currentState) {
    case INIT:
      CenterServos();         // Center servos
      delay(500);
      currentState = IDLE;    // Transition to idle
      break;

    case IDLE:
      Serial.println("Idle state."); // Wait state
      delay(1000);
      currentState = SCAN_CENTER;   // Start scanning forward
      break;

    case SCAN_CENTER: {
      Head.write(Hcenter);          // Move head to center
      unsigned int cmCenter = GetSonar();

      if (cmCenter < Min_DISTANCE) {
        currentState = SCAN_RIGHT;  // Scan right if obstacle detected
      } else {
        currentState = FORWARD;     // Move forward if path is clear
      }
      break;
    }

    case SCAN_RIGHT: {
      Head.write(Hcenter + 45);     // Move head to the right
      unsigned int cmRight = GetSonar();

      if (cmRight > Min_DISTANCE) {
        currentState = TURN_RIGHT; // Turn right if path is clear
      } else {
        currentState = SCAN_LEFT;  // Scan left otherwise
      }
      break;
    }

    case SCAN_LEFT: {
      Head.write(Hcenter - 45);     // Move head to the left
      unsigned int cmLeft = GetSonar();

      if (cmLeft > Min_DISTANCE) {
        currentState = TURN_LEFT;  // Turn left if path is clear
      } else {
        currentState = IDLE;       // Return to idle if all paths blocked
      }
      break;
    }

    case FORWARD: {
      unsigned int cmCenter = GetSonar();
      if (cmCenter < Min_DISTANCE) {
        currentState = SCAN_RIGHT; // Scan right if obstacle ahead
      } else {
        int nSteps = cmCenter / 5; // Limit steps based on distance
        if (nSteps > 5) nSteps = 5;
        Forward(nSteps, Speed);   // Move forward
        currentState = SCAN_CENTER; // Resume scanning
      }
      break;
    }

    case TURN_RIGHT:
      TurnRight(5, Speed);        // Turn right
      currentState = SCAN_CENTER; // Resume scanning
      break;

    case TURN_LEFT:
      TurnLeft(5, Speed);         // Turn left
      currentState = SCAN_CENTER; // Resume scanning
      break;
  }
}

// Utility Functions
int GetSonar() {
  unsigned int uS = sonar.ping();  // Get ultrasonic reading
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
  return uS / US_ROUNDTRIP_CM;
}

void CenterServos() {
  Lleg.write(LLcenter);           // Center left leg
  Rleg.write(RLcenter);           // Center right leg
  Lfoot.write(LFcenter);          // Center left foot
  Rfoot.write(RFcenter);          // Center right foot
  Head.write(Hcenter);            // Center head
  delay(1000);
}

void Forward(byte steps, byte speed) {
  for (int i = 0; i < steps; i++) {
    TiltRightUp(tAngle, speed);
    TiltLeftDown(tAngle, speed);
    TiltRightDown(tAngle, speed);
    TiltLeftUp(tAngle, speed);
  }
}

void TurnLeft(byte steps, byte speed) {
  for (int i = 0; i < steps; i++) {
    TiltRightUp(uAngle, speed);
    TiltLeftDown(uAngle, speed);
    TiltRightDown(uAngle, speed);
    TiltLeftUp(uAngle, speed);
  }
}

void TurnRight(byte steps, byte speed) {
  for (int i = 0; i < steps; i++) {
    TiltLeftUp(uAngle, speed);
    TiltRightDown(uAngle, speed);
    TiltLeftDown(uAngle, speed);
    TiltRightUp(uAngle, speed);
  }
}

void TiltRightUp(byte ang, byte sp) {
  Rleg.write(RLcenter + ang); // Raise right leg
  Lleg.write(LLcenter);       // Keep left leg neutral
  delay(sp);
}

void TiltRightDown(byte ang, byte sp) {
  Rleg.write(RLcenter);       // Lower right leg
  Lleg.write(LLcenter);       // Keep left leg neutral
  delay(sp);
}

void TiltLeftUp(byte ang, byte sp) {
  Lleg.write(LLcenter - ang); // Raise left leg
  Rleg.write(RLcenter);       // Keep right leg neutral
  delay(sp);
}

void TiltLeftDown(byte ang, byte sp) {
  Lleg.write(LLcenter);       // Lower left leg
  Rleg.write(RLcenter);       // Keep right leg neutral
  delay(sp);
}
