/*
 * Contains Functions for Sensors
 */
float readings[NUM_READINGS];      // Array to store the distance readings.
int readIndex = 0;               // Index of the current reading.
float total = 0;                 // Running total of the readings.

//int pirState = LOW; //start assuming no motion
//int motionStatus = 0; // Current PIR status 1 = motion detected 0 = motion ended

//int val = 0; //variable for reading the pin status

double accumulator = 0.0; //variable for accumaltor of the ultrasonic

//Push Button Variables
int buttonState1;            // the current reading from the input pin
int lastButtonState1 = LOW;  // the previous reading from the input pin
int highButtonState1 = LOW; // Vairbale for when the button state is high

int buttonState2;            // the current reading from the input pin
int lastButtonState2 = LOW;  // the previous reading from the input pin
int highButtonState2 = LOW; // Vairbale for when the button state is high

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output

//ultrasonic
unsigned long alarm_triggered_ms = 0;
unsigned long detection_start_ms = 0;
unsigned long object_gone_start_ms = 0;
bool alarm_triggered = false;
bool gone_alarm_triggered = false;

float ultrasonic_in(const int x, const int y){//ultrasonic funtion in returns inches
    float duration;
    
    digitalWrite(x, LOW); //set pingPin volatage to low 0 volts (ground)
    delayMicroseconds(2); //delay
    digitalWrite(x, HIGH); //set pingPin voltage to high 5V 
    delayMicroseconds(10); //delay
    digitalWrite(x, LOW); //set pingPin volatage to low 0 volts (ground)
    duration = pulseIn(y, HIGH); //return duration of pulse and set to duration
    
    return duration / 74 / 2; //use to convert to inches
}

float ultrasonic_cm(const int x, const int y){//ultrasonic funtion in returns centimeters
    float duration;
    
    digitalWrite(x, LOW); //set pingPin volatage to low 0 volts (ground)
    delayMicroseconds(2); //delay
    digitalWrite(x, HIGH); //set pingPin voltage to high 5V 
    delayMicroseconds(10); //delay
    digitalWrite(x, LOW); //set pingPin volatage to low 0 volts (ground)
    duration = pulseIn(y, HIGH); //return duration of pulse and set to duration
    //Sound travels at 343 meters per second, which means it needs 29.155 microseconds per centimeter. So, we have to divide the duration by 29 and then by 2, because the sound has to travel the distance twice. It travels to the object and then back to the sensor.
    return duration / 29 / 2; //use to convert to centimeters
}

