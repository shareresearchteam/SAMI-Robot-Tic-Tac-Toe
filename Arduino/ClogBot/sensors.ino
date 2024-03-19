/*
 * Contains Functions for Sensors
 */

int pirState = LOW; //start assuming no motion

int val = 0; //variable for reading the pin status

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

void pir(int x){

  val = digitalRead(x); //read input value
  Serial.print("PIR Sensor Value: ");
  Serial.print(val); //print value of the DI
  if (val == HIGH){ //check if the input is HIGH
    if (pirState == LOW){
      //we have just turned on
      Serial.println("Motion Detected!");
      //Only printing on the output change, not the state
      pirState = HIGH;
  }
  } else{
    if (pirState == HIGH){
      //we have just turned off
      Serial.println("Motion Ended!");
      //Only printing on the output chage not the state
      pirState = LOW;
    }
  }
}
