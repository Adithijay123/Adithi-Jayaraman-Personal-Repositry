// LED control pins
int pinLED1 = 18;
int pinLED2 = 19;
int pinLED3 = 20;

// TCRT sensor pins
int pinTCRT1 = 26;
int pinTCRT2 = 27;
int pinTCRT3 = 28;

// Motor control pins
int pinMotor1a = 0;
int pinMotor1b = 1;
int pinMotor2a = 2;
int pinMotor2b = 3;

// LED control functions
void setLED1(bool light) {
  digitalWrite(pinLED1, light);
}

void setLED2(bool light) {
  digitalWrite(pinLED2, light);
}

void setLED3(bool light) {
  digitalWrite(pinLED3, light);
}

// TCRT sensor read functions
int readTCRT1() {
  return analogRead(pinTCRT1);
}

int readTCRT2() {
  return analogRead(pinTCRT2);
}

int readTCRT3() {
  return analogRead(pinTCRT3);
}

// Motor control functions
void leftMotorForward(int power) {
  digitalWrite(pinMotor1a, LOW);
  analogWrite(pinMotor1b, power);
}

void leftMotorBackward(int power) {
  digitalWrite(pinMotor1b, LOW);
  analogWrite(pinMotor1a, power);
}

void leftMotorStop() {
  digitalWrite(pinMotor1a, LOW);
  digitalWrite(pinMotor1b, LOW);
}

void rightMotorForward(int power) {
  digitalWrite(pinMotor2a, LOW);
  analogWrite(pinMotor2b, power);
}

void rightMotorBackward(int power) {
  digitalWrite(pinMotor2b, LOW);
  analogWrite(pinMotor2a, power);
}

void rightMotorStop() {
  digitalWrite(pinMotor2a, LOW);
  digitalWrite(pinMotor2b, LOW);
}

void setup() {
  // Initialize LED pins
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);

  // Initialize TCRT sensor pins
  pinMode(pinTCRT1, OUTPUT);
  pinMode(pinTCRT2, OUTPUT);
  pinMode(pinTCRT3, OUTPUT);

  // Initialize motor pins
  pinMode(pinMotor1a, OUTPUT);
  pinMode(pinMotor1b, OUTPUT);
  pinMode(pinMotor2a, OUTPUT);
  pinMode(pinMotor2b, OUTPUT);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Test LEDs
  setLED1(1);
  delay(200);
  setLED2(1);
  delay(200);
  setLED3(1);
  delay(200);
  setLED1(0);
  delay(200);
  setLED2(0);
  delay(200);
  setLED3(0);
  delay(200);

  // Read TCRT sensors and print values
  Serial.print("TCRT1 = ");
  Serial.print(readTCRT1());
  Serial.print(", TCRT2 = ");
  Serial.print(readTCRT2());
  Serial.print(", TCRT3 = ");
  Serial.println(readTCRT3());
  delay(100);

  // Test left motor forward and backward
  leftMotorForward(127);
  delay(1000);
  leftMotorBackward(127);
  delay(1000);
  leftMotorStop();
  delay(1000);

  // Test right motor forward and backward
  rightMotorForward(127);
  delay(1000);
  rightMotorBackward(127);
  delay(1000);
  rightMotorStop();
  delay(1000);
}
