#include "globalVariables.h"
#include "Communication.h"
#include "ultrasonic.h"
#include "pir.h"
#include "button.h"

int buttonStateY = 0; //variable for reading pushbutton
int buttonStateN = 0; //variable for reading pushbutton
float average = 0;               // The average of the readings.
bool filled = false;             // Flag to check if readings array is initially filled.

////middle PIR
//int motion =0; //1 = motion detected; 0 = motion ended
//int motionStatus = 0; // Current PIR status 1 = motion detected 0 = motion ended
//int val = 0; //variable for reading the pin status
//int pirState = LOW; //start assuming no motion
//
////Right PIR
//int motionR =0; //1 = motion detected; 0 = motion ended
//int motionStatusR = 0; // Current PIR status 1 = motion detected 0 = motion ended
//int valR = 0; //variable for reading the pin status
//int pirStateR = LOW; //start assuming no motion
//
////Left PIR
//int motionL =0; //1 = motion detected; 0 = motion ended
//int motionStatusL = 0; // Current PIR status 1 = motion detected 0 = motion ended
//int valL = 0; //variable for reading the pin status
//int pirStateL = LOW; //start assuming no motion

//General detection variables
bool detected = false; //detection from eiher Left or Right PIR
bool center = false; //detection from both Left and Right PIR

unsigned long last_ultrasonic_check_ms = 0;
bool object_detected = false;
bool object_gone = false;

bool PERSON_PRESENT = false; //Global Person is Present

void setup() {
  // Ultrasonic setup
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  //pinMode(PIR_PIN, INPUT); // Declare sensor as input
  pinMode(PIR_PINR, INPUT); // Declare sensor as input Right PIR
  pinMode(PIR_PINL, INPUT); // Declare sensor as input Left PIR

  initBtns();
//  pinMode(PUSHB_1, INPUT); // Initialize pushbutton 1
//  pinMode(PUSHB_2, INPUT); // Initialize pushbutton 2

  //initializeReadings();
  Serial.begin(115200);
  // Then start our first ultrasonic ping
  attachInterrupt(digitalPinToInterrupt(ECHO_PIN),
                  echoPinInterrupt,
                  CHANGE);
  startUltrasonicPing();
  
  // Stabilization delay
  #if defined(DEBUG) && DEBUG 
    Serial.println("Stabilizing sensor...");
  #endif
  delay(3000);  // 3 seconds stabilization time
  #if defined(DEBUG) && DEBUG 
    Serial.println("Sensor stabilized.");
  #endif

  
}

void loop() {
  unsigned long current_time = millis();

  // Check if we have a new reading from our ultrasonic sensor, and check if our distance has changed
  checkUltrasonic();

  // Update all our PIR sensors
  readAllPIRs();

  // If we detect motion from left or right, and have nothing detected in the center...
  if ((motionStatusL || motionStatusR) && !detected && !center) {
    // Then we have detected a person passing
    detected = true;
    // and we need to send a message that we detected something
    sendPirData(1);
  }
  // If something has gotten closer, and we are not centered
  else if (distanceChange == 1 && !center) {
    // Then something has come up in the front
    detected = true;
    center = true;
    sendPirData(1);
    // reset this since we've acknowledged there was a change
    distanceChange = 0;
  }
  else if ((motionStatusL || motionStatusR) && distanceChange == 2 && detected && center) {
    // Ahhh??? Maybe a person is leaving? Still detected but leaving
    center = false;
    distanceChange = 0;
  }
  else if (!motionStatusL && !motionStatusR && distanceChange == 0 && !center && detected) {
    // then probably they've left
    detected = false;
    sendPirData(0);
  }


  // Original motion detect code

   // Only check PIR sensor if no object is detected by the ultrasonic sensor
//    // PIR Sensor
//    pir(PIR_PIN);
//    // PIR Sensor Right
//    pirR(PIR_PINR);
//    // PIR Sensor Left
//    pirL(PIR_PINL);

//// If motion detected by either sensor, no previous detection, and not centered
//if ((motionStatusL || motionStatusR || motionStatus) && !detected && !center) {
//    sendPirData(1);
//    //Serial.print("Time: ");
//    //Serial.print(current_time);
//    Serial.println(" ms - Person DETECTED!");
//    detected = true; // Set detected to true
//    center = false;  // Ensure center is false
//} 
//// If motion detected by both sensors, previously detected, but not centered
//else if (((motionStatusL && motionStatusR && motionStatus)|| (motionStatusL && motionStatus)|| (motionStatusR && motionStatus) ||(motionStatusL && motionStatusR)) && detected && !center) {
//    //Serial.print("Time: ");
//    //Serial.print(current_time);
//    Serial.println(" ms - Person has ENTERED the CENTER");
//    sendPirDataM(1); //send 1 when entering center
//    detected = true; // Ensure detected remains true
//    center = true;   // Set center to true
//} 
//// If motion detected by only one sensor, previously detected and centered
//else if (((motionStatusL && !motionStatusR && !motionStatus) || (!motionStatusL && motionStatusR && !motionStatus)|| (!motionStatusL && !motionStatusR && motionStatus)) && detected && center) {
//    //Serial.print("Time: ");
//    //Serial.print(current_time);
//    sendPirDataM(0); //send 0 when entering center
//    Serial.println(" ms - Person is LEAVING the CENTER");
//    detected = true; // Ensure detected remains true
//    center = false;  // Set center to false
//} 
//// If no motion detected by both sensors, previously detected but not centered
//else if (!motionStatusL && !motionStatusR && !motionStatus && detected && !center) {
//    sendPirData(0);
//    //Serial.print("Time: ");
//    //Serial.print(current_time);
//    Serial.println(" ms - Person has fully LEFT");
//    detected = false; // Set detected to false
//    center = false;   // Ensure center remains false
//}

  // function checks the state of all buttons and sends any button messages if a button has been pressed
  checkBtns();
    
//  //read the state of the pushbutton value:
//  buttonStateY = pushButton1(PUSHB_1);
//// //send the message only if the button has been pressed
// if (buttonStateY == 1){
//  sendPushButtonData(0);
// }
////  //read the state of the pushbutton value:
//  buttonStateN = pushButton2(PUSHB_2);
//
////send the message only if the button has been pressed
//  if (buttonStateN == 1){
//  sendPushButtonData(1);
// }  
delay(1000);
}
