// Define start and end markers
const char startMarker = '<';
const char endMarker = '>';

char ultraMsg = 'U';
char pirMsg = 'P';
char pbMsg1 = 'Y';//YES push button
char pbMsg2 ='N';//NO push button

void sendUltrasonicData(float distance) {
  Serial.print(startMarker);
  Serial.print(ultraMsg); // Message type for Ultrasonic
  Serial.print(distance);
  Serial.println(endMarker);
}

void sendPirData(int motionStatus) {
  if (motionStatus != -1) { // Only send data on state change
    Serial.print(startMarker);
    Serial.print(pirMsg); // Message type for PIR
    Serial.print(motionStatus);
    Serial.println(endMarker);
  }
}

void sendPushButtonData1(int buttonState1) {
    Serial.print(startMarker);
    Serial.print(pbMsg1); // Message type for push button 1
    Serial.print(buttonState1);
    Serial.println(endMarker);
  }

void sendPushButtonData2(int buttonState2) {
    Serial.print(startMarker);
    Serial.print(pbMsg2); // Message type for push button 2
    Serial.print(buttonState2);
    Serial.println(endMarker);
  }
  
