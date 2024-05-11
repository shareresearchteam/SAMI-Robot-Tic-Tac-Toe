/*************************************************** 
This contains all the functions and controls for our servo motors for the brain.
Initial pieces and instructions here are based off the Adafruit servo test example.
Original description follows:

  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution


 ****************************************************/
#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "constants.h"

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
// you can also call it with a different address you want
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

void initServos () {
  pwm1.begin();
  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */
  pwm1.setOscillatorFrequency(27000000);
  pwm1.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  pwm2.begin();
  pwm2.setOscillatorFrequency(27000000);
  pwm2.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  // Setup
}

int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  //analog_value = int(float(pulse_wide) / 1000000  SERVO_FREQ  4096);
  analog_value = static_cast<int>(static_cast<float>(pulse_wide) / 1000000 * SERVO_FREQ * 4096);
  return analog_value;
}

void setServoAngle(uint8_t n, int angle) {
  int pulse;
  pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm1.setPWM(n, 0, pulse);
}

//set joint angles for servos 1-16
void setJointAngle1(joints joint, int angle) {
  int pulse;
  pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm1.setPWM(joint, 0, pulse);
}

//set joint angles for servos 17-32
void setJointAngle2(joints joint, int angle) {
  int pulse;
  pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm2.setPWM(joint, 0, pulse);
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  //Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  //Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  //Serial.println(pulse);
  pwm1.setPWM(n, 0, pulse);
}

void setAllJointsInitial(int jointAnglesInitial[]){
  for (int joint = RightGripper; joint < LeftElbow+1; joint++) {
    setJointAngle1(static_cast<joints>(joint), jointAnglesInitial[joint]);
  }
}
// Function to set all joints from 1-16 servos to their corresponding angles
void setAllJoints1() {
  for (int joint = HeadNod; joint < TorsoTilt+1; joint++) {
    setJointAngle1(static_cast<joints>(joint), jointAngles[joint]);
    //Serial.print("Angles sent to servos: ");
    //Serial.print(jointAngles[joint]);
    //Serial.print(" ");
  }
}

// Function to set all joints from 17-32 servos to their corresponding angles
void setAllJoints2() {
  for (int joint = RightGripper; joint < LeftElbow+1; joint++) {
    setJointAngle1(static_cast<joints>(joint), jointAngles[joint]);
  }
}


#endif
