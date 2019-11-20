#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QWidget>

namespace Ui {
class SerialMonitor;
}

class SerialMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit SerialMonitor(QWidget *parent = nullptr);
    ~SerialMonitor();

    void traffic(bool in, unsigned char b);

private:
    Ui::SerialMonitor *ui;
    QString currLine;
    QString prevText;
    int currSize;
};

#endif // SERIALMONITOR_H
