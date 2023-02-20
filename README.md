
[![Arduino CI](https://github.com/RobTillaart/FastShiftIn/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/FastShiftIn/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/FastShiftIn/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/FastShiftIn/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/FastShiftIn/actions/workflows/jsoncheck.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/FastShiftIn/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/FastShiftIn.svg?maxAge=3600)](https://github.com/RobTillaart/FastShiftIn/releases)


# FastShiftIn

Arduino library for **AVR** optimized shiftIn - e.g. for 74HC165.

Related libraries
- https://github.com/RobTillaart/FastShiftOut
- https://github.com/RobTillaart/FastShiftInOut
- https://github.com/RobTillaart/ShiftInSlow
- https://github.com/RobTillaart/ShiftOutSlow


## Description

FastShiftIn is a class that has optimized code (AVR only) to shift in data faster 
than the normal **shiftIn()** function.
It speeds up the shift using low level ports and masks. These are predetermined
in the constructor of the FastShiftIn object.

If not an **ARDUINO_ARCH_AVR** or **ARDUINO_ARCH_MEGAAVR** the class falls back 
to the default shiftIn() implementation.

Since 0.3.2 read16(), read24() and read32() are added.
These are experimental and not fully tested yet.


## Performance

The performance of **read()** is substantially faster than the default Arduino 
**shiftIn()**, but not as fast as HW SPI. 
Exact how big the performance gain is can be seen with the example sketch.
It does a comparison and shows how the class is to be used.

Time in microseconds, Arduino UNO

|  function            |   0.2.3  |   0.3.2  |
|:---------------------|---------:|---------:|
|  read()              |   19.30  |   20.49  |
|  read16()            |          |   41.04  |
|  read24()            |          |   62.91  |
|  read32()            |          |   83.95  |
|  readLSBFIRST()      |   19.04  |   19.92  |
|  readMSBFIRST()      |   19.04  |   19.92  |
|  reference shiftIn() |  107.82  |  108.20  |


0.3.2 is a bit slower (incl. reference) than 0.2.3 but still much
faster than the reference.



## Interface

```cpp
#include "FastShiftIn.h"
```

#### Functions

- **FastShiftIn(uint8_t dataIn, uint8_t clockPin, uint8_t bitOrder = LSBFIRST)** Constructor
- **uint16_t read(void)** reads a new value, 8 bit.
- **uint16_t read16(void)** reads a new value, 16 bit.
- **uint32_t read24(void)** reads a new value, 24 bit.
- **uint32_t read32(void)** reads a new value, 32 bit.
- **uint32_t lastRead()** returns last value read.
- **bool setBitOrder(uint8_t bitOrder)** set LSBFIRST or MSBFIRST. 
Returns false for other values.
- **uint8_t getBitOrder(void)** returns LSBFIRST or MSBFIRST.
- **uint16_t readLSBFIRST(void)**  optimized LSB read(), 8 bit.
- **uint16_t readMSBFIRST(void)**  optimized MSB read(), 8 bit.


#### Byte order

It might be that **read16/24/32** has bytes not in the right order.
Then you should use multiple calls to **read()** and merge these
bytes in the order you want them.


## Notes

- The optimizations are AVR only for now, other platforms may follow.
- The 74HC165 needs 0.1uF caps and the data and clock lines may need  
pull up resistors, especially if wires are exceeding 10 cm (4").


## Future

#### Must

#### Should

- extend unit tests

#### Could

- esp32 optimization readLSBFIRST readMSBFIRST
- **read(uint8_t \* arr, uint8_t nr)** ??
- example schema
- would it be interesting to make a fastShiftIn16() etc?
  - squeeze performance but more maintenance.?

#### Wont


