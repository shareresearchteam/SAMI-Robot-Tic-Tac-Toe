// Trigger Pin of Ultrasonic Sensor
#define TRIG_PIN 7
// Echo Pin of Ultrasonic Sensor
#define ECHO_PIN 8

#define BUZZER_PIN 5

//PIR sensor input pin
#define PIR_PIN  10
#define PIR_PINR  11
#define PIR_PINL  12

//Push button input pin
#define PUSHB_1 4
#define PUSHB_2 3

#define NUM_READINGS 15  // Number of readings to average.
#define THRESHOLD    50   // Deviation threshold from the average (in centimeters).


// Constants
const unsigned int MAX_DIST = 23200;
const unsigned long ALARM_DURATION_MS = 1000;
const unsigned long DETECTION_PERIOD_MS = 5000; // 5 seconds
const unsigned long ULTRASONIC_INTERVAL_MS = 100; // Interval between ultrasonic measurements
