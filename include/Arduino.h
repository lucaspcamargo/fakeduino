#pragma once

#include <cstdint>
#include <cstdbool>
#include <cstring>
#include <cmath>
#include <ctime>
#include <cctype>

#include "fake_avr.h"

typedef uint8_t byte;

typedef void (*voidfunct_t)();

void init();
void setup(); // declaration, definition required from sketch
void loop();  // declaration, definition required from sketch

void fakeduino_loop(voidfunct_t);

unsigned long millis();
void delay( unsigned long millis );
void yield();

#define OUTPUT 0
#define INPUT 1
#define INPUT_PULLUP 2

inline void pinMode( int pin, int mode ) {}
inline bool digitalRead( int pin ) { return 0; }
inline bool digitalWrite( int pin, bool value ) { return 0; }

void tone( int pin, int freq, int dur );
void noTone( int pin );

inline bool isAlphaNumeric( int c ) { return std::isalnum(c); }


#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19
#define A6 20
#define A7 21

#define F(STR) (STR)
class __FlashStringHelper;

#include "Serial.h"
