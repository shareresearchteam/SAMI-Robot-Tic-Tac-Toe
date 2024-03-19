/*************************************************** 
This contains all our constant definitions, including:
 - Motor specific tuning
 - Motor definitions
 - Pin definitions


 ****************************************************/
#ifndef CONSTANTS_H
#define CONSTANTS_H


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
enum joints {
// Left side //
  LeftChest,
  LeftShoulder,
  LeftBicep,
  LeftElbow,
  LeftGripper,
  LeftHip,
  LeftKnee,
  LeftAnkle,
// Right side //
  RightChest,
  RightShoulder,
  RightBicep,
  RightElbow,
  RightGripper,
  RightHip,
  RightKnee,
  RightAnkle,
// Head control //
  HeadNod,
  HeadTurn,
  HeadTilt,
// Torso control //
  TorsoBow,
  TorsoTilt
};

// Define a global array for joint angles
extern int jointAngles[TorsoTilt+1]; // Assuming TorsoTilt is the last item in the enum

//extern int jointAnglesInitial = [170,155,90,0,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21]; // Assuming TorsoTilt is the last item in the enum

/********** Pin Definitions **********/
// Eyes //
// We use non-PWM pins here
#define LEFT_EYE_PIN 2
#define RIGHT_EYE_PIN 4

// Head & Torso //
// Must be PWM pins
#define HEAD_NOD_PIN 3
#define HEAD_TURN_PIN 5
#define HEAD_TILT_PIN 6
#define TORSO_BOW_PIN 9
#define TORSO_TILT_PIN 10


#endif
