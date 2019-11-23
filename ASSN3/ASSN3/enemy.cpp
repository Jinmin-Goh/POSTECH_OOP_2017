#include "enemy.h"
#include <QTimer>
#include <QGraphicsScene>

Enemy::Enemy()
{
    setSize((rand() % 30) + 10);    // random size, 10 ~ 40
    setRect(rand() % 800, rand() % 800, getSize(), getSize());
    setDirection(rand() % 4);       // random direction
    QTimer* moveTimer = new QTimer();   // timer for moving
    QTimer* dirTimer = new QTimer();    // timer for changing direction
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(Move()));
    connect(dirTimer, SIGNAL(timeout()), this, SLOT(ChangeDir()));
    moveTimer->start(50);
    dirTimer->start(3000);
}

void Enemy::Draw()
{

}

void Enemy::Move()
{
    if(getDirection() == Left)
        setPos(x() - 1, y());
    else if(getDirection() == Right)
        setPos(x() + 1, y());
    else if(getDirection() == Up)
        setPos(x(), y() - 1);
    else
        setPos(x(), y() + 1);
}

void Enemy::ChangeDir()
{
    int dir = rand() % 4;
    setDirection(dir);
}
