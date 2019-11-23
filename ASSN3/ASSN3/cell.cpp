#include "cell.h"
#include <QDebug>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QtGui>
#include <QPainter>

Cell::Cell()
{
    setSize(20);
    setRect(400, 400, getSize(), getSize());  // player's initial position is middle
    setDirection(rand() % 4);   // random direction
    boost = false;              // defalut - no boost
    QTimer* moveTimer = new QTimer();
    QTimer* drainTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(Move()));
    connect(drainTimer, SIGNAL(timeout()), this, SLOT(Drain()));
    moveTimer->start(50);
    drainTimer->start(500);
}
void Cell::Draw()
{

}

void Cell::Move()
{
    if(boost)
    {
        if(getDirection() == Left)
            setPos(x() - 3, y());
        else if(getDirection() == Right)
            setPos(x() + 3, y());
        else if(getDirection() == Up)
            setPos(x(), y() - 3);
        else
            setPos(x(), y() + 3);
    }
    else
    {
        if(getDirection() == Left)
            setPos(x() - 2, y());
        else if(getDirection() == Right)
            setPos(x() + 2, y());
        else if(getDirection() == Up)
            setPos(x(), y() - 2);
        else
            setPos(x(), y() + 2);
    }
}

void Cell::Drain()
{
    if(boost)
        setSize(getSize());
}

void Cell::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        setDirection(Left);

    if(event->key() == Qt::Key_Right)
        setDirection(Right);

    if(event->key() == Qt::Key_Up)
        setDirection(Up);

    if(event->key() == Qt::Key_Down)
        setDirection(Down);

    if(event->key() == Qt::Key_Space)
        boost = !boost;
}
