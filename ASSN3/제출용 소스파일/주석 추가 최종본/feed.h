#ifndef FEED_H
#define FEED_H
#include <QGraphicsRectItem>
//#include <QObject>
#include "bio.h"

class Feed : public Bio
{
    Q_OBJECT

public:
    Feed();
    void Draw();    // virtual method의 세부 정의
    void Move();    // virtual method의 세부 정의
};

#endif // FEED_H
