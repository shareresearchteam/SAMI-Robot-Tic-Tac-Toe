#include "include.h"
#include "SerialServo.h"

// Change this to the ID value you want on the servo, and run the code.
int newID = 3;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(1000);
}

void loop() {
  LobotSerialServoSetID(Serial1, ID_ALL, newID);
  delay(500);
  int id = LobotSerialServoReadID(Serial1);
  Serial.println("");
  Serial.print("new ID:");
  Serial.println(id);
  delay(1000);
}
