/*************************************************** 
 Arduino motor controller and logic for Aaron, the open-source robot,
 developed as a live-in exercise and game buddy in skileld nursing facilities
 to promote feelings of agency and self-efficacy, and to inhibit learned helplessness.

 Aaron is based on Aster (https://www.thingiverse.com/thing:3992150), which is a modified 
 Poppy robot (https://www.thingiverse.com/thing:2280067), with additional hardware modification
 plus low level onboard logic and higher level PC based interactions. 
 The project github page ()  includes:
  - All software source code (this microcontroller and all PC-side code)
  - Wiring diagrams and circuit schematics
  - All chassis part 3D model files 
  - Electrical & Mechanical BoMs
  - Assembly & setup instructions
  - Operating manual
  - Programmer guide
  
 Additionally, the project page has links to the heftier system content including:
  - Audio files
  - 3D model part files for the mechanical assembly
  - ???????
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "constants.h"
#include "servoControl.h"




void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  // Handles our initialization of the 16 channel servo driver board & remaining servos
  initServos();

  delay(10);
}



void loop() {
  // Get instruction string from PC
  // split movement control from eye control
  // send servo commands
  // send eye commands
  // maybe have all the eye stuff handled by a separate lil trinket? for sanity?
  // and just send eye commands to it?
  // profit????
  delay(300);
}
