# Motor control driver board
Driver board for the servo bus motors. Includes connection for LED eyes, serial control for bus servo motors, and power control for bus servo motors, with mounting spot for microcontroller dev board.

## To-Do Edits for Final PCB
 - Label the relays + transistors for each relay circuit (aka arms relay, legs relay)
 - Fix the big boy diode hole size (Should be like, .082" which is the drill bit size I used the on the drill press, but please fact check me)
 - Transistor spacing (more space between the pads)
 - Q3 trace overlay issue (we're self-shorting lol)
 - Screw holes for the arduino board
 - Zane says we should round our pcb corners lol
 - PCB board name/revision number on solder mask?
 - Making the JST labels end with L or R instead of 1 would make it just a bit easier to read
 - Moving the JST labels out a bit means if we use non-right angle connectors for dumb reasons we can still read the labels
 - The 10k resistor label could be a lil clooooser
 - Having a marker on the jst labels that says which pin is ground would be a bit helpful for confirming which connector direction we need
 - Label for the jsts which pin is signal, pwr, ground (for soldering order safety)
 - The jst left leg vs right leg (and arms) labels actually don't matter because of how the serial is set up, as long as they're on the right relay. (The grippers DO matter tho)
 - Swap the connector for the 5V power to the smaller XT30PW-M connector for protection from user error: https://www.tme.com/us/en-us/details/xt30pw-m/dc-power-connectors/amass/


## Bill of Materials (BoM)
This BoM includes all items necessary to populate this particular PCB. It does not include all items necessary for the entire robot, which can be found [here](../../BoM.md). The parts listed are standalone items you need, as well as a consolidated list of all items you can purchase as a group from [DigiKey](https://www.digikey.com/). 

 - 1x [Mini Arduino ATMEGA2560](https://www.amazon.com/dp/B0D7ZT5M2R), any manufacturer who matches this footprint/pinout will work.
 - 1x [AMASS XT60PW-M Connector](https://www.tme.com/us/en-us/details/xt60pw-m/dc-power-connectors/amass/)
 - 1x [AMASS XT30PW-M Connector](https://www.tme.com/us/en-us/details/xt30pw-m/dc-power-connectors/amass/)
 - 2.54mm pitch female header strips, for connecting the Arduino
 - [DigiKey Part List](../JamieMotorControlBoardDigiKey.csv)

