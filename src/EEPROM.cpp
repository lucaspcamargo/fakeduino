#include <EEPROM.h>
#include "fakeduino.h"

uint8_t EEPROMInterface::read( uint8_t addr )
{
    Fakeduino::get()->eepromRead(addr);
}

void EEPROMInterface::write( uint8_t addr, uint8_t val )
{
    Fakeduino::get()->eepromWrite(addr, val);
}
