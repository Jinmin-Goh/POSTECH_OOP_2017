#ifndef CELL_H
#define CELL_H
#include <QGraphicsEllipseItem>
//#include <QObject>
#include "bio.h"

class Cell : public Bio
{
    Q_OBJECT

private:
    enum Direction{Up, Down, Left, Right};
    bool boost;
public:
    Cell();

    void keyPressEvent(QKeyEvent *event);

public slots:
    void Draw();
    void Move();
    void Drain();

};

#endif // CELL_H
