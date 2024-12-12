/*************************************************** 
This contains all our constant definitions, including:
 - Pin definitions
 - Motor definitions
 - Motor specific tuning

 ****************************************************/
#ifndef CONSTANTS_H
#define CONSTANTS_H

/********** Pin Definitions **********/
// The data pin for our LED Eyes
#define EYES_PIN 32
// The pin that controls the relay providing power to the servos
#define NECKTORSO_RELAY 33 // Pin for controlling power to the neck and torso motors
#define LEGS_RELAY 26 // Pin for controlling power to the leg motors
#define ARMS_RELAY 28 // Pin for controlling power to the arm motors


/********** Motor Definitions **********/
/*
 The left side and right side arm and leg motor chains are attached through
 the Adafruit 16 channel servo driver: https://www.adafruit.com/product/815
 The remaining head and torso control are controlled directly from the arduino (for the moment)
 Using the enum here, the left and right side enum positions can align directly with the pin
 wiring on the driver board, meaning we can use them for calling each motor directly
*/

// With two hat boards, we have 32 available servo motor pins, 
// so that's the maximum number of joint commands we could send in a single message
const int NumPins = 32;
// We also define some global arrays, one for the joint pin numbers, 
// and a second for the corresponding joint angle
extern uint8_t jointIDs[NumPins];
extern uint8_t jointAngles[NumPins];
// We also have a variable we use for tracking the number of joints we recieved in a joint message
extern int numJointsRecv;
extern uint8_t jointTime;

#endif
