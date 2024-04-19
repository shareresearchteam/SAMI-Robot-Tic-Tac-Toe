// Define start and end markers
const char startMarker = '<';
const char endMarker = '>';

char ultraMsg = 'U';
char pirMsg = 'P';

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
