#include <Arduino.h>
#include <unistd.h>
#include <cstdio>

static unsigned long _millis_beginning = 0;

void init()
{
    // Initialize main Fakeduino object??
}

unsigned long millis()
{
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    auto now = static_cast<unsigned long>(ts.tv_sec * 1000l + ts.tv_nsec / 1000000l);

    static bool init = false;
    if(!init)
    {
        _millis_beginning = now;
        init = true;
        return 0;
    }

    return now - _millis_beginning;
}

void delay( unsigned long millis )
{
    for(int i = 0; i < 10; i++)
    {
        yield();
        usleep(static_cast<unsigned int>(millis * 100));
    }
}

void tone( int pin, int freq, int dur )
{
    (void) pin;
    char cmd[1024];
    snprintf(cmd, 1024, "padsp signalgen -s 22000 -16 -A 25 -t %dm  square %d", dur, freq);
    system(cmd);
}

void noTone( int pin )
{
    (void) pin;
    system("killall -9 signalgen");
}

SerialInterface Serial;
