

## Mechanical Bill of Materials
The mechanical BoM includes all of the 3D printed parts, and associated screw pieces:

| Part | Quantity | Additional Notes | Right Eye |
| :------ | :----------: | --------: | --------: |
| M3x     |   GND        | GND       | GND       |
| 5V      |   5V         | ------    | ------    |
| A4      |   SDA        | ------    | ------    |
| A5      |   SCL        | ------    | ------    |
| Pin 6   | ------       | Din       | ------    |
| Pin 7   | ------       | ------    | Din       |


## Electrical Bill of Materials
Power Supply: 24V, many Amp, buck converter down to 6V (Need to check current still)
PTC Fuses for each motor: RKEF075-2
Relays for each motor group: PR9-5V-200-1A




Relay setup breakdowns! My notes based on looking for relays to handle each section. Checking again I think we're doing 6 relays, but check the datasheet for yourself.


If by side and arm/leg:
chest shoulder
shoulder shoulder
twist shoulder
elbow
single tendon gripper
(12.5A all stall current)
(75W @ 6VDC)

hip
knee
ankle
(7.5A all stall current)
(45W @ 6VDC)

If Body motion weaker motors:
chest tilt
hip forward
neck turn
neck nod
neck tilt
(12.5A all stall current)
(75W @ 6VDC)


If we're doing big boy motors, I have those split out too.
BIG BOY MODE (3+ A stall current)(7.4 VDC)
chest tilt 
hip forward
(~7A all stall current)
(~52W @ 7.4VDC)

With normal neck motors?
neck turn
neck nod
neck tilt
(7.5A all stall current)
(45W @ 6VDC)