int pir(int x){

val = digitalRead(x);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    
    if (pirState == LOW) {
      // we have just turned on
      //Serial.println("Middle Motion detected!");
      motionStatus = 1; //motion detected
      //sendPirData(1);
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    
    if (pirState == HIGH){
      // we have just turned of
      //Serial.println("Middle Motion ended!");
      motionStatus = 0; //motion ended
      //sendPirData(0);
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
  return motionStatus;
}

//Right PIR
int pirR(int x){

valR = digitalRead(x);  // read input value
  if (valR == HIGH) {            // check if the input is HIGH
    
    if (pirStateR == LOW) {
      // we have just turned on
      //Serial.println("Right Motion detected!");
      motionStatusR = 1; //motion detected
      //sendPirDataR(1);
      // We only want to print on the output change, not state
      pirStateR = HIGH;
    }
  } else {
    
    if (pirStateR == HIGH){
      // we have just turned of
      //Serial.println("Right Motion ended!");
      motionStatusR = 0; //motion ended
      //sendPirDataR(0);
      // We only want to print on the output change, not state
      pirStateR = LOW;
    }
  }
  return motionStatusR;
}

//Left PIR
int pirL(int x){

valL = digitalRead(x);  // read input value
  if (valL == HIGH) {            // check if the input is HIGH
    
    if (pirStateL == LOW) {
      // we have just turned on
      //Serial.println("Left Motion detected!");
      motionStatusL = 1; //motion detected
      //sendPirDataL(1);
      // We only want to print on the output change, not state
      pirStateL = HIGH;
    }
  } else {
    
    if (pirStateL == HIGH){
      // we have just turned of
      //Serial.println("Left Motion ended!");
      motionStatusL = 0; //motion ended
      //sendPirDataL(0);
      // We only want to print on the output change, not state
      pirStateL = LOW;
    }
  }
  return motionStatusL;
}

void initializeReadings() {
  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = 0;
  }
}

void sensor_avg(float newReading){

  // Subtract the oldest reading from the total
  total -= readings[readIndex];
  
  // Add the new reading to the array and to the total
  readings[readIndex] = newReading;
  total += readings[readIndex];
  
  // Move to the next index cyclically
  readIndex = (readIndex + 1) % NUM_READINGS;
  
  // Check if the array is filled
  if (readIndex == 0) {
    filled = true;
  }
  
  // Calculate the new average only if the array is filled
  if (filled) {
    average = total / NUM_READINGS;
  }
}


int pushButton1(int x){
  // read the state of the switch into a local variable:
  highButtonState1 = LOW; //Reset High button state variable
  int reading1 = digitalRead(x);

    if (reading1 != buttonState1) {
      buttonState1 = reading1;
      //Serial.println("Change.");
      // only toggle the LED if the new button state is HIGH
      if (buttonState1 == HIGH) {
        highButtonState1 = buttonState1;
      }
    }
    
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState1 = reading1;
  return highButtonState1;
}

int pushButton2(int y){
  // read the state of the switch into a local variable:
  highButtonState2 = LOW; //Reset High button state variable
  int reading2 = digitalRead(y);

    if (reading2 != buttonState2) {
      buttonState2 = reading2;
      //Serial.println("Change.");
      // only toggle the LED if the new button state is HIGH
      if (buttonState2 == HIGH) {
        highButtonState2 = buttonState2;
      }
    }
    
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState2 = reading2;
  return highButtonState2;
}

void checkUltrasonicSensor() {
  unsigned long t1, t2, pulse_width;
  float cm;

//  // Handle alarm if triggered
//  if (millis() - alarm_triggered_ms < ALARM_DURATION_MS && alarm_triggered_ms != 0) {
//    tone(BUZZER_PIN, 330, 1000);
//    //sendUltrasonicData(1);
//  }
//
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Wait for pulse on echo pin and measure duration
  if (!waitForPulse(ECHO_PIN, HIGH, MAX_DIST, t1)) return;
  if (!waitForPulse(ECHO_PIN, LOW, MAX_DIST, t2)) return;

  pulse_width = t2 - t1;
  cm = pulse_width / 58.0;

  if (pulse_width > MAX_DIST) {
    //Serial.println("Out of range");
    return;
  }

  handleDetection(cm);
}

bool waitForPulse(int pin, int state, unsigned long timeout, unsigned long &timestamp) {
  unsigned long start = micros();
  while (digitalRead(pin) != state) {
    if (micros() - start > timeout) {
      //Serial.println("Out of range");
      return false;
    }
  }
  timestamp = micros();
  return true;
}

void handleDetection(float cm) {
  if (cm <= 20) {
    if (!object_detected) {
      object_detected = true;
      detection_start_ms = millis();
      resetFlags();
    } else if (millis() - detection_start_ms >= DETECTION_PERIOD_MS && !alarm_triggered) {
      alarm_triggered_ms = millis();
      alarm_triggered = true;
      PERSON_PRESENT = true;
      sendUltrasonicData(1);
    }
    object_gone_start_ms = 0;
  } else {
    handleObjectGone();
  }
}

void resetFlags() {
  object_gone = false;
  alarm_triggered = false;
  gone_alarm_triggered = false;
}

void handleObjectGone() {
  if (object_detected && !object_gone) {
    object_gone = true;
    object_gone_start_ms = millis();
  } else if (object_gone && !gone_alarm_triggered && millis() - object_gone_start_ms >= DETECTION_PERIOD_MS) {
    alarm_triggered_ms = millis();
    gone_alarm_triggered = true;
    sendUltrasonicData(0);
    object_detected = false;
    PERSON_PRESENT = false;
  }
}
