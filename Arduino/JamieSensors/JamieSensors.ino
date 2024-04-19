#include "Sensors.h"
#include "globalVariables.h"
#include "Communication.h"

void setup() {
  pinMode(PING_PIN, OUTPUT); //enable pingPing as an OUTPUT
  pinMode(ECHO_PIN, INPUT); //enable echoPin as an INPUT
  pinMode(PIR_PIN, INPUT); //decalre sensor as input

  Serial.begin(115200);
}

void loop() {
   // Read and send ultrasonic sensor data
  float distance = ultrasonic_cm(PING_PIN, ECHO_PIN);
  sendUltrasonicData(distance);

  // Read and send PIR sensor data
  int motionDetected = pir(PIR_PIN);
  sendPirData(motionDetected);

  // Delay a little to not spam
  delay(200);

}
