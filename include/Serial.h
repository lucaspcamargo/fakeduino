#pragma once

#include "Arduino.h"

class SerialInterface
{
public:

    static void begin( int baud ) ;

    static int available() ;
    static int read() ;
    static void write( uint8_t data ) ;

    static void print( int num ) ;
    static void print( char ch ) ;
    static void print( const char * str ) ;
    static void print( __FlashStringHelper * str ) ;

    static bool isOpen();

private:

};

extern SerialInterface Serial;
