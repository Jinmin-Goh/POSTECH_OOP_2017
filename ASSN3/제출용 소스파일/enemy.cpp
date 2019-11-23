#include "bio.h"
#include "cell.h"
#include "enemy.h"
#include "feed.h"
#include "virus.h"
#include <QTimer>
#include <QGraphicsScene>

Enemy::Enemy()
{
    setSize((rand() % 30) + 10);    // random size, 10 ~ 40
    setX(rand() % (int)(400 - getSize()));
    setY(rand() % (int)(400 - getSize()));
    Draw();
    setDirection(rand() % 4);       // random direction
    QTimer* enemyMoveTimer = new QTimer();   // timer for moving
    QTimer* dirTimer = new QTimer();    // timer for changing direction
    QTimer* enemyDrawTimer = new QTimer();
    connect(enemyMoveTimer, SIGNAL(timeout()), this, SLOT(Move()));
    connect(dirTimer, SIGNAL(timeout()), this, SLOT(ChangeDir()));
    connect(enemyDrawTimer, SIGNAL(timeout()), this, SLOT(Draw()));
    enemyMoveTimer->start(50);
    dirTimer->start(3000);
    enemyDrawTimer->start(50);
}

void Enemy::Draw()
{
    setRect(x(), y(), this->getSize(), this->getSize());
}

void Enemy::Move()
{
    if(getDirection() == Left)
    {
        if(x() > 0)
        setPos(x() - 1, y());
    }
    else if(getDirection() == Right)
    {
        if(x() < (800 - this->getSize()) / 2)
        setPos(x() + 1, y());
    }
    else if(getDirection() == Up)
    {
        if(y() > 0)
        setPos(x(), y() - 1);
    }
    else if(getDirection() == Down)
    {
        if(y() < (800 - this->getSize()) / 2)
        setPos(x(), y() + 1);
    }

    QList<QGraphicsItem *> collided = collidingItems();

    for (int i=0; i<collided.size(); i++)
    {
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
                dynamic_cast<Bio*>(collided[i])->operator +(this);

                scene()->removeItem(this);
                delete this;
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
                return;
            }
            return;
        }
    }
}

void Enemy::ChangeDir()
{
    int dir = rand() % 4;
    setDirection(dir);
}
