#include <Encoder.h>

Encoder motor(6, 7);

long int pos = 0;

int ticksPerRevolution = 0;
int gearing = 0;
float wheelradius = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  pos = motor.read();
  float motorpos = float(pos)/(4.0*11.0);
  float wheelpos = motorpos / gearing;
  Serial.println(wheelpos);
}
