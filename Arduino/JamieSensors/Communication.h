// Define start and end markers
const char startMarker = '<';
const char endMarker = '>';

char ultraMsg = 'U';
char pirMsg = 'P';
char btnMsg = 'B';
char pbMsg1 = 'Y';//YES push button
char pbMsg2 ='N';//NO push button

void sendUltrasonicData(float distance) {
  Serial.print(startMarker);
  Serial.print(ultraMsg); // Message type for Ultrasonic
  Serial.print(distance);
  Serial.write(endMarker);
}

void sendPirData(int motionStatus) {
  if (motionStatus != -1) { // Only send data on state change
    Serial.write(startMarker);
    Serial.write(pirMsg); // Message type for PIR
    Serial.write(motionStatus);
    Serial.println(endMarker);
  }
}

void sendPushButtonData(int buttonNum) {
    Serial.write(startMarker);
    Serial.write(btnMsg); // Message type for push button 1
    Serial.write(buttonNum);
    Serial.println(endMarker);
  }

void sendPushButtonData2(int buttonState2) {
    Serial.write(startMarker);
    Serial.write(pbMsg2); // Message type for push button 2
    Serial.write(buttonState2);
    Serial.println(endMarker);
  }
  
