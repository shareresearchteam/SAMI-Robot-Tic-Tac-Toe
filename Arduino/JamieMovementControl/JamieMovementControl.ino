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
#include <NeoEyes.h>
#include "constants.h"
#include "servoControl.h"
#include "serialComms.h"
String readString;

NeoEyes<EYES_PIN> roboEyes  = NeoEyes<EYES_PIN>(isSerpentine,followColumnFirst,isTwoPanels);

void setup() {
  pinMode(SERVO_RELAY1, OUTPUT); //pin 1 is the on and off for the servo relay power
  pinMode(SERVO_RELAY2, OUTPUT); //pin 2 is the on and off for the servo relay power
  pinMode(SERVO_RELAY3, OUTPUT); //pin 3 is the on and off for the servo relay power
  pinMode(SERVO_RELAY4, OUTPUT); //pin 4 is the on and off for the servo relay power
  pinMode(SERVO_RELAY5, OUTPUT); //pin 5 is the on and off for the servo relay power
  pinMode(SERVO_RELAY6, OUTPUT); //pin 6 is the on and off for the servo relay power

  // Eyes Setup!
  roboEyes.begin();
  roboEyes.setBrightness(50); // Set the brightness to something less than max (255) to avoid blinding yourself

  // Servo bits
  // Turn off power to all the servos to start
  setServoRelays(false);
  
  //int initial[]={170,155,90,90,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21}; //initial servo values
  Serial.begin(115200);
  //Serial.println("21 channel Servo test!");

  // Handles our initialization of the 16 channel servo driver board & remaining servos
  initServos();
  //setAllJointsInitial(initial);

  delay(10);
}


void loop() {
// Check for any serial communications
recvWithStartEndMarkers();
if(newData) {
  Serial.println("Got new data!");
  Serial.print("Message type: ");
        Serial.println(msgType);
  // If we got a new emote instruction, then set the eyes
  if(newEmote) {
    Serial.print("Emote Recieved: ");
          Serial.println(currentEmote);
    roboEyes.setStandardEmote(currentEmote);
    newEmote = false;
  }
  else if(newJoints) {
    setServoRelays(true);
    setFromJointMsg();
    newJoints = false;
  }
  newData = false;
}

delay(10);
  
}
