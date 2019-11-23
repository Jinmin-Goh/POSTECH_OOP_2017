#ifndef BIO_H
#define BIO_H
#include <QGraphicsRectItem>
#include <QObject>
#include <iostream>
#include <QtGui>


class Bio :  public QObject, public QGraphicsRectItem//, public QGraphicsEllipseItem//, public QPainter
{
    Q_OBJECT

private:
    int direction;      // 객체의 방향 저장
    float size;         // 객체의 크기 저장
public:
    Bio();
    virtual void Draw() = 0;        // 하위 메소드에서 정의할 pure virtual method
    virtual void Move() = 0;        // 하위 메소드에서 정의할 pure virtual method
    int getDirection();
    void setDirection(int direction);
    float getSize();
    void setSize(float size);
    void operator +(Bio* bio);  // + operator overloading, bio 객체의 size를 더하거나 다.
    bool operator >(Bio* bio);  // > operator overloading, bio 객체의 size를 비교
};

#endif // BIO_H
