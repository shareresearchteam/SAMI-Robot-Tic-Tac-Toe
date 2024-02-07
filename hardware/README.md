# Aaron Robot Hardware
All of the hardware information for the Aaron robot.

## Future Improvements
More involved improvements for future development, in no particular order
 - Add hip roll/out at side flexor motors
 - Add a torso twist motor
 - 


## Bill of Materials

### Mechanical Bill of Materials
The mechanical BoM includes all of the 3D printed parts, and associated screw pieces (currently in an excel doc for my sanity)



### Electrical Bill of Materials
Also in the same excel doc for the moment

 - Power Supply: 12V, 30A, buck converter down to 6V (Need to check current still)
 - PTC Fuses for each motor: RKEF075-2
 - Relays for each motor group: PR9-5V-200-1A
 - NPN Transistors for each motor group relay controller: BC547CBU-ND
 - Diode between motors and servo: 15SQ100



## Mechanical Information

### Joint Rotation Range & Centering
These are hardware joint angles for assembly, ***not for operation***. The arduino code takes in values so the operator does not have to remember how the joints are reversed.

|                      | Min | Max | Home |   |
|----------------------|-----|-----|------|---|
| Head Nod             | 0   |     | 20   |   |
| Head Turn            | 0   | 180 | 90   |   |
| Head Tilt            | 0   | 180 | 90   |   |
| Torso Bow            | 40  | 140 | 90   |   |
| Torso Tilt           | 40  | 140 | 90   |   |
| Right Shoulder Pitch | 0   | 180 | 0    |   |
| Right Shoulder Roll  | 0   | 180 | 25   |   |
| Right Arm Twist      | 0   | 180 | 90   |   |
| Right Elbow          |     |     |      |   |
| Right Gripper        |     |     |      |   |
| Left Shoulder Pitch  | 0   | 180 | 180  |   |
| Left Shoulder Roll   | 0   | 180 | 155  |   |
| Left Arm Twist       | 0   | 180 | 90   |   |
| Left Elbow           |     |     |      |   |
| Left Gripper         |     |     |      |   |
| Right Hip            |     |     | 90   |   |
| Right Knee           |     | 180 | 175  |   |
| Right Ankle          |     |     | 90   |   |
| Left Hip             |     |     | 90   |   |
| Left Knee            | 0   |     | 5    |   |
| Left Ankle           |     |     | 90   |   |

### 3D Model QoL Adjustments
To do when time permits, in no particular order
 - Slightly extend the round nubs that we use to stabilize motor rotation (the round nubs opposite a motor shaft) for the chest and neck connectors
 - Check if the head tilt motor support nub is actually inline with the motor shaft
 - Decrease motor horn screw holes sizing on spine/hip connection point for better attachment stability
 - Improve the arm twist motor attachment to be easier and more consistent/stable
 - Make elbow motor mounting more stable
 - Make knee motor mounting more stable
 - Make ankle motor easier to install
 - Make the shoulders on the chest piece less... whatever they are (less pointy on ends of shoulder tops, maybe use square nuts and hide the motors from the front, etc)
 - **Separate the servo joint sections from the rest of the body links, so we can make different shape designs for the limbs/torso without needing to re-zero or re-assemble the motors**



## Electrical Information
Check the [Electrical](./Electrical/) subfolder for all of the information on the electrical side of the circuit.

## References
 - []()