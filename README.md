# FastShiftIn

Arduino library for (AVR) optimized shiftIn - e.g. for 74HC165

A library for FastShiftOut also exist.

## Description

FastShiftIn is a class that speeds up the shifting of the bits by using predetermined ports and masks. 
These are predetermined inthe constructor of the FastShiftIN object.

The performance of **read()** is substantially faster than the default Arduino **shiftIn()**, 
but not as fast as HW SPI. Exact how big the performance gain is can be seen with the example sketch.
It does a comparison and shows how the class is to be used.

Version 0.2.0 added **readLSBFIRST()** and **readMSBFIRST()** to squeeze max performance. 
The next stop might be assembly.

**Note**
The optimizations are AVR only for now, other platforms may follow.

**Note** 
The 74HC165 needs 0.1uF caps and the data and clock lines 
may need pull up resistors, especially if wires are exceeding 10 cm (4").

## Operation

See examples

