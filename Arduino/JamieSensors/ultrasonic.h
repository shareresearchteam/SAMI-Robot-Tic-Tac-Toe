//#include "globalVariables.h"
// TODO: timeout checking
// Note: we might want some sort of filtering on this, but for now we're just checking and comparing raw values.
// Use these to track our distance difference
float currentDistance = -1;
float previousDistance = 0;
float distanceThreshold = 10; // If the difference between current and previous is smaller than that, ignore it
// Tracking for if our distance has changed at all
// 0 - no change
// 1 - distance is closer
// 2 - distance is further
unsigned int distanceChange = 0; 
bool objectInRange = false;

// These are for tracking our pulse length using interrupts
volatile unsigned long pulseInTimeBegin = micros();
volatile unsigned long pulseInTimeEnd = micros();
volatile bool newPulseDurationAvailable = false;
unsigned long pulseTrigTime = 0;
unsigned long timeoutTime = 10000; // If we don't return anything within 1ms  of starting a trig call, we want to just try again lol


// This just kicks off the initial trig call for the echo to catch
void startUltrasonicPing() {
  digitalWrite(TRIG_PIN, LOW);  
  delayMicroseconds(2);  
  digitalWrite(TRIG_PIN, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(TRIG_PIN, LOW); 
  // And then save when we last pulsed the trig for sanity
  pulseTrigTime = micros();
}


// We connect this to our interrupt pin so we can track our pulse time in a non-blocking way
void echoPinInterrupt()
{
  if (digitalRead(ECHO_PIN) == HIGH) {
    // start measuring
    pulseInTimeBegin = micros();
  }
  else {
    // stop measuring
    pulseInTimeEnd = micros();
    newPulseDurationAvailable = true;
  }
}

// Then we do the actual distance calculations and any analysis as part of our main loop by checking the ultrasonic
void checkUltrasonic(){
  if (newPulseDurationAvailable) {
    // Reset our availability check
    newPulseDurationAvailable = false;
    // set the current distance to our previous distance value
    previousDistance = currentDistance;
    unsigned long pulseDuration = pulseInTimeEnd - pulseInTimeBegin;
    // calculate our pulse duration as when the pulse in ends minus when it begings. then calculate the new distance and set it to our current distance
    currentDistance = (pulseDuration*.0343)/2; 
      
    // If the currentDistance is measuring ~2180, then that means it's reached end of range and there's nothing there
    // If currentDistance is above ~200 but less than end of range, then there's something there, but it's so far away that it would be unreasonable to interact with it
    // So we only really care if the distance is below ~200
    if (currentDistance <= 200) {
      objectInRange = true;
      #if defined(DEBUG) && DEBUG 
        Serial.print("Something is in range at distance: ");
        Serial.println(currentDistance);
      #endif
      // If the object is in range, let's see if the distance has changed since last time.
      // If we don't have a last time, then the difference will just be current distance, and we'll have to handle the reading
      float distDiff = currentDistance - previousDistance;
      // If the difference between them is greater than the threshold, then it's likely not just noise
      // if distance is greater than the threshold...
      if (distDiff > distanceThreshold) {
        // Then the object is further away
        distanceChange = 2;
        #if defined(DEBUG) && DEBUG 
          Serial.print("Object moved away to: ");
          Serial.println(currentDistance);
        #endif
      }
      // Otherwise if the distance is less than the negative threshold
      else if (distDiff < -distanceThreshold) {
        // Then the object is closer
        distanceChange = 1;
        #if defined(DEBUG) && DEBUG 
          Serial.print("Object moved closer to: ");
          Serial.println(currentDistance);
        #endif
      }
      // We don't modify the distanceChange value if there is no change, because a non-zero value indicates a new value
      // So it gets reset to zero by elsewhere in the code
    }
    else {
      if (objectInRange) {
        // If we were previously in range, then we've moved out of range, so we moved further away,
        // but once we're out of range we stop caring
        distanceChange = 2;
      }
      // If our current distance is beyond the 200 range, then it's too far away and we do not care
      objectInRange = false;
    }
    
    // Then we go ahead and start a new sensor reading
    startUltrasonicPing();
  }
  else {
    #if defined(DEBUG) && DEBUG 
        Serial.println("Data not ready");
      #endif
    unsigned long currTime = micros();
    if(abs(currTime - pulseTrigTime) > timeoutTime) {
      // If we've reached beyond the timeout time since we first sent a ping out or micros has rolled over and gone beyond the timeout time...
      // then the signal is lost and we should just send a new ping
      // Should we say we're infinitely far if that happens? idk, for the moment we wont
      #if defined(DEBUG) && DEBUG 
        Serial.println("Echo ping not recieved");
      #endif
      startUltrasonicPing();
    }
  }
}
