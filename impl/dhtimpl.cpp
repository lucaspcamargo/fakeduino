#include "dhtimpl.h"
#include "ui_dhtimpl.h"

DHTImpl::DHTImpl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DHTImpl)
{
    ui->setupUi(this);
}

DHTImpl::~DHTImpl()
{
    delete ui;
}

int DHTImpl::temp() {return ui->tempSlider->value();}

int DHTImpl::hum() {return ui->humSlider->value();}
