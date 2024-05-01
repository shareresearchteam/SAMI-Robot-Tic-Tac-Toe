#include "globalVariables.h"
#include "Communication.h"

int buttonState1 = 0; //variable for reading pushbutton
int buttonState2 = 0; //variable for reading pushbutton
float average = 0;               // The average of the readings.
bool filled = false;             // Flag to check if readings array is initially filled.

void setup() {
  pinMode(PING_PIN, OUTPUT); //enable pingPing as an OUTPUT
  pinMode(ECHO_PIN, INPUT); //enable echoPin as an INPUT
  pinMode(PIR_PIN, INPUT); //decalre sensor as input
  pinMode(PUSHB_1, INPUT); //initialize pushbutton 1
  pinMode(PUSHB_2, INPUT); //initialize pushbutton 2

  initializeReadings();
  
  Serial.begin(115200);
}

void loop() {
   // Read and send ultrasonic sensor data
  float newDistance = ultrasonic_cm(PING_PIN, ECHO_PIN);

  // Serial.print("Current reading: ");
   //Serial.print(newDistance);
  // Serial.println(" cm");
      
  if (newDistance>0){

    sensor_avg(newDistance);

    if (filled && abs(newDistance - average) >= THRESHOLD){
      Serial.print("Significant reading: ");
      Serial.print(newDistance);
      Serial.println(" cm");
     // sendUltrasonicData(newDistance);
      
    }
   // Serial.print("Current Average: ");
   // Serial.print(average);
   // Serial.println(" cm");
  }

  // Read and send PIR sensor data
  int motionDetected = pir(PIR_PIN);
 // sendPirData(motionDetected);

  //read the state of the pushbutton value:
  buttonState1 = digitalRead(PUSHB_1);
 // sendPushButtonData1(buttonState1);

  //read the state of the pushbutton value:
  buttonState2 = digitalRead(PUSHB_2);
 // sendPushButtonData2(buttonState2);
  
  // Delay 
  delay(200);

}
