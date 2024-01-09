# Aaron Robot Hardware
All of the hardware information for the Aaron robot.

## Bill of Materials

### Mechanical Bill of Materials
The mechanical BoM includes all of the 3D printed parts, and associated screw pieces:

|Part                      |Quantity|Notes                                                                  |Head Twist|Head Nod|Head Tilt|Torso Tilt|Torso Bow|Chest Shoulder|Shoulder|Arm Twist|Elbow|Gripper|Hip|Knee|Ankle|
|--------------------------|--------|-----------------------------------------------------------------------|----------|--------|---------|----------|---------|--------------|--------|---------|-----|-------|---|----|-----|
|M3x14                     |20      |                                                                       |4         |        |         |4         |4        |4             |        |         |     |       |   |    |     |
|M3x16 countersunk         |12      |                                                                       |          |        |         |          |         |              |        |         |2    |       |   |2   |2    |
|M3x16                     |4       |                                                                       |          |        |         |          |         |              |        |         |     |       |2  |    |     |
|M3x30                     |4       |                                                                       |          |        |         |          |         |              |        |2        |     |       |   |    |     |
|M3x35                     |4       |                                                                       |          |        |         |          |         |              |2       |         |     |       |   |    |     |
|M3x40                     |4       |                                                                       |          |        |         |          |         |              |        |2        |     |       |   |    |     |
|M3 hex nut                |32      |                                                                       |          |        |         |          |         |4             |2       |2        |2    |       |2  |2   |2    |
|M3 square nut             |16      |Fits the 2.6mm x 5.5mm x 5.5mm square nuts                             |4         |        |         |4         |4        |              |        |2        |     |       |   |    |     |
|M2x8 self-tapping pan head|8       |could probably use them for all of the motor horns if you really wanted|          |4       |         |          |         |              |        |
|M1.6x8                    |60      |motor horn                                                             |4         |        |         |4         |4        |4             |4       |         |4    |       |4  |4   |4    |
|M1.6 hex nut              |60      |motor horn                                                             |4         |        |         |4         |4        |4             |4       |         |4    |       |4  |4   |4    |
|M1.6 flat washer          |60      |motor horn                                                             |4         |        |         |4         |4        |4             |4       |         |4    |       |4  |4   |4    |
|MG-996R                   |17      |main servo motor, using the towerpro dimensions                        |1         |1       |1        |          |         |1             |1       |1        |1    |       |1  |1   |1    |
|LD-27MG                   |2       |Hiwonder servo motor dimensions                                        |1         |1       |         |          |         |              |        |         |     |       |





### Electrical Bill of Materials

 - Power Supply: 24V, many Amp, buck converter down to 6V (Need to check current still)
 - PTC Fuses for each motor: RKEF075-2
 - Relays for each motor group: PR9-5V-200-1A
 - NPN Transistors for each motor group relay controller: BC547CBU-ND
 - Diode between motors and servo: 15SQ100



## Mechanical Information

### Joint Rotations & Home
Head nod: facing forward -> 20 degrees
Head tilt: straight up -> 90 degrees
Head turn: straight forward -> 90 degrees
Left (stage left) shoulder pitch -> 


## Electrical Information

TODO:
 - Flyback diodes for the relays (we've added one stand-in diode with zener in the fritzing, but we need to also pick a part and at it to the others, useful example circuit [here](https://blog.mbedded.ninja/electronics/components/relays/))
 - Big capacitors on power supply output (2x system voltage, like 1000uF each)
 - Double check if we actually want a slightly heftier PTC fuse


### Safety Circuitry


#### Motor Current Characteristics

See the motor current characteristics for the arms (without gripper) and legs

![Downward, upward, idle, and when blocked max current ratings for each of the arm motors](res/ArmCurrentRatings.png?raw=true "Arm Current Ratings")

![Downward, upward, idle, and when blocked max current ratings for each of the leg motors](res/LegCurrentRatings.png?raw=true "Leg Current Ratings")


#### Safety Circuit Current Breakdown
We have PTC fuses to protect the servos from melting themselves, and 15A relays so we can cut power to the servos if operation is not currently necessary.


##### Relay Circuits
There are 6 relay groups, broken down for each arm, and leg, as well as the neck and torso. Each relay needs 40mA control current, which becomes 240mA current from the Arduino 5V line. To turn the control circuit on and off, each relay has an individual NPN transistor. These transistors are controlled by a common Arduino pin.

 - Arm Motors: Max Rating: 12.5A, 75W @ 6VDC
    - Chest Shoulder
    - Shoulder
    - Arm Twist
    - Elbow
    - Single Tendon Gripper
 - Leg Motors: Max Rating: 7.5A, 45W @ 6VDC
    - Hip
    - Knee
    - Ankle
 - Head Motors: Max Rating: 7.5A, 45W @ 6VDC
    - Head Twist
    - Head Nod
    - Head Tilt
 - Torso Motors: Max Rating: ~7.5A, 52W @ 7.4VDC
    - Torso Tilt
    - Torso Bow

