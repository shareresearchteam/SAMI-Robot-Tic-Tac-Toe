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
#include <NeoEyes.h>
#include "constants.h"
#include "servoControl.h"
#include "serialComms.h"

// LED Panel definition: NeyoEyes<Panel data pin>(isSerpentine, followColumnFirst, isTwoPanels)
// In our case the eyes follows a row-first serpentine pattern (isSerpentine = true, followColumnFirst = false)
// and the eyes are two 8x8 panels connected in series (isTwoPanels = true)
// 
NeoEyes<EYES_PIN> roboEyes  = NeoEyes<EYES_PIN>(false, false, true);

// Setting up the servo bus controller communication on Serial1
// TODO: Do something with the temperature information 
// TODO: Figure out what we're doing for the power circuitry/relays
servoControl servoController(Serial1);

void setup() {
  // Set up our servo relay pins
  pinMode(SERVO_RELAY1, OUTPUT); //pin 1 is the on and off for the servo relay power
  pinMode(SERVO_RELAY2, OUTPUT); //pin 2 is the on and off for the servo relay power
  pinMode(SERVO_RELAY3, OUTPUT); //pin 3 is the on and off for the servo relay power
  pinMode(SERVO_RELAY4, OUTPUT); //pin 4 is the on and off for the servo relay power
  pinMode(SERVO_RELAY5, OUTPUT); //pin 5 is the on and off for the servo relay power
  pinMode(SERVO_RELAY6, OUTPUT); //pin 6 is the on and off for the servo relay power

  // Turn off power to all the servos to start
  setServoRelays(false);
  
  // Eyes Setup!
  roboEyes.begin();
  roboEyes.setBrightness(50); // Set the brightness to something less than max (255) to avoid blinding yourself

  Serial.begin(115200);
  // Handles our initialization of the bus servos and gives them a seperate, dedicated Serial line. In this case, Serial1
  servoController.begin();

  delay(10);
}

void loop() {
  // Check for any serial communications
  recvWithStartEndMarkers();
  if(newData) {
    //Serial.print("Message type: ");
    //Serial.println(msgType);
    // If we got a new emote instruction, then set the eyes
    if(newEmote) {
      //Serial.print("Emote Recieved: ");
      //Serial.println(currentEmote);
      roboEyes.setStandardEmote(currentEmote);
      newEmote = false;
    }
    // If we got new joint data
    else if(newJoints) {
      //Serial.print("Number Joints Recieved: ");
      //Serial.println(numJointsRecv);
      // Turn the servo relays on, just in case they currently are not
      setServoRelays(true);
      // Set the new joint values for the specific joint pins we recieved
      servoController.setFromJointMsg();
      newJoints = false;
    }
    newData = false;
  }
  // Every so many loops let's check the temperature of the servos, and cut power if they get ~spicy~
  
  delay(10);
}
