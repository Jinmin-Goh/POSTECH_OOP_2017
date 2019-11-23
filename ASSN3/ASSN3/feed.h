#ifndef FEED_H
#define FEED_H
#include <QGraphicsRectItem>
//#include <QObject>
#include "bio.h"

class Feed : public Bio, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Feed();
    void Draw();
    void Move();
};

#endif // FEED_H
