#include "DHTx.h"
#include "dhtimpl.h"

#include "fakeduino.h"

DHTx::DHTx(uint8_t pin, uint8_t count)
{
    d = new DHTImpl();
    Fakeduino::get()->showGadget(d);
}

void DHTx::begin(uint8_t usec)
{
}

bool DHTx::read(int16_t *temp, uint16_t *humidity, bool force)
{
    *temp = d->temp() * 10;
    *humidity = d->hum() * 10;

    return true;
}
