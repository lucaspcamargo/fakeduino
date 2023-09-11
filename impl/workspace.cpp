#include "workspace.h"
#include "ui_workspace.h"

#include "QMdiSubWindow"

Workspace::Workspace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Workspace)
{
    ui->setupUi(this);
}

Workspace::~Workspace()
{
    delete ui;
}

void Workspace::showGadget(QWidget *qw)
{
    auto sw = ui->mdiArea->addSubWindow(qw);
    sw->show();
    sw->setFocus(Qt::OtherFocusReason);
}

void Workspace::showStatus(QString status)
{
    ui->statusbar->showMessage(status, 5000);
}
