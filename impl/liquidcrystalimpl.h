#ifndef LIQUIDCRYSTALIMPL_H
#define LIQUIDCRYSTALIMPL_H

#include <QWidget>
#include <QMap>
#include <QQueue>
#include <QMouseEvent>

namespace Ui {
class LiquidCrystalImpl;
}

class LiquidCrystalImpl : public QWidget
{
    Q_OBJECT

public:
    explicit LiquidCrystalImpl(QWidget *parent = nullptr);
    ~LiquidCrystalImpl();

    void begin(int cols, int lines);

    void put( char c );
    void puts( const char *str );
    void gotoxy( int col, int line );
    void clear();

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override
    {
        setFocus(Qt::MouseFocusReason);
        event->accept();
    };

private:
    void updateScreen();

    Ui::LiquidCrystalImpl *ui;

    int numCols;
    int numLines;

    int currCol;
    int currLine;

    QStringList lines;
    QMap< char, QChar > substTable;

};

#endif // LIQUIDCRYSTALIMPL_H
