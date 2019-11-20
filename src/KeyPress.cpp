#include "KeyPress.h"
#include "fakeduino.h"

namespace KeyPress
{
    bool isPressed( uint32_t keyId )
    {
        return Fakeduino::get()->isPressed(keyId);
    }
}
