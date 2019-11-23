#ifndef BIO_H
#define BIO_H
#include <QGraphicsRectItem>
#include <QObject>
#include <iostream>
#include <QtGui>

class Bio :  public QObject, public QPainter
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
};

#endif // BIO_H
