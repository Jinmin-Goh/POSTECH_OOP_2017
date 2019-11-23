#include "virus.h"
#include <QTimer>
#include <QGraphicsScene>

Virus::Virus()
{
    shrinkNum = 0;
    setSize((rand() % 5) + 15);     // random size, 15 ~ 20
    setX(rand() % (int)(400 - getSize()));
    setY(rand() % (int)(400 - getSize()));
    Draw();
    setDirection(rand() % 4);       // random direciton
    QTimer* virusMoveTimer = new QTimer();   // timer for moving
    QTimer* shrinkTimer = new QTimer(); // timer for shrink
    QTimer* virusDrawTimer = new QTimer();
    connect(virusMoveTimer, SIGNAL(timeout()), this, SLOT(Move()));
    connect(shrinkTimer, SIGNAL(timeout()), this, SLOT(Shrink()));
    connect(virusDrawTimer, SIGNAL(timeout()), this, SLOT(Draw()));
    virusMoveTimer->start(1000);
    shrinkTimer->start(4000);
    virusDrawTimer->start(50);
}

void Virus::Draw()
{
    setRect(x(), y(), getSize(), getSize());
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
    if(shrinkNum == 4)
    {
        scene()->removeItem(this);
        delete this;
        return;
    }
    setSize(getSize() * 0.75);   // change size
    shrinkNum++;
}
