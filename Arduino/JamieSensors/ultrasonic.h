//#include "globalVariables.h"
// TODO: timeout checking
// Note: we might want some sort of filtering on this, but for now we're just checking and comparing raw values.
// Use these to track our distance difference
float currentDistance = -1;
float previousDistance = -1;
float distanceThreshold = 10; // If the difference between current and previous is smaller than that, ignore it
// Tracking for if our distance has changed at all
// 0 - no change
// 1 - distance is closer
// 2 - distance is further
unsigned int distanceChange = 0; 


// These are for tracking our pulse length using interrupts
volatile unsigned long pulseInTimeBegin = micros();
volatile unsigned long pulseInTimeEnd = micros();
volatile bool newPulseDurationAvailable = false;
unsigned long pulseTrigTime = micros();
unsigned long timeoutTime = 10000000; // If we don't return anything within 10 seconds of starting a trig call, we want to just try again lol


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
    // Calculate our pulse duration
    unsigned long pulseDuration = pulseInTimeEnd - pulseInTimeBegin;
    // then calculate the new distance and set it to our current distance
    currentDistance = (pulseDuration*.0343)/2; 
    #if defined(DEBUG) && DEBUG 
      Serial.print("New Distance: ");
      Serial.println(currentDistance);
    #endif
    
    // If we have a real current and a real previous distance, then let's check the difference!
    if (previousDistance != -1) {
      float distDiff = currentDistance - previousDistance;
      // If the difference between them is greater than the threshold, then we care! 
      if( abs(distDiff) > distanceThreshold) {
        // If the distance is further away...
        if (distDiff > 0) {
          distanceChange = 2;
          #if defined(DEBUG) && DEBUG 
            Serial.println("Distance is further");
          #endif
        }
        // Otherwise if the distance is closer
        else {
          distanceChange = 1;
          #if defined(DEBUG) && DEBUG 
            Serial.println("Distance is closer");
          #endif
        }
      }
      // We don't modify the distanceChange value if there is no change, because a non-zero value indicates a new value
      // So it gets reset to zero by elsewhere in the code
    }
    
    // Then we go ahead and start a new sensor reading
    startUltrasonicPing();
  }
  else if((micros() - pulseTrigTime > timeoutTime) || ( micros() < pulseTrigTime && micros() > timeoutTime)) {
    // If we've reached beyond the timeout time since we first sent a ping out or micros has rolled over and gone beyond the timeout time...
    // then the signal is lost and we should just send a new ping
    // Should we say we're infinitely far if that happens? idk, for the moment we wont
    startUltrasonicPing();
  }
}
