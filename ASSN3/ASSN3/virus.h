#ifndef VIRUS_H
#define VIRUS_H
#include <QGraphicsRectItem>
//#include <QObject>
#include "bio.h"

class Virus : public Bio, public QGraphicsRectItem
{
    Q_OBJECT

private:
    enum Direction{Right, Up, Left, Down};
public:
    Virus();
    void Draw();
public slots:
    void Move();
    void Shrink();
};

#endif // VIRUS_H
