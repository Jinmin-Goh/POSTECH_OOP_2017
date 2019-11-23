#ifndef VIRUS_H
#define VIRUS_H
#include <QGraphicsRectItem>
//#include <QObject>
#include "bio.h"

class Virus : public Bio
{
    Q_OBJECT

private:
    enum Direction{Right, Up, Left, Down};  // 방향을 표현하는 상수
    int shrinkNum;  // 4가 되면 인스턴스 소멸. 처음에는 0이고 크기가 줄을 때마다 1씩 증가
public:
    Virus();

public slots:
    void Move();    // virtual method의 세부 정의
    void Shrink();  // 객체의 크기를 줄이는 메소드
    void Draw();    // virtual method의 세부 정의
};

#endif // VIRUS_H
