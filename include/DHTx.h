#pragma once
#include <cstdint>

class DHTImpl;

class DHTx
{
public:
    DHTx(uint8_t pin, uint8_t count=6);

    void begin(uint8_t usec=55);

    bool read(int16_t *temp, uint16_t *humidity, bool force=false);

    int convertCtoF(int c) { return c * 18000 / 10000 + 32; }
    int convertFtoC(int f) { return (f - 32) * 5555 / 10000; }

private:
    DHTImpl *d;
};
