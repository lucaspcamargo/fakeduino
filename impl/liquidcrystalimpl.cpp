#include "liquidcrystalimpl.h"
#include "ui_liquidcrystalimpl.h"

#include <QKeyEvent>
#include "fakeduino.h"

LiquidCrystalImpl::LiquidCrystalImpl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiquidCrystalImpl)
{
    ui->setupUi(this);

    begin(16, 2);

    substTable[static_cast<char>(0xdf)] = QChar{u'°'};
    substTable[0] = QChar{L'☎'};
    substTable[1] = QChar{L'☏'};
    substTable[2] = QChar{L'⛒'};
    substTable[3] = QChar{u'⏰'};
    substTable[4] = QChar{u'⛭'};
    substTable[5] = QChar{u'⚬'};
}

LiquidCrystalImpl::~LiquidCrystalImpl()
{
    delete ui;
}

void LiquidCrystalImpl::begin(int cols, int lines)
{
    numCols = cols;
    numLines = lines;
    currCol = 0;
    currLine = 0;

    clear();
}

void LiquidCrystalImpl::put( char c )
{
    QChar qc = substTable.contains(c)? substTable[c] : QChar{c};

    lines[currLine][currCol] = qc;
    if((++currCol) == numCols)
    {
        currCol = 0;
        currLine = (currLine + 1) % numLines;
    }

    updateScreen();
}

void LiquidCrystalImpl::puts( const char *str )
{
    while(*str)
    {
        put(*str);
        ++str;
    }
}

void LiquidCrystalImpl::gotoxy( int col, int line )
{
    currCol = col % numCols;
    currLine = line % numLines;
}

void LiquidCrystalImpl::clear()
{
    lines.clear();
    for(int i = 0; i < numLines; i++)
    {
        QString blank;
        blank.fill(' ', numCols);
        lines.append(blank);
    }

    updateScreen();
}

void LiquidCrystalImpl::updateScreen()
{
    QString all;
    for( auto l: lines )
    {
        all += l;
        all += '\n';
    }

    all.chop(1); // remove last \n

    ui->label->setText(all);
    QApplication::processEvents();
}


void LiquidCrystalImpl::keyPressEvent(QKeyEvent *event)
{
    Fakeduino::get()->keyPressed(event->key());
    event->accept();
}

void LiquidCrystalImpl::keyReleaseEvent(QKeyEvent *event)
{
    Fakeduino::get()->keyReleased(event->key());
    event->accept();
}
