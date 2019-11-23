#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsEllipseItem>
//#include <QObject>
#include "bio.h"

class Enemy : public Bio, public QGraphicsEllipseItem
{
    Q_OBJECT

private:
    enum Direction{Up, Down, Left, Right};

public:
    Enemy();
    void Draw();

public slots:
    void Move();
    void ChangeDir();

};

#endif // ENEMY_H
