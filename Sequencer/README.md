# Trigger Sequencer
Here are the files related to the Trigger Sequencer

Theory:
=======
The module can either generate its own beat using a timer or accept a trigger input for this. You can select this with a switch.
Using the first Potentiometer you can adjust the speed of the internal trigger.
Based on the trigger, whether internal or external, it steps through an array of data, the pattern you input is saved to the array and sent to the outputs. 
This loops once an amount of steps set by the second potentiometer is reached.
There are also two buttons on this module, one prevents the step number from incrementing, the other clears the array data at the current step.

Pinout:
=======

* TX  = output 7
* RX  = output 8
* 2  = output 6
* 3  = output 5
* 4  = output 4
* 5  = output 3
* 6  = output 2
* 7  = output 1
* 8  = input 8
* 9  = input 7
* 10 = input 6
* 11 = input 5
* 12 = input 4
* 13 = trigger in / trigger out
* 14 = input 3
* 15 = input 2
* 16 = input 1
* 17 = trigger mode input
* 18 = delete input (pullup)
* 19 = hold input (pullup)
* A6 = speed input (analog)
* A7 = tracksize input (analog

Known oddities:
===============

* This code works on the Arduino Nano and Pin compatible Processors only as it uses every pin and is writted with direct register access.
* The potentiometer that controls the Timing needs 2 capacitors, otherwise the timing may be unstable.
* While programming, nothing should be connected to Pin 1 and 0 as that prevents the serial communication.
