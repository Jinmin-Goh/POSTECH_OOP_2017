#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsEllipseItem>
//#include <QObject>
#include "bio.h"

class Enemy : public Bio
{
    Q_OBJECT

private:
    enum Direction{Up, Down, Left, Right};  // 방향을 표현하는 상수

public:
    Enemy();

public slots:
    void Move();        // virtual method의 세부 정의
    void ChangeDir();   // direction을 랜덤하게 바꾼다
    void Draw();        // virtual method의 세부 정의
};

#endif // ENEMY_H
