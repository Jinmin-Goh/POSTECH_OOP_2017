#ifndef VIRUS_H
#define VIRUS_H
#include <QGraphicsRectItem>
//#include <QObject>
#include "bio.h"

class Virus : public Bio
{
    Q_OBJECT

private:
    enum Direction{Right, Up, Left, Down};
    int shrinkNum;
public:
    Virus();

public slots:
    void Move();
    void Shrink();
    void Draw();
};

#endif // VIRUS_H
