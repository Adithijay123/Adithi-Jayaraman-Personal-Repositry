int pinTCRT1 = 26;
int pinTCRT2 = 27;
int pinTCRT3 = 28;
int readTCRT1() {
 int reading = 0;
 reading = analogRead(pinTCRT1);
 return reading;
}
int readTCRT2() {
 int reading = 0;
 reading = analogRead(pinTCRT2);
 return reading;
}
int readTCRT3() {
 int reading = 0;
 reading = analogRead(pinTCRT3);
 return reading;
}
void setup() {
 pinMode(pinTCRT1, OUTPUT);
 pinMode(pinTCRT2, OUTPUT);
 pinMode(pinTCRT3, OUTPUT);
 Serial.begin(9600);
}
void loop() {
 //print the value from tcrt1
 Serial.print("tcrt1 = ");
 Serial.print(readTCRT1());
 //print the value from tcrt1
 Serial.print("tcrt2 = ");
 Serial.print(readTCRT2());
 //print the value from tcrt1
 Serial.print("tcrt3= ");
 Serial.print(readTCRT3());
 //println to actually send the text to the serial monitor
 Serial.println();
 //delay so the text is readable
 delay(100);
}
