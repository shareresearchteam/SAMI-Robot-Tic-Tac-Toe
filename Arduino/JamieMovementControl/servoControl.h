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


// Turn on/off power to all the servos at once
void setServoRelays(bool isOn) {
  digitalWrite(SERVO_RELAY1, isOn);
  digitalWrite(SERVO_RELAY2, isOn);
  digitalWrite(SERVO_RELAY3, isOn);
  digitalWrite(SERVO_RELAY4, isOn);
  digitalWrite(SERVO_RELAY5, isOn);
  digitalWrite(SERVO_RELAY6, isOn);
}

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

void setJointAngle(uint8_t jointNum, int angle) {
  if(jointNum > NumPins) { return; } // We only have two driver boards, so we can't have more than 32 joint pins
  int pulse;
  pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  if(jointNum > 15) {
    pwm2.setPWM(jointNum-16, 0, pulse);
    // then exit the function
    return;
  }
  pwm1.setPWM(jointNum, 0, pulse);
}

void setFromJointMsg() {
  if(numJointsRecv > -1 && numJointsRecv < NumPins) {
    for (int i = 0; i <= numJointsRecv; i++) {
      setJointAngle(jointIDs[i], jointAngles[i]);
    }
  }
}

#endif
