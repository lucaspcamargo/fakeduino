#include "LiquidCrystal.h"

#include "qtclean.h"
#include "liquidcrystalimpl.h"
#include "fakeduino.h"

LiquidCrystal::LiquidCrystal(int, int, int, int, int, int)
{
    d = new LiquidCrystalImpl();
    Fakeduino::get()->showGadget(d);
}

LiquidCrystal::~LiquidCrystal()
{
    delete d;
}

void LiquidCrystal::begin( int cols, int lines )
{
    d->begin( cols, lines );
}

void LiquidCrystal::clear()
{
    d->clear();
}

void LiquidCrystal::setCursor( int x, int y )
{
    d->gotoxy(x, y);
}

void LiquidCrystal::print( int num )
{
    char buf[32];
    snprintf(buf, 32, "%d", num);
    d->puts(buf);
}

void LiquidCrystal::print( char ch )
{
    d->put(ch);
}

void LiquidCrystal::write( unsigned char ch )
{
    d->put(ch);
}

void LiquidCrystal::print( const char * str )
{
    d->puts(str);
}

void LiquidCrystal::print( __FlashStringHelper * str )
{    
    d->puts(reinterpret_cast<const char *>(str));
}

void LiquidCrystal::createChar(uint8_t index, uint8_t* data7bytes)
{
    (void) index;
    (void) data7bytes;
}
