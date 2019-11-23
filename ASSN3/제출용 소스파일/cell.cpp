#include "bio.h"
#include "cell.h"
#include "enemy.h"
#include "feed.h"
#include "virus.h"
#include "mainwindow.h"
#include <QDebug>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QtGui>
#include <QPainter>
#include <QList>

Cell::Cell()
{
    setSize(20);
    // initial position
    setX(200);
    setY(200);
    Draw();
    setDirection(rand() % 4);   // random direction
    boost = false;              // defalut - no boost

    QTimer* cellMoveTimer = new QTimer();
    QTimer* drainTimer = new QTimer();
    QTimer* cellDrawTimer = new QTimer();
    connect(cellMoveTimer, SIGNAL(timeout()), this, SLOT(Move()));
    connect(drainTimer, SIGNAL(timeout()), this, SLOT(Drain()));
    connect(cellDrawTimer, SIGNAL(timeout()), this, SLOT(Draw()));
    cellMoveTimer->start(50);
    drainTimer->start(500);
    cellDrawTimer->start(50);
}
void Cell::Draw()
{
    setRect(x(), y(), getSize(), getSize());
}

void Cell::Move()
{
    if(boost)
    {
        if(getDirection() == Left)
        {
            if(x() > 0)
                setPos(x() - 3, y());
        }
        else if(getDirection() == Right)
        {
            if(x() < (800 - this->getSize()) / 2)
                setPos(x() + 3, y());
        }
        else if(getDirection() == Up)
        {
             if(y() > 0)
                setPos(x(), y() - 3);
        }
        else if(getDirection() == Down)
        {
            if(y() < (800 - this->getSize()) / 2)
                setPos(x(), y() + 3);
        }
    }
    else
    {
        if(getDirection() == Left)
        {
            if(x() > 0)
                setPos(x() - 2, y());
        }
        else if(getDirection() == Right)
        {
            if(x() < (800 - this->getSize()) / 2)
                setPos(x() + 2, y());
        }
        else if(getDirection() == Up)
        {
            if(y() > 0)
                setPos(x(), y() - 2);
        }
        else if(getDirection() == Down)
        {
            if(y() < (800 - this->getSize()) / 2)
            setPos(x(), y() + 2);
        }
    }

    QList<QGraphicsItem *> collided = collidingItems();

    for (int i=0; i<collided.size(); i++)
    {
        if(this->getSize() > 800)
        {
            MainWindow aa;
            aa.GameWin();
        }

        if(typeid(*(collided[i])) == typeid(Enemy))
        {
            if(this->operator >(dynamic_cast<Bio*>(collided[i])))
            {
                this->operator +(dynamic_cast<Bio*>(collided[i]));
                scene()->removeItem(collided[i]);
                delete collided[i];
                return;
            }
            else
            {
                scene()->removeItem(this);
                delete this;
                MainWindow aa;
                aa.GameOver();
                return;
            }
        }
        else if(typeid(*(collided[i])) == typeid(Feed))
        {

            this->operator +(dynamic_cast<Bio*>(collided[i]));
            scene()->removeItem(collided[i]);
            delete collided[i];
            return;
        }
        else if(typeid(*(collided[i])) == typeid(Virus))
        {
            this->operator +(dynamic_cast<Bio*>(collided[i]));
            scene()->removeItem(collided[i]);
            delete collided[i];
            if(this->getSize() < 0)
            {
                delete this;
                MainWindow aa;
                aa.GameOver();
            }
            return;
        }
    }
}

void Cell::Drain()
{
    if(boost)
        setSize(getSize() * 0.95);
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
