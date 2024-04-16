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
#include "Global_Variables.h"
#include "newCommunication.h"
String readString;

NeoEyes<EYES_PIN> roboEyes;

void setup() {
  pinMode(SERVO_RELAY, OUTPUT); //pin 4 is the on and off for the servo relay power
  pinMode(PING_PIN, OUTPUT); //enable pingPing as an OUTPUT
  pinMode(ECHO_PIN, INPUT); //enable echoPin as an INPUT
  pinMode(PIR_PIN, INPUT); //decalre sensor as input

  // Eyes Setup!
  roboEyes.begin();

  // Servo bits
  digitalWrite(SERVO_RELAY, HIGH);
  int initial[]={170,155,90,90,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21}; //initial servo values
  Serial.begin(115200);
  //Serial.println("21 channel Servo test!");

  // Handles our initialization of the 16 channel servo driver board & remaining servos
  initServos();
  setAllJointsInitial(initial);

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
  

//for (uint16_t pulselen = 0; pulselen < 180; pulselen++) {
//    setServoAngle(0, pulselen);
//  }
//  
//  delay(500);
//
//for (uint16_t pulselen = 180; pulselen > 0; pulselen--) {
//    setServoAngle(0, pulselen);
//  }

//code to all the pir and ultrasonic sensor
//float in, c;
//in = ultrasonic_in(PING_PIN, ECHO_PIN);
//Serial.print(in);
//Serial.print("in, ");
//pir(PIR_PIN);

// Turn on servo motor power?
digitalWrite(SERVO_RELAY, HIGH);

// Check for any serial communications
//checkForCom();
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
    //servoCom();
    setAllJoints1();
    setAllJoints2();
    //setJointAngle(LeftChest, 0);
    newJoints = false;
  }
  newData = false;
}

delay(100);

//  while (Serial.available()) {
//    char c = Serial.read();  //gets one byte from serial buffer
//    readString += c; //makes the string readString
//    delay(2);  //slow looping to allow buffer to fill with next character
//  }
//
//  if (readString.length() >0) {
//    Serial.println(readString);  //so you can see the captured string 
//    int n = readString.toInt();  //convert readString into a number
//  
//      Serial.print("writing Angle: ");
//      Serial.println(n);
//      setServoAngle(0, n);
//    
//
//    readString=""; //empty for next input
//  }
  
}
