# Aaron Robot Electrical
All of the information for the electrical systems and wiring for the robot.

## Future Improvements
TODO:
 - So much assembly


## Bill of Materials
Currently all in the excel doc one level up

 - Power Supply: 12V, 30A, buck converter down to 6V (Need to check current still)
 - PTC Fuses for each motor: RKEF075-2
 - Relays for each motor group: PR9-5V-200-1A
 - NPN Transistors for each motor group relay controller: BC547CBU-ND
 - Diode between motors and servo: 15SQ100

## Wiring Guide


## Custom PCBs


### Safety Circuitry


#### Motor Current Characteristics

See the motor current characteristics for the arms (without gripper) and legs below. The measured torso nod motor current during operation was seen as a maximum of 0.6A, and the stall current was measured at 1.12A. The measured torso tilt current during operation similarly hit a maximum of 0.6A, but the stall current when held still was 1.99A.

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
    - Hip flexor motor? (add another 2.5A)
 - Head Motors: Max Rating: 7.5A, 45W @ 6VDC
    - Head Twist
    - Head Nod
    - Head Tilt
    - Camera pan motor? (add another 2.5A)
 - Torso Motors: Max Rating: ~6A, 45W @ 7.4VDC
    - Torso Tilt
    - Torso Bow
    - Spine-hip bow point? (adds another ~3A)



## References
 - [Flyback diode example circuit](https://blog.mbedded.ninja/electronics/components/relays/)