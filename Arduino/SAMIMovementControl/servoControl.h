/*************************************************** 
This contains all the functions and controls for our servo motors for the brain, using HiWonder BusServos (the HTS-35H and HTS-20H lines)
The lower level serial command handling written by HiWonder is in SerialServo.h
 ****************************************************/
#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H
#include "SerialServo.h"


class servoControl {
  private:
    HardwareSerial& _serialX;

   public:
    servoControl(HardwareSerial& port) : _serialX(port) { }
    void begin() {
      _serialX.begin(115200);
    }
    /*
   Move the servo with:
    - servo ID: jointID
    - goal position as angle, mapped from 0-240 degrees to 0-1000... clicks?
    - set with goal time in milliseconds (currently 1 second)
  */
  void setJointAngle(uint8_t jointID, uint8_t angle) {
    LobotSerialServoMove(_serialX, jointID, map(angle,0,240,0,1000), jointTime*1000);
  }
  
  // Get the temperature of a specified joint
  int getJointTemp(int jointID) {
    return LobotSerialServoReadTemp(_serialX, jointID);
  }
  
  void setFromJointMsg() {
    if(numJointsRecv > 0 && numJointsRecv < 255) {
      for (int i = 0; i < numJointsRecv; i++) {
        setJointAngle(jointIDs[i], jointAngles[i]);
      }
    }
  }
};




#endif
