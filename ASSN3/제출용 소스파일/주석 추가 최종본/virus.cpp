#include "virus.h"
#include <QTimer>
#include <QGraphicsScene>

Virus::Virus()
{
    shrinkNum = 0;  // 생성 직후에는 shrinkNum 0
    setSize((rand() % 5) + 15);     // random size, 15 ~ 20
    // random position
    setX(rand() % (int)(400 - getSize()));
    setY(rand() % (int)(400 - getSize()));
    Draw(); // 생성 직후 draw
    setDirection(rand() % 4);       // random direciton

    // timer 정의 및 connection 수행
    QTimer* virusMoveTimer = new QTimer();  // timer for moving
    QTimer* shrinkTimer = new QTimer();     // timer for shrink
    QTimer* virusDrawTimer = new QTimer();  // timer for drawing
    connect(virusMoveTimer, SIGNAL(timeout()), this, SLOT(Move())); // 50ms 마다 이동
    connect(shrinkTimer, SIGNAL(timeout()), this, SLOT(Shrink()));  // 4초마다 shrink
    connect(virusDrawTimer, SIGNAL(timeout()), this, SLOT(Draw())); // 50ms 마다 화면에 출력 갱신
    virusMoveTimer->start(1000);
    shrinkTimer->start(4000);
    virusDrawTimer->start(50);
}

void Virus::Draw()
{
    // 객체의 위치, size 지정
    setRect(x(), y(), getSize(), getSize());
}

void Virus::Move()
{
    // direction별 이동
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
    // shrinkNum이 4인 경우 객체 소멸
    if(shrinkNum == 4)
    {
        scene()->removeItem(this);
        delete this;
        return;
    }
    // shrinkNum이 4보다 작은 경우 size 0.75배 적용 후 shrinkNum 1 증가
    setSize(getSize() * 0.75);   // change size
    shrinkNum++;
}
