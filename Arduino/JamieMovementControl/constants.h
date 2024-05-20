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
#define EYES_PIN 7
// The pin that controls the relay providing power to the servos
#define SERVO_RELAY1 1 // LEFT ARM
#define SERVO_RELAY2 2 //TORSO CONTROL
#define SERVO_RELAY3 3 //LEFT LEGS
#define SERVO_RELAY4 4 //RIGHT LEG
#define SERVO_RELAY5 5 //RIGHT ARM
#define SERVO_RELAY6 6 //HEAD

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
// We also define two global arrays, one for the joint pin numbers, 
// and a second for the corresponding joint angle
extern int jointIDs[NumPins];
extern int jointAngles[NumPins];
// We also have a variable we use for tracking the number of joints we recieved in a joint message
extern int numJointsRecv;

/********** Motor Tuning Constants **********/
/*
 Depending on your servo make, the pulse width min and max may vary, you 
 want these to be as small/large as possible without hitting the hard stop
 for max range. You'll have to tweak them as necessary to match the servos you
 have!
*/
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

//#define SERVOMIN  800 // This is the 'minimum' pulse length count (out of 4096)
//#define SERVOMAX  3500 // This is the 'maximum' pulse length count (out of 4096)
//#define USMIN  3200 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 800
//#define USMAX  14000 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 3500
//#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

#endif
