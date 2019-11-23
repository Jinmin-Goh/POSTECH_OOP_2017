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
    int direction;
    float size;
public:
    Bio();
    virtual void Draw();
    virtual void Move();
    int getDirection();
    void setDirection(int direction);
    float getSize();
    void setSize(float size);
    void operator +(Bio* bio); // + operator overloading
    bool operator >(Bio* bio); // > operator overloading
};

#endif // BIO_H
