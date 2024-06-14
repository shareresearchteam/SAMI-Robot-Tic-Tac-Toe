#include "globalVariables.h"
#include "Communication.h"

int buttonStateY = 0; //variable for reading pushbutton
int buttonStateN = 0; //variable for reading pushbutton
float average = 0;               // The average of the readings.
bool filled = false;             // Flag to check if readings array is initially filled.

int motion =0; //1 = motion detected; 0 = motion ended
int motionStatus = 0; // Current PIR status 1 = motion detected 0 = motion ended
int val = 0; //variable for reading the pin status
int pirState = LOW; //start assuming no motion

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
  // Read and send PIR sensor data
  pir(PIR_PIN);

  //read the state of the pushbutton value:
  buttonStateY = pushButton1(PUSHB_1);

// //send the message only if the button has been pressed
 if (buttonStateY == 1){
  sendPushButtonData1(buttonStateY);
 }
//  //read the state of the pushbutton value:
  buttonStateN = pushButton2(PUSHB_2);

//send the message only if the button has been pressed
  if (buttonStateN == 1){
  sendPushButtonData2(buttonStateN);
 }  
  // Delay 
  //delay(200);

}
