#ifndef CELL_H
#define CELL_H
#include <QGraphicsEllipseItem>
//#include <QObject>
#include "bio.h"

class Cell : public Bio
{
    Q_OBJECT

private:
    enum Direction{Up, Down, Left, Right};  // 방향을 표현하는 상수
    bool boost;         // boost 상태를 표시
public:
    Cell();

    void keyPressEvent(QKeyEvent *event);   // 키 입력을 받아 인식하는 함수

public slots:
    void Draw();    // virtual method의 세부 정의
    void Move();    // virtual method의 세부 정의
    void Drain();   // boost 상태에서 size 감

};

#endif // CELL_H
