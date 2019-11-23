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
    // random initial position
    setX(rand() % (int)(400 - getSize()));
    setY(rand() % (int)(400 - getSize()));
    Draw();     // 초기 생성 후 위치 draw
    setDirection(rand() % 4);       // random direction

    // timer 정의 및 connection 수행
    QTimer* enemyMoveTimer = new QTimer();  // timer for moving
    QTimer* dirTimer = new QTimer();        // timer for changing direction
    QTimer* enemyDrawTimer = new QTimer();  // timer for drawing
    connect(enemyMoveTimer, SIGNAL(timeout()), this, SLOT(Move())); // 50ms 마다 이동
    connect(dirTimer, SIGNAL(timeout()), this, SLOT(ChangeDir()));  // 3초마다 방향 무작위 전환
    connect(enemyDrawTimer, SIGNAL(timeout()), this, SLOT(Draw())); // 50ms 마다 화면에 출력 갱신
    enemyMoveTimer->start(50);
    dirTimer->start(3000);
    enemyDrawTimer->start(50);
}

void Enemy::Draw()
{
    // 객체의 위치, size 지정
    setRect(x(), y(), this->getSize(), this->getSize());
}

void Enemy::Move()
{
    // direction별 이동
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

    // 충돌 확인
    QList<QGraphicsItem *> collided = collidingItems();

    for (int i=0; i<collided.size(); i++)
    {
        // 충돌 객체가 enemy인 경우
        if(typeid(*(collided[i])) == typeid(Enemy))
        {
            if(this->operator >(dynamic_cast<Bio*>(collided[i])))
            {
                // this가 더 큰 경우 this의 크기에 더하고 다른 enemy 삭제
                this->operator +(dynamic_cast<Bio*>(collided[i]));
                scene()->removeItem(collided[i]);
                delete collided[i];
                return;
            }
            else
            {
                // this가 더 작은 경우 다른 enemy의 크기에 더하고 this 삭제
                dynamic_cast<Bio*>(collided[i])->operator +(this);
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
        // 충돌 객체가 feed인 경우
        else if(typeid(*(collided[i])) == typeid(Feed))
        {
            // cell의 크기에 더하고 feed 삭제
            this->operator +(dynamic_cast<Bio*>(collided[i]));
            scene()->removeItem(collided[i]);
            delete collided[i];
            return;
        }
        // 충돌 객체가 virus인 경우
        else if(typeid(*(collided[i])) == typeid(Virus))
        {
            // this의 크기에서 빼고 virus 삭제
            this->operator +(dynamic_cast<Bio*>(collided[i]));
            scene()->removeItem(collided[i]);
            delete collided[i];
            // this size가 0 이하면 this 삭제
            if(this->getSize() <= 0)
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
    // direction을 임의로 지정
    int dir = rand() % 4;
    setDirection(dir);
}
