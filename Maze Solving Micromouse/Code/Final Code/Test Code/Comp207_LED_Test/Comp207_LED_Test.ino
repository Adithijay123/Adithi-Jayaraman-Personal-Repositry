int pinLED1 = 18;
int pinLED2 = 19;
int pinLED3 = 20;
void setLED1(bool light) {
 digitalWrite(pinLED1, light);
}
void setLED2(bool light) {
 digitalWrite(pinLED2, light);
}
void setLED3(bool light) {
 digitalWrite(pinLED3, light);
}
void setup() {
 pinMode(pinLED1, OUTPUT);
 pinMode(pinLED2, OUTPUT);
 pinMode(pinLED3, OUTPUT);
}
void loop() {
 //Turn the LEDs on, one by one
 setLED1(1);
 delay(200);
 setLED2(1);
 delay(200);
 setLED3(1);
 delay(200);
 //Turn the LEDs off, one by one
 setLED1(1);
 delay(200);
 setLED2(1);
 delay(200);
 setLED3(1);
 delay(200);
}
