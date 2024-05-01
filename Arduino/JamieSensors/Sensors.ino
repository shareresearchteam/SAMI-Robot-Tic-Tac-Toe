/*
 * Contains Functions for Sensors
 */

float readings[NUM_READINGS];      // Array to store the distance readings.
int readIndex = 0;               // Index of the current reading.
float total = 0;                 // Running total of the readings.

int pirState = LOW; //start assuming no motion

int val = 0; //variable for reading the pin status

double accumulator = 0.0; //variable for accumaltor of the ultrasonic

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

  val = digitalRead(x); //read input value
  //Serial.print("PIR Sensor Value: ");
  //Serial.print(val); //print value of the DI
  if (val == HIGH){ //check if the input is HIGH
    if (pirState == LOW){
      //we have just turned on
      //Serial.println("Motion Detected!");
      //Only printing on the output change, not the state
      pirState = HIGH;
      return 1; // Motion detected
  }
  } else{
    if (pirState == HIGH){
      //we have just turned off
      //Serial.println("Motion Ended!");
      //Only printing on the output chage not the state
      pirState = LOW;
      return 0; // Motion ended
    }
    return -1; // No change in state
  }
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
