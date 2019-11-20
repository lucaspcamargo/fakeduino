#pragma once

#include "Arduino.h"


class LiquidCrystalImpl;
class LiquidCrystal
{
public:
    LiquidCrystal(int, int, int, int, int, int);
    virtual ~LiquidCrystal();

    void begin( int cols, int lines );
    void clear();

    void setCursor( int x, int y );
    void write( unsigned char num );
    void print( int num );
    void print( char ch );
    void print( const char * str );
    void print( __FlashStringHelper * str );

    void createChar(uint8_t index, uint8_t* data7bytes);

private:
    LiquidCrystalImpl *d;
};
