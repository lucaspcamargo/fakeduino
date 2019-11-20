#pragma once

#include "./Arduino.h"

class EEPROMInterface
{
public:
    static uint8_t read( uint8_t addr );

    static void write( uint8_t addr, uint8_t val );

    static void update( uint8_t addr, uint8_t val )
    {
        write( addr, val );
    }
};

static EEPROMInterface EEPROM;
