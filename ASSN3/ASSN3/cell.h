#ifndef CELL_H
#define CELL_H
#include <QGraphicsEllipseItem>
//#include <QObject>
#include "bio.h"

class Cell : public Bio, public QGraphicsEllipseItem
{
    Q_OBJECT

private:
    enum Direction{Up, Down, Left, Right};
    bool boost;
public:
    Cell();
    void Draw();

    void keyPressEvent(QKeyEvent *event);

public slots:
    void Move();
    void Drain();

};

#endif // CELL_H
