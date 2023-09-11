#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QMainWindow>

namespace Ui {
class Workspace;
}

class Workspace : public QMainWindow
{
    Q_OBJECT

public:
    explicit Workspace(QWidget *parent = nullptr);
    ~Workspace();

    void showGadget( QWidget * qw );
    void showStatus( QString status );

    Ui::Workspace *ui;
private:
};

#endif // WORKSPACE_H
