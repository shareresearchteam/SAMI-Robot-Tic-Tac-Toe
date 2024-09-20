# JAMIE Robot Hardware
All of the hardware information for the robot system.

 1. [Bill of Materials (BoM)]()
 2. [Assembly Instructions]()
 3. [Mechanical Information]()
 4. [Electrical Information]()

## Bill of Materials (BoM)
The below mechanical and electrical BoMs include all components that are assembled into the robot system, and are the minimum hardware requirements necessary to make the system. In addition to this, it is assumed you have a computer to run the higher level system control, with one USB port as a minimum, with an additional USB port for the sensor box, and an HDMI port for the captioning system.

In addition to the above components, as part of the assembly process, it is assumed you have access to standard electrical prototyping equipment such as breadboards and jumper wires, as well as a benchtop power supply or other 12V power source for use during robot assembly.

### Mechanical Bill of Materials
The mechanical BoM includes all of the 3D printed parts, and associated screw pieces (currently in an excel doc for my sanity)

#### Robot 
3D printed so many parts
so, so many screws
Ikea chair
cable ties
diffusion acrylic (optix is what we used)
fishing line and eyelets (for tendon gripper)

#### Sensor Box
3D printer enclosure
3D printed button tops
3D printer button covers
some screws

#### Captioning System
3D printed enclosure
some screws probably


### Electrical Bill of Materials
The electric BoM includes all components necessary for populating all PCBs and sensors, as well as initial assembly. It's currently in an excel doc along with the mechanical bom

#### Robot 
17x HiWonder HTS-20H servos
2x HiWonder HTS-35H servos
2x linear actuator
so much pcb electronics
jst connector cables for the servos
arduino mega 256?
2x adafruit led 8x8 panels
12V power supply
power switch
5V power supply?
more bits idk
usb cable
panel mount usb cable?
##### Optional bits to mount in the robot space:
speakers
microphone
webcam

#### Sensor Box
2x PIR sensor
1x ultrasonic sensor
1x arduino
2x button
rfid thing
more bits
usb cable
panel mount usb cable


#### Captioning System
7" portable monitor (with dimensions matching [this one](https://www.amazon.com/dp/B09MFNLRQQ))
HDMI cable (probably comes with)
usb power cable (probably comes with)



## Assembly Instructions
 1. [Robot Assembly Instructions]()
     1. [Initializing Servo IDs and Positions]()
     2. [Overall Assembly Information]()
     3. [Neck and Torso Assembly]()
     4. [Arm Assembly]()
     5. [Lower Body Assembly]()
     6. [Final Assembly]()
 2. [Sensor Box Assembly Instructions]()
 3. [Caption Assembly Instructions]()

### Robot Fabrication and Assembly Instructions
*If using Prusa i3 printers with Prusa Slicer,* all parts should be printed at 0.3mm resolution ("draft quality" on Prusa Slicer), with 15% gyroid infill, and organic supports enabled (where necessary), **except for the chest piece,** which should be printed at 0.2mm resolution, with 15% gyroid infill, and normal grid-style supports instead.

Print orientations are shown below for each part, along with the part names that are used throughout this documentation.

**IMG GO HERE**

#### Initializing Servo IDs and Positions

You will need to communicate with the motors as part of the assembly process. As such, we provide a simplified breadboard-able circuit to use in communicating with the motors during this process. See below for the circuit wiring.

**Breadboard assembly circuit wiring go here**

Before assembling the robot, it is necessary to assign unique motor IDs for each joint motor. You can set these IDs with the [SetServoID Arduino code project](../Arduino/SetServoID/) as well as a simplified breadboard circuit for communicating, presented [here](). Any ID numbers may be chosen, but the default configuration file, and these assembly instructions, will use the joint names and IDs as listed in the table below.

