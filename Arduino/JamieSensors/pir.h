//#include "globalVariables.h"

// We have some number of PIRs with states to track
// Right PIR
int motionStatusR = 0; // Current PIR status 1 = motion detected 0 = motion ended
int pirStateR = LOW; //start assuming no motion

// Left PIR
int motionStatusL = 0; // Current PIR status 1 = motion detected 0 = motion ended
int pirStateL = LOW; //start assuming no motion

// Middle PIR
int motionStatusM = 0; // Current PIR status 1 = motion detected 0 = motion ended
int pirStateM = LOW; //start assuming no motion


// Read our PIR sensor and update the pir state and current motion state
int pir(int pirPin, int &pirState, int &motionStatus){

  int val = digitalRead(pirPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    // only make updates if the value has changed, basically
    if (pirState == LOW) {
      // we have just turned on
      motionStatus = 1; //motion detected
      // We only want to print on the output change, not state
      pirState = HIGH;
      #if defined(DEBUG) && DEBUG 
        Serial.println("PIR state changed to HIGH");
      #endif
    }
  } else {
    // only make updates if the value has changed, basically
    if (pirState == HIGH){
      // we have just turned off
      motionStatus = 0; //motion ended
      // We only want to print on the output change, not state
      pirState = LOW;
      #if defined(DEBUG) && DEBUG 
        Serial.println("PIR state changed to LOW");
      #endif
    }
  }
  return motionStatus;
}

// Update all PIRs
void readAllPIRs(){
  // Right PIR
  #if defined(DEBUG) && DEBUG 
    Serial.println("Check Right PIR");
  #endif
  pir(PIR_PINR, pirStateR, motionStatusR);
  // Left PIR
  #if defined(DEBUG) && DEBUG 
    Serial.println("Check Left PIR");
  #endif
  pir(PIR_PINL, pirStateL, motionStatusL);
  // Middle PIR
//  #if defined(DEBUG) && DEBUG 
//    Serial.println("Check Middle PIR");
//  #endif
//  pir(PIR_PINM, pirStateM, motionStatusM);
}
