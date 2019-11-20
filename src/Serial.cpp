#include "Serial.h"

#include "qtclean.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QFile>
#include "serialmonitor.h"
#include "fakeduino.h"

static struct
{
    QSerialPort *sp = nullptr;
    SerialMonitor *sm = nullptr;
} d;

void SerialInterface::begin( int baud )
{
    auto ports = QSerialPortInfo::availablePorts();

    QSerialPortInfo found;

    for(auto pi : ports)
    {
        if(pi.isNull() || pi.isBusy())
            continue;

        fprintf(stderr, "Serial port found: %s\n", pi.portName().toStdString().c_str());
        if(found.isNull() || found.portName().contains("MON"))
            found = pi;
    }

    if(found.isNull())
        fprintf(stderr, "No serial port found!\n");
    else
    {
        if(QFile("/dev/ttyMON").exists())
        {
            fprintf(stderr, "Override to /dev/ttyMON\n");
            d.sp = new QSerialPort("/dev/ttyMON");
        }
        else
            d.sp = new QSerialPort(found);

        d.sp->open(QIODevice::ReadWrite);
        if(!d.sp->isOpen())
        {
            fprintf(stderr, "Could not open serial port: %s\n", d.sp->errorString().toStdString().c_str());
            delete d.sp;
            d.sp = nullptr;
            return;
        }
        d.sp->setBaudRate( baud );

        d.sm = new SerialMonitor();

        Fakeduino::get()->showGadget(d.sm);
    }
}

bool SerialInterface::isOpen()
{

    return d.sp && d.sp->isOpen();
}

int SerialInterface::available()
{
    yield();

    if(!d.sp)
        return 0;

    return static_cast<int>(d.sp->bytesAvailable());
}

int SerialInterface::read()
{
    yield();

    if(!d.sp)
        return 0;

    auto res = d.sp->read(1);
    if(res.size())
    {
        if(d.sm)
            d.sm->traffic(true, res[0]);
        return res[0];
    }
    else return -1;
}

void SerialInterface::write( uint8_t data )
{
    yield();

    if(!d.sp)
        return;

    d.sp->write( QByteArray{(const char*)&data, 1} );

    if(d.sm)
        d.sm->traffic(false, data);
}

void SerialInterface::print( int num )
{
    yield();

    if(!d.sp)
        return;

    char buf[32];
    snprintf(buf, 32, "%d", num);
    d.sp->write(buf);

    char *c = buf;
    if(d.sm)
        while(*c)
            d.sm->traffic(false, *(c++));
}

void SerialInterface::print( char ch )
{
    yield();

    write((uint8_t) ch);
}

void SerialInterface::print( const char * str )
{
    yield();

    if(!d.sp)
        return;

    d.sp->write(str);
    const char *c = str;
    if(d.sm)
        while(*c)
            d.sm->traffic(false, *(c++));
}

void SerialInterface::print( __FlashStringHelper * str )
{
    print( reinterpret_cast<const char*>(str) );
}
