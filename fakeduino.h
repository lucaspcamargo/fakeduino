#ifndef FAKEDUINO_H
#define FAKEDUINO_H

#include "fakeduino_global.h"

struct FakeduinoPrivate;
class QWidget;

class FAKEDUINO_EXPORT Fakeduino
{
    // private constructor
    Fakeduino();
public:
    ~Fakeduino();

    static Fakeduino* get();
    void exec(void (*voidfunc)());

    uint8_t eepromRead( uint8_t addr );
    void eepromWrite( uint8_t addr, uint8_t value );

    void keyPressed( uint32_t kc );
    void keyReleased( uint32_t kc );
    bool isPressed( uint32_t kc );

    void showGadget( QWidget * qw );

private:
    void eepromPrepare();
    void eepromTerminate();

    FakeduinoPrivate *d;
};



#endif // FAKEDUINO_H
