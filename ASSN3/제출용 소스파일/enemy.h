#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsEllipseItem>
//#include <QObject>
#include "bio.h"

class Enemy : public Bio
{
    Q_OBJECT

private:
    enum Direction{Up, Down, Left, Right};

public:
    Enemy();

public slots:
    void Move();
    void ChangeDir();
    void Draw();
};

#endif // ENEMY_H
