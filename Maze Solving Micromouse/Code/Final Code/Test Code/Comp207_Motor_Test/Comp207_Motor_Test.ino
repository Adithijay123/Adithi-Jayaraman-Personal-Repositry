//declare pins for motor 1
int pinMotor1a = 0;
int pinMotor1b = 1;
//declare pins for motor 2
int pinMotor2a = 2;
int pinMotor2b = 3;
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
 pinMode(pinMotor1a, OUTPUT);
 pinMode(pinMotor1b, OUTPUT);
 pinMode(pinMotor2a, OUTPUT);
 pinMode(pinMotor2b, OUTPUT);
}
void loop() {
 //test the motions of the left motor
 leftMotorForward(127);
 delay(1000);
 leftMotorStop();
 delay(1000);
 leftMotorForward(127);
 delay(1000);
 leftMotorStop();
 delay(1000);
 //test the motions of the left motor
 rightMotorForward(127);
 delay(1000);
 rightMotorStop();
 delay(1000);
 rightMotorForward(127); 
 delay(1000);
 rightMotorStop();
 delay(1000);
}
