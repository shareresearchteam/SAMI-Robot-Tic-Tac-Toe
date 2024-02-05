#include "constants.h"
/*
 * All Serial Communication Functions
 */
// Initialize the global jointAngles array
int jointAngles[TorsoTilt+1] = {0};

//Serial Communication for servo bytes message starts with 0xFF and ends with 0xFE
void servoCom() {
  if (Serial.available() > 0) {
    // Check for the start byte
    if (Serial.read() == 0xFF) {
      delay(50);  // Wait a bit for all bytes to arrive this was needed for it to work
      //int angles[20];
      int byteCount = 0;
      bool endByteReceived = false;

      // Read up to 5 bytes (angles) before end byte
    while (Serial.available() > 0 && byteCount <= TorsoTilt + 1) { // Ensure we do not overflow the jointAngles array
        int byteRead = Serial.read();

        // Check if the end byte is received
        if (byteRead == 0xFE) {
          endByteReceived = true;
          break;
        }

        jointAngles[byteCount] = byteRead;
        byteCount++;
      }

      // If 5 bytes received and end byte found
      if (endByteReceived) {
        Serial.print("Angles received: ");
        for (int i = 0; i < TorsoTilt+1; i++) { // Use enum for indexing
          Serial.print(jointAngles[i]);
          Serial.print(" ");
        }
        Serial.println();
      } else {
        Serial.println("Incomplete or incorrect packet");
      }
    }
  }
}
