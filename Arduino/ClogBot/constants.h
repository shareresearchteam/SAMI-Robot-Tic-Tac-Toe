/*************************************************** 
This contains all our constant definitions, including:
 - Motor specific tuning
 - Motor definitions
 - Pin definitions


 ****************************************************/
#ifndef CONSTANTS_H
#define CONSTANTS_H

//Pin Declarations
// The data pin for our LED Eyes
#define EYES_PIN 7
// The pin that controls the relay providing power to the servos
#define SERVO_RELAY1 1 // LEFT ARM
#define SERVO_RELAY2 2 //TORSO CONTROL
#define SERVO_RELAY3 3 //LEFT LEGS
#define SERVO_RELAY4 4 //RIGHT LEG
#define SERVO_RELAY5 5 //RIGHT ARM
#define SERVO_RELAY6 6 //HEAD


/********** Eye Details *********/
bool isSerpentine = true;
bool followColumnFirst = false;
bool isTwoPanels = true;

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

/********** Motor Definitions **********/
/*
 The left side and right side arm and leg motor chains are attached through
 the Adafruit 16 channel servo driver: https://www.adafruit.com/product/815
 The remaining head and torso control are controlled directly from the arduino (for the moment)
 Using the enum here, the left and right side enum positions can align directly with the pin
 wiring on the driver board, meaning we can use them for calling each motor directly
*/
const int NumPins = 32;

// Define a global array for joint angles
extern int jointIDs[NumPins];
extern int jointAngles[NumPins];
extern int numJointsRecv;

/********** Eye Control Variables **********/
// Emote variables to share for the Eyes data
//extern bool newEmote = false;
//extern int currentEmote = 0;


/********** Pin Definitions **********/
// Eyes //
// We use non-PWM pins here
//#define LEFT_EYE_PIN 7
//#define RIGHT_EYE_PIN 4


// Head & Torso //
// Must be PWM pins
//#define HEAD_NOD_PIN 3
//#define HEAD_TURN_PIN 5
//#define HEAD_TILT_PIN 6
//#define TORSO_BOW_PIN 9
//#define TORSO_TILT_PIN 10


#endif