|     Joint Name       | ID |
|----------------------|----|
| Head Tilt            | 01 |
| Head Nod             | 02 |
| Head Turn            | 03 |
| Right Shoulder Pitch | 04 |
| Right Shoulder Roll  | 05 |
| Right Arm Twist      | 06 |
| Right Elbow          | 07 |
| Left Shoulder Pitch  | 08 |
| Left Shoulder Roll   | 09 |
| Left Arm Twist       | 10 |
| Left Elbow           | 11 |
| Right Hip            | 12 |
| Right Knee           | 13 |
| Right Ankle          | 14 |
| Left Hip             | 15 |
| Left Knee            | 16 |
| Left Ankle           | 17 |
| Torso Bow            | 18 |
| Torso Tilt           | 19 |
| Right Gripper        | 20 |
| Left Gripper         | 21 |


During assembly of the robot, it will be necessary to set each motor to a known rotation and then assemble the parts to match that orientation. These positions are *not operational home*, but are instead an easy reference position for use in assembly. The robot assembly pose, along with each joint name, motor ID, and the motor angle corresponding to the current pose, are shown in the image below. 

**IMG GO HERE**

#### Notes On Assembly Process
Some components are sensitive, or could be easily damaged during assembly. To help mitigate this, these notes are provided as important notes to keep in my during the process.

##### Screwing Threading Plastic and Metal
The entire system is largely assembled with machine screws through 3D printed parts, with either lock nuts or captured square nuts as backing. To aid with alignment and minimize cross-threading the nuts or other components, it's recommended to first screw the machine screws all the way into the 3D printed hole, to thread the plastic and clear any debris from the 3D printing process, before unscrewing the screws, and then assembling the full joint with any nuts, servos, or motor horns screwed in once the plastic holes have been cleared and the screw screws easily into the plastic hole.

Additionally, when screwing to the metal servo horns, it is very easy to misalign your screw and cross thread the screw onto the servo horn. Clearing plastic holes first should allow you to easily hand thread the screw through the plastic into the horn, and simply finish tightening the fully inserted screw down with a screwdriver.

##### Servo Horn Alignment
Once a motor has been set to the default position, you can attach the metal horn with the small indent facing towards the motor body (see below image) as a useful visual reference to assist in verifying that the servo does not get misaligned or shifted during the assembly process. Additionally, when screwing the machines

**IMG GO HERE**

##### Servo JST Cables
The JST cables that come with the servos are a very tight fit into the servo recepticals. We recommend only partially inserting them for initial assembly and testing. These partially inserted connectors will still make electrical contact for continuity testing and motor operation, while still providing more space for pliers to pull the header out without touching the wires themselves. Once operation is confirmed, the connectors can easily be pressed the rest of the way in.

Additionally, despite how tight the connectors are into the recepticals, be very careful when disconnecting them to not pull on the cable wires themselves, as this could damage the individual wires or pull them out of the JST header.


#### Neck and Torso Assembly


#### Arm Assembly


#### Lower Body Assembly

#### Final Assembly
PCB and electrical box wiring goes here

### Sensor Box Assembly Instructions


### Caption System Assembly Instructions







## Mechanical Information

### Robot Joint Rotation & Home Position Reference
Below is a listing of the safe operation ranges and home angle positions for each robot joint. In addition to this are images showing the robot in home position, along with the rotational position corresponding the the minimum and maximum positions for each joint, for reference when designing behaviors.

|     Joint Name       | Min | Max | Home |   |
|----------------------|-----|-----|------|---|
| Head Nod             | 0   | 240 | 120  |   |
| Head Turn            | 0   | 240 | 120  |   |
| Head Tilt            | 0   | 240 | 120  |   |
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

 
 

## Electrical Information
The [Electrical](./Electrical/) subfolder contains detailed information on fabricating and assembling the custom PCBs for both the robot itself as well as the sensor box.


## Future Improvements
More involved improvements for future development, in no particular order
 - Add hip roll/out at side flexor motors
 - Add foot side-side turn motor
 - Add a torso twist motor
 - Separate the servo joint sections from the rest of the body links, so we can make different shape designs for the limbs/torso without needing to re-zero or re-assemble the motors

## References
 - []()