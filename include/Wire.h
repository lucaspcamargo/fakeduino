#pragma once

#include "./Arduino.h"

class WireInterface
{
public:
    static void beginTransmission( uint8_t addr ) { }
    static void write(uint8_t *buf, uint8_t sz) { }
    static void endTransmission() { }
    static uint8_t read() { return 0; }
    static uint8_t requestFrom( uint8_t addr, uint8_t sz ) { return sz; }
};

static WireInterface Wire;
