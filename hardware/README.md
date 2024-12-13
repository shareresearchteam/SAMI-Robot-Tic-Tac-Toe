![image](https://github.com/user-attachments/assets/45520710-7f09-4389-8d31-96ac0d6e39b5)# JAMIE Robot Hardware
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
fishing line (check thickness) and eyelets (for tendon gripper)

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
*If using Prusa i3 printers with Prusa Slicer,* all parts should be printed at 0.3mm resolution ("draft quality" on Prusa Slicer), with 15% gyroid infill, and organic supports enabled (where necessary), **except for the chest piece,** which should be printed at 0.2mm resolution, with 15% gyroid infill, and normal grid-style supports instead. Alternatively, the **finger hinges** should be printed using PETG filament with 0% gyroid infill and a brim.

**The hands** used for this robot have been sized down by 42.5% with minimal changes to the bolt holes from the original prosthetic model, but the mechanism funtionality remains the same.

Print orientations are shown below for each part, along with the part names that are used throughout this documentation.

#### Headshell
<img src="https://github.com/user-attachments/assets/0e18def7-b7d4-41be-88ae-e472a4a695b2" width="516.75" height="379.75"/>

#### Chest and Headshell Panel
<img src="https://github.com/user-attachments/assets/636dd761-b5fc-43b5-8e5c-8b0e2f4229c1" width="516.75" height="379.75"/>

#### Head/Neck Connectors and Spine
<img src="https://github.com/user-attachments/assets/e3e65f0d-32de-43c1-860c-792ffeab9e75" width="516.75" height="379.75"/>

#### Hands and Lower Arms
<img src="https://github.com/user-attachments/assets/8007a63c-7314-44be-8fca-9a795e9bf6fc" width="516.75" height="379.75"/>

#### Finger Hinges
<img src="https://github.com/user-attachments/assets/2c212639-9a70-4d46-acc8-a449d4b221ca" width="516.75" height="379.75"/>

#### Hips and Upper Legs
<img src="https://github.com/user-attachments/assets/83526c1b-5862-4ef0-a28d-257d7125a591" width="516.75" height="379.75"/>

#### Lower Legs and Feet
<img src="https://github.com/user-attachments/assets/c406bfa1-295f-4980-ab76-eb80dea6b9db" width="516.75" height="379.75"/>

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

<img src="https://github.com/user-attachments/assets/58a353cc-a3eb-429b-9c43-654319a532c8" width="250" height="400"/>

##### Hands Construction
Before beginning assembly, please be sure to double check that the hinges match the size-dependent and axial orientation on the fingers, with the fingers aligned to their corresponding palm (*Figures 1-3*). It is **highly** recommended to fit the largest hinges into the palm first. While the hinges should be printed as a more "spongey" material, you may need to use a pair of pliers to manually squeeze the larger side of the hinge into its gap in the palm. You can also use a file or a craft knife to trim a little from the opening sides. After fitting the palm hinges, all fingers can be assembled separately from the hand. They should perfectly slide into the finger hinge slots (following size contraints but axial orientation shouldn't matter). 

Stringing the fishing line through the hands should be the **last step** (with fingers not yet assembled to the palm). Begin by measuring the amount you think you might need for your project by fitting the line through the bottom of the hand and up through the 3D piece (**do not cut yet**). Then, continue stringing your fishing line up the holes in the fingers and upon reaching the tip of the top finger, restring back through the second hole and leaving enough to tie it off (*Figure 4*). To get an accurate length of fishing line you will need, attach the finger to the palm and measure how much you think you will need at the bottom of the hand (leaving adequate space at the top to tie off your line). After ensuring you have the right length, you can cut off your line from its container and use pliers to tie a double knot at the top of the finger.

<img src="https://github.com/user-attachments/assets/03f3db47-aefa-4afc-8d25-8f3e58caebf9" width="516.75" height="379.75"/>

*Figure 1*: Composition and BOM of Flexy-Hand 2 ([Flexy-Hand 2]())


<img src="https://github.com/user-attachments/assets/b6199e72-d340-43bb-9e2d-71c6663d8e74" width="516.75" height="379.75"/>

*Figure 2*: Finger plate with labeled orientation ([Flexy-Hand 2]())


<img src="https://github.com/user-attachments/assets/39fc64ee-b7f5-481a-aca4-d31c52dddc7e" width="500" height="250"/>

*Figure 3*: Hinge orientation for all fingers ([Flexy-Hand 2]())


<img src="https://github.com/user-attachments/assets/8d863733-dc20-4b80-aee7-aa96baf8d8a7" width="516.75" height="379.75"/>

*Figure 4*: Tendon knot placement for all fingers ([Flexy-Hand 2]())


##### Servo JST Cables
The JST cables that come with the servos are a very tight fit into the servo recepticals. We recommend only partially inserting them for initial assembly and testing. These partially inserted connectors will still make electrical contact for continuity testing and motor operation, while still providing more space for pliers to pull the header out without touching the wires themselves. Once operation is confirmed, the connectors can easily be pressed the rest of the way in.

Additionally, despite how tight the connectors are into the recepticals, be very careful when disconnecting them to not pull on the cable wires themselves, as this could damage the individual wires or pull them out of the JST header.


#### Neck and Torso Assembly


#### Arm Assembly


#### Lower Body Assembly
When assembling the lower body it is best to start with the feet and then work your way up to the upper legs. This ensures that you will have everything aligned and allows you to begin with the more simpler pieces first.

The first and foremost step that is **highly** recommended is pre-setting all of the Lower Body motors before beginning the assembly. All HiWonder HTS-20H servos involved in this assembly would be: Right Hip, Knee, Ankle and Left Hip, Knee, Ankle. All correlated motor IDs are listed above in [Initializing Servo IDs and Positions], as well as instructions for how to set the IDs and their home positions. It is also recommended that you check the servo horn orientation during this time, following the alignment found here [Servo Horn Alignment].

##### Feet
Next up is the feet. The feet are a fairly quick and simple set-up that will require a M3 screwdriver, 1 servo horn per foot, 8 silver M3 screws and 2 black M3 screws from the motor package. As suggested before, it is **highly** recommended that you pre-thread the 3D-printed body so that you don't accidentally re-thread the servo horn. After pre-threading you are ready to move onto the next step. **Do not** attach the Ankle servo horn at this time.

##### Lower Legs
Following the set-up of the feet are the lower legs of the robot. The lower legs will require a M3 screwdriver, 1 servo horn per leg, 8 silver M3 screws and 2 black M3 screws from the motor package, 4 M3 x 18 mm (check this), 4 rubber spacers (included in the motor package), and 4 hexagonal-shaped nuts. As done same with the feet, pre-thread all the screw holes on the lower legs before beginning assembly. Next, add the rubber spacers onto the screw notches of the motor (pictured below) as this will help stabilize our screws in the frame. After, you can begin attaching the Hiwonder servo into its correct placement on the lower end of the leg, ensuring that the servo horn can be attached to the foot later on. 

#### Hands Assembly


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
 - [Flexy-Hand 2](https://www.thingiverse.com/thing:380665)
 - []()
