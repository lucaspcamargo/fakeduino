#include "serialmonitor.h"
#include "ui_serialmonitor.h"

#include <QScrollBar>

static const int LB  = 16;

SerialMonitor::SerialMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialMonitor)
{
    ui->setupUi(this);
    currSize = 0;
}

SerialMonitor::~SerialMonitor()
{
    delete ui;
}

void SerialMonitor::traffic(bool in, unsigned char b)
{
    char dir = in? '>' : '<';

    if(!(currSize && currSize < LB && currLine[0] == dir))
    {
        prevText += '\n';
        prevText += currLine;

        currSize = 0;
        currLine.fill(' ', 4*LB + 4);
        currLine[0] = dir;
    }

    char hex[3];
    snprintf(hex, 3, "%02x", (int) b);
    currLine[2+(3*currSize)] = hex[0];
    currLine[2+(3*currSize)+1] = hex[1];

    currLine[4 + 3*LB + currSize] = QChar::isPrint(b)? b : '.';

    currSize ++;
    ui->te->setPlainText(prevText + '\n' + currLine);
    auto &MyTextEdit = *ui->te;
    MyTextEdit.verticalScrollBar()->setValue(MyTextEdit.verticalScrollBar()->maximum());

}
