//
//    FILE: FastShiftIn.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: Fast ShiftIn for 74HC165 register, AVR optimized
//    DATE: 2013-09-29
//     URL: https://github.com/RobTillaart/FastShiftIn.git
//

#include "FastShiftIn.h"

FastShiftIn::FastShiftIn(const uint8_t datapin, const uint8_t clockpin, const uint8_t bitOrder)
{
    _bitorder = bitOrder;

    pinMode(datapin, INPUT);
    pinMode(clockpin, OUTPUT);

    // uint8_t _datatimer  = digitalPinToTimer(datapin);
    // if (_datatimer != NOT_ON_TIMER) turnOffPWM(_datatimer); TODO
    uint8_t _dataport   = digitalPinToPort(datapin);
    _datain = portOutputRegister(_dataport);
    _databit = digitalPinToBitMask(datapin);

    // uint8_t _clocktimer = digitalPinToTimer(clockpin);
    // if (_clocktimer != NOT_ON_TIMER) turnOffPWM(_clocktimer);
    uint8_t _clockport  = digitalPinToPort(clockpin);
    _clockin = portOutputRegister(_clockport);
    _clockbit = digitalPinToBitMask(clockpin);
}


int FastShiftIn::read()
{
    uint8_t value = 0;
	uint8_t cbmask1 = _clockbit;
	uint8_t cbmask2 = ~_clockbit;
	uint8_t dbmask = _databit;

    for (uint8_t i = 0, m = 1, n = 128; i < 8; i++, m <<= 1, n >>= 1)
    {
        uint8_t oldSREG = SREG;
        cli();
        *_clockin |= cbmask1;

        if ((*_datain & dbmask) > 0)
        {
            if (_bitorder == LSBFIRST)
            {
              value |= m;
            }
            else
            {
              value |= n;
            }
        }
        *_clockin &= cbmask2;
        SREG = oldSREG;
    }
    _value = value;
    return _value;
}

int FastShiftIn::readLSBFIRST()
{
    uint8_t value = 0;
	uint8_t cbmask1 = _clockbit;
	uint8_t cbmask2 = ~_clockbit;
	uint8_t dbmask = _databit;

	for (uint8_t m = 1; m > 0; m <<= 1)
	{
		uint8_t oldSREG = SREG;
		cli();
		*_clockin |= cbmask1;
		if ((*_datain & dbmask) > 0)
		{
			value |= m;
		}
		*_clockin &= cbmask2;
		SREG = oldSREG;
	}
    _value = value;
    return _value;
}

int FastShiftIn::readMSBFIRST()
{
    uint8_t value = 0;
	uint8_t cbmask1 = _clockbit;
	uint8_t cbmask2 = ~cbmask1;
	uint8_t dbmask = _databit;

	for (uint8_t n = 128; n > 0; n >>= 1)
	{
		uint8_t oldSREG = SREG;
		cli();
		*_clockin |= cbmask1;
	
		if ((*_datain & dbmask) > 0)
		{
			value |= n;
		}
		*_clockin &= cbmask2;
		SREG = oldSREG;
	}
    _value = value;
    return _value;
}

// -- END OF FILE --
