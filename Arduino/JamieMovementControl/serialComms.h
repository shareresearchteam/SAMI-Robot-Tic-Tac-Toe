#include "constants.h"
/*
 * Serial comms for recieving messages from the PC!
 * Message structure follows byte pattern:
 * Start msg byte - msg type byte - msg info bytes - Stop msg byte
 * Where start msg byte is < and stop msg byte is > and msg type is defined as below
 * 
 * EMOTE Message:
 * An emote message is E, followed by the id for the emote they want to display, as ordered by the NeoEyes library
 * So neutral expression would be 4 bytes and look like: <E0>
 * 
 * JOINT Message:
 * A joint message is J, followed by the time it should take for the joints to reach the requested position (in seconds)
 * followed then by a list of paired bytes that denote the joint servo id, and the angle
 * So, a message telling two servos, with ids 1 and 5 to go to 90 degrees in 2 seconds would be 8 bytes and look like:
 *   <J2190590>
 * 
 */

const byte numChars = 33;
char receivedChars[numChars]; // an array to store the received data
// Our type of message with data
char msgType = 'N';
char noMsg = 'N';
char emoteMsg = 'E';
char jointMsg = 'J';

int currentEmote = 0;
bool newEmote = false;

// We have two header boards, so max 32 joint pins.
// joint IDs 0-15 will go to board 1, 16-31 go to board 2
int jointIDs[NumPins] = {0};
int jointAngles[NumPins] = {0};
int numJointsRecv = -1;
int jointTime = 1; // this is sent in seconds, we default to one second
bool getJointTime = false;
bool getJointID = false; // basically, should we be getting a joint ID next?
bool newJoints = false;

boolean newData = false;

// Helper function just to separate out the joint pin/angle read logic
void getNewJointData(char newByte) {
  // If we haven't gotten a time to drive the joints, lets get that first!
  if (getJointTime) {
    jointTime = newByte;
    // Reset these once we have our joint time so we can get our joint angle info
    numJointsRecv = -1;
    getJointID = true;
    getJointTime = false;
  }
  // If we're looking for a new joint ID, and we still have more joint pins available...
  else if (getJointID && numJointsRecv < 31) {
    // Increment the number of joints we've recieved
    numJointsRecv++;
    // Add the recieved byte to the jointIDs array
    jointIDs[numJointsRecv] = newByte;
    // Flag that we aren't looking for a new joint ID (aka, looking for a new angle)
    getJointID = false;
  }
  // Otherwise, if we're not looking for a joint ID, and we're on any of the actual joint pins available
  else if (!getJointID && numJointsRecv <= 31) {
    // Then add the byte as an angle for our currently recieving joint
    jointAngles[numJointsRecv] = newByte;
    // And flag that the next byte should be a joint ID
    getJointID = true;
  }
}

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

    // If we have already recieved a start byte
    // then we're actively recieving new data as it's available
    if (recvInProgress == true) {
      // If we haven't yet recieved the end marker
      if (rc != endMarker) {
        // If our index is zero, meaning this is the first byte we've read
        // after the start byte, then set the value as our msg type
        if (ndx == 0) {
          msgType = rc;
          if (msgType == jointMsg) {
            // let's get the time to drive the joints first
            getJointTime = true;
          }
          ndx++;
        }
        // Or, if we were told our msg type is an expression, then set our current expression to the new byte
        else if(msgType == emoteMsg && ndx == 1) {
          currentEmote = rc; // convert char to int
          ndx++;
        }
        // Or if our msg is a joint msg, and we aren't out of joint pins, then set new joint ids and angles
        else if(msgType == jointMsg && ndx <= 32){
          getNewJointData(rc);
          ndx++;
        }
        // Otherwise it's just kinda w/e
        else {
          receivedChars[ndx] = rc;
          ndx++;
        }
        // Make sure we don't overflow the buffer
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      // If we did get the end message byte command
      else {
        // close out our reviewed chars buffer
        receivedChars[ndx] = '\0'; // terminate the string
        // No longer recieving data
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
