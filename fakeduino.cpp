#include "fakeduino.h"
#include "fakeduino_defs.h"

#include <QtWidgets/QApplication>
#include <QTimer>
#include <QDebug>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <QIcon>
#include <impl/workspace.h>

struct FakeduinoPrivate
{
    QApplication *app   = nullptr;
    Workspace *wspc =  nullptr;
    int eeprom_fd       = -1;
    QTimer *mainLoop = nullptr;
    void (*loopFunc)() = nullptr;

    QSet<uint32_t> pressedKeys;

} __attribute__((packed));



static Fakeduino * _fd_instance = nullptr;

Fakeduino::Fakeduino()
{
    static int one = 1;
    d = new FakeduinoPrivate();
    d->app = new QApplication(one, &program_invocation_name);

    Q_INIT_RESOURCE(fakeduino);

    d->app->setWindowIcon(QIcon(":/fakeduino/icon_256.png"));

    d->wspc = new Workspace();
    d->wspc->setWindowIcon(QIcon(":/fakeduino/icon_256.png"));
    d->wspc->show();

    d->mainLoop = new QTimer();

    eepromPrepare();


    d->wspc->showStatus("fakeduino ready");
}

Fakeduino::~Fakeduino()
{
    delete d;
}

Fakeduino* Fakeduino::get()
{
    if(!_fd_instance)
        _fd_instance = new Fakeduino();

    return _fd_instance;
}

#include <functional>

void Fakeduino::exec(void (*voidfunc)())
{
    d->loopFunc = voidfunc;

    d->mainLoop = new QTimer();
    d->mainLoop->setTimerType(Qt::CoarseTimer);
    d->mainLoop->connect(d->mainLoop, &QTimer::timeout, [this](){d->loopFunc();});
    d->mainLoop->start(2);

    d->app->exec();
}


void Fakeduino::showGadget( QWidget * qw )
{
    d->wspc->showGadget(qw);
}


// eeprom

uint8_t Fakeduino::eepromRead( uint8_t addr )
{
    lseek(d->eeprom_fd, addr, SEEK_SET);
    uint8_t ret;
    read(d->eeprom_fd, &ret, 1);
    return ret;
}

void Fakeduino::eepromWrite( uint8_t addr, uint8_t value )
{
    lseek(d->eeprom_fd, addr, SEEK_SET);
    write(d->eeprom_fd, &value, 1);
}

void Fakeduino::eepromPrepare()
{
    d->eeprom_fd = open( FDO_EEPROM_LOCATION, O_RDWR | O_CREAT, 0644 );
    if(d->eeprom_fd < 0)
        perror("EEPROM");
    ftruncate( d->eeprom_fd, FDO_EEPROM_SIZE );
}

void Fakeduino::eepromTerminate()
{
    close(d->eeprom_fd);
}



// keys

void Fakeduino::keyPressed( uint32_t kc )
{
    d->pressedKeys.insert(kc);
}

void Fakeduino::keyReleased( uint32_t kc )
{
    d->pressedKeys.remove(kc);
}

bool Fakeduino::isPressed( uint32_t kc )
{
    return d->pressedKeys.contains(kc);
}




// library init

static void _fd_init() __attribute__((constructor));
static void _fd_term() __attribute__((destructor));

void _fd_init()
{
    Fakeduino::get();
}

void fakeduino_loop(void (*voidfunc)())
{
    Fakeduino::get()->exec(voidfunc);
}


void _fd_term()
{
    // TODO
    //delete _fd_instance;
}

void yield()
{
    QApplication::processEvents();
}
