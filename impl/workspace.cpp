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
    ui->mdiArea->addSubWindow(qw)->show();
}
