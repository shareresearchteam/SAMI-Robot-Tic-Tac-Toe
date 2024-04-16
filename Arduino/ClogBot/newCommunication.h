#include "constants.h"
const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data
// Our type of message with data
char msgType = 'N';
char noMsg = 'N';
char emoteMsg = 'E';
char jointMsg = 'J';

int currentEmote = 0;
bool newEmote = false;

int jointAngles[NumJoints+1] = {0};
bool newJoints = false;

boolean newData = false;

// a lot of the base stuff here is shamelessly taken from:
// https://forum.arduino.cc/t/serial-input-basics/278284/2

// When we have start and end markers!
void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;
  while(Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        if (ndx == 0) {
          msgType = rc;
          ndx++;
        }
        else if(msgType == emoteMsg) {
          currentEmote = rc; // convert char to int
        }
        else if(msgType == jointMsg && ndx <= NumJoints + 1){
          jointAngles[ndx-1] = rc; // convert char to int
          ndx++;
        }
        else {
          receivedChars[ndx] = rc;
          ndx++;
        }
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
        
        if (msgType == emoteMsg) {
          newEmote = true;
          
        }
        if (msgType == jointMsg) {
          newJoints = true;
        }
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
      ndx = 0;
    }
  }
}

void recvWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}
