/*************************************************** 
This contains all the functions and controls for our servo motors for the brain, using HiWonder BusServos (the HTS-35H and HTS-20H lines)
The lower level serial command handling written by HiWonder is in SerialServo.h
 ****************************************************/
#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H
#include "SerialServo.h"
#include "constants.h"

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
  void setJointAngle(int jointID, int angle) {
    LobotSerialServoMove(_serialX, jointID, map(angle,0,240,0,1000), jointTime*1000);
  }
  
  // Get the temperature of a specified joint
  int getJointTemp(int jointID) {
    return LobotSerialServoReadTemp(_serialX, jointID);
  }
  
  void setFromJointMsg() {
    if(numJointsRecv > -1 && numJointsRecv < 254) {
      for (int i = 0; i <= numJointsRecv; i++) {
        setJointAngle(jointIDs[i], jointAngles[i]);
      }
    }
  }
};


// Turn on/off power to all the servos at once
void setServoRelays(bool isOn) {
  digitalWrite(SERVO_RELAY1, isOn);
  digitalWrite(SERVO_RELAY2, isOn);
  digitalWrite(SERVO_RELAY3, isOn);
  digitalWrite(SERVO_RELAY4, isOn);
  digitalWrite(SERVO_RELAY5, isOn);
  digitalWrite(SERVO_RELAY6, isOn);
}


#endif
