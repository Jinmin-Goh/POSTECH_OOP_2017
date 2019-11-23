#include "feed.h"
#include <QGraphicsScene>

Feed::Feed()
{
    setDirection(0);    // fixed direction - no matter
    setSize((rand() % 5) + 7);    // random size, 10 ~ 40
    // 처음 한 번만 출력
    setRect(rand() % (int)(800 - getSize()), rand() % (int)(800 - getSize()), getSize(), getSize());
}

// feed는 따로 움직이지 않으므로 충돌해 사라지기 전까지 아무런 작업을 수행하지 않는다
void Feed::Draw()
{
    return;
}

void Feed::Move()
{
    return;
}
