#include "Servo.h"

enum State_enum {BACKWARD, FORWARD,};
enum Sensors_enum {NONE, BOTH, };

static Sensors_enum sensors;
static State_enum state;
 
void motors_backward();
void motors_forward();

int timer;
int leftSensor;
int rightSensor;
Servo leftServo;
Servo rightServo;

void setup()
{
  Serial.begin(9600);
  leftServo.attach(9);
  rightServo.attach(10);
  state = FORWARD;
}
 
void loop()
{
  state_machine_run(sensors); 

 
  leftSensor = analogRead(A1); // Set the pins to your sensor pin
  rightSensor = analogRead(A2);
  Serial.println(leftSensor);
  Serial.println(rightSensor);

  if (rightSensor > 930 && leftSensor > 930) 
  {
    sensors = BOTH;
  }
  if (rightSensor < 860 && leftSensor < 860) 
  {
    sensors = NONE;
  }

  delay(10);
}
 
void state_machine_run(uint8_t sensors) //Goes forward til it senses an object, then it moves backwards for a second 
{
  switch(state)
  {
    case FORWARD:
      if(sensors == BOTH){
        motors_forward();
      }
      else {
        motors_backward();
        timer = millis();
        state = BACKWARD;
      }
         
      break;
       
    case BACKWARD:
     
   if(timer - millis() > 1000){
        state = FORWARD;
      }
      break;
  }
}

void motors_backward()
{
  //code for driving backward
  leftServo.write(0);
  rightServo.write(180);
  delay(1000);
}
 
void motors_forward()
{
  //code for driving forward  
  leftServo.write(180);
  rightServo.write(0);
  delay(1000);
}
 
