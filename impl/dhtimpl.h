#ifndef DHTIMPL_H
#define DHTIMPL_H

#include <QWidget>

namespace Ui {
class DHTImpl;
}

class DHTImpl : public QWidget
{
    Q_OBJECT

public:
    explicit DHTImpl(QWidget *parent = nullptr);
    ~DHTImpl();

    int temp();
    int hum();

private:
    Ui::DHTImpl *ui;
};

#endif // DHTIMPL_H
