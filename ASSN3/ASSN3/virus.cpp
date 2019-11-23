#include "virus.h"
#include <QTimer>
#include <QGraphicsScene>

Virus::Virus()
{
    setSize((rand() % 5) + 15);     // random size, 15 ~ 20
    setRect(rand() % 800, rand() % 800, getSize(), getSize());
    setDirection(rand() % 4);       // random direciton
    QTimer* moveTimer = new QTimer();   // timer for moving
    QTimer* shrinkTimer = new QTimer(); // timer for shrink
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(Move()));
    connect(shrinkTimer, SIGNAL(timeout()), this, SLOT(Shrink()));
    moveTimer->start(50);
    shrinkTimer->start(1000);
}

void Virus::Draw()
{

}

void Virus::Move()
{
    if(getDirection() == Left)
        setPos(x() - 20, y());
    else if(getDirection() == Right)
        setPos(x() + 20, y());
    else if(getDirection() == Up)
        setPos(x(), y() - 20);
    else
        setPos(x(), y() + 20);

    setDirection((getDirection() + 1) % 4); // change direction to next direction
}

void Virus::Shrink()
{
    setSize(getSize() * 0.75);   // change size
}
