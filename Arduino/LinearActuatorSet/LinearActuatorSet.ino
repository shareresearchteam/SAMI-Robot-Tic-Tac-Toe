/*
 Controlling Actuonix Linear Actuator servo
*/

#include <Servo.h>
#define r_gripper 34
#define l_gripper 40

Servo myservo;  // create servo object to control a servo

int val = 20;   // variable to set linear actuator: range = 0 - 20

void setup() {
  myservo.attach(34);  // attaches the servo on pin to the servo object
  val = map(val, 0, 1023, 0, 20);
  myservo.write(val);
}

