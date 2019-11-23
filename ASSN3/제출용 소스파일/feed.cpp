#include "feed.h"
#include <QGraphicsScene>

Feed::Feed()
{
    setDirection(0);    // fixed direction - no matter
    setSize((rand() % 5) + 7);    // random size, 10 ~ 40
    setRect(rand() % (int)(800 - getSize()), rand() % (int)(800 - getSize()), getSize(), getSize());
}

void Feed::Draw()
{

}

void Feed::Move()
{
    return;
}
