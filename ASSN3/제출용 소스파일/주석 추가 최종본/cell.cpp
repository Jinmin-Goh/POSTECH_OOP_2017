#include "bio.h"
#include "cell.h"
#include "enemy.h"
#include "feed.h"
#include "virus.h"
#include "mainwindow.h"
#include <QDebug>
#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsScene>
#include <QtGui>
#include <QPainter>
#include <QList>

Cell::Cell()
{
    setSize(20);    // size 고정
    // initial position
    setX(200);
    setY(200);
    Draw();     // 생석 직후 출력
    setDirection(rand() % 4);   // random direction
    boost = false;              // defalut - no boost

    // timer 정의 및 connection 수행
    QTimer* cellMoveTimer = new QTimer();   // timer for moving
    QTimer* drainTimer = new QTimer();      // timer for draining
    QTimer* cellDrawTimer = new QTimer();   // timer for drawing
    connect(cellMoveTimer, SIGNAL(timeout()), this, SLOT(Move()));  // 50ms 마다 이동
    connect(drainTimer, SIGNAL(timeout()), this, SLOT(Drain()));    // 500ms 마다 draining
    connect(cellDrawTimer, SIGNAL(timeout()), this, SLOT(Draw()));  // 50ms 마다 화면에 출력 갱신
    cellMoveTimer->start(50);
    drainTimer->start(500);
    cellDrawTimer->start(50);
}
void Cell::Draw()
{
    // 객체의 위치, size 지정
    setRect(x(), y(), getSize(), getSize());
}

void Cell::Move()
{
    if(boost)   // boost 상태인 경우의 이동
    {
        if(getDirection() == Left)
        {
            if(x() > 0)
                setPos(x() - 3, y());
        }
        else if(getDirection() == Right)
        {
            if(x() < (800 - this->getSize()) / 2)
                setPos(x() + 3, y());
        }
        else if(getDirection() == Up)
        {
             if(y() > 0)
                setPos(x(), y() - 3);
        }
        else if(getDirection() == Down)
        {
            if(y() < (800 - this->getSize()) / 2)
                setPos(x(), y() + 3);
        }
    }
    else    // boost가 아닌 상태의 이동
    {
        if(getDirection() == Left)
        {
            if(x() > 0)
                setPos(x() - 2, y());
        }
        else if(getDirection() == Right)
        {
            if(x() < (800 - this->getSize()) / 2)
                setPos(x() + 2, y());
        }
        else if(getDirection() == Up)
        {
            if(y() > 0)
                setPos(x(), y() - 2);
        }
        else if(getDirection() == Down)
        {
            if(y() < (800 - this->getSize()) / 2)
            setPos(x(), y() + 2);
        }
    }

    // 충돌 확인
    QList<QGraphicsItem *> collided = collidingItems();

    for (int i=0; i<collided.size(); i++)
    {
        // 만일 cell의 크기가 화면을 넘어가면 게임 종료(승리)
        if(this->getSize() > 800)
        {
            MainWindow aa;
            aa.GameWin();
        }

        // 충돌 객체가 enemy인 경우
        if(typeid(*(collided[i])) == typeid(Enemy))
        {
            if(this->operator >(dynamic_cast<Bio*>(collided[i])))
            {
                // cell이 더 큰 경우 cell의 크기에 더하고 enemy 삭제
                this->operator +(dynamic_cast<Bio*>(collided[i]));
                scene()->removeItem(collided[i]);
                delete collided[i];
                return;
            }
            else
            {
                // enemy가 더 큰 경우 cell삭제 후 프로그램 종료(패배)
                scene()->removeItem(this);
                delete this;
                MainWindow aa;
                aa.GameOver();
                return;
            }
        }
        // 충돌 객체가 feed인 경우
        else if(typeid(*(collided[i])) == typeid(Feed))
        {

            // cell의 크기에 더하고 feed 삭제
            this->operator +(dynamic_cast<Bio*>(collided[i]));
            scene()->removeItem(collided[i]);
            delete collided[i];
            return;
        }
        // 충돌 객체가 virus인 경우
        else if(typeid(*(collided[i])) == typeid(Virus))
        {
            // cell의 크기에서 빼고 virus 삭제
            this->operator +(dynamic_cast<Bio*>(collided[i]));
            scene()->removeItem(collided[i]);
            delete collided[i];
            // cell size가 0 이하면 cell 삭제 후 게임 종료(패배)
            if(this->getSize() <= 0)
            {
                delete this;
                MainWindow aa;
                aa.GameOver();
            }
            return;
        }
    }
}

void Cell::Drain()
{
    // boost 상태면 size를 0.95배로 감소시킨다
    if(boost)
        setSize(getSize() * 0.95);
}

void Cell::keyPressEvent(QKeyEvent *event)
{
    // 방향키별 입력 수행
    if(event->key() == Qt::Key_Left)
        setDirection(Left);

    if(event->key() == Qt::Key_Right)
        setDirection(Right);

    if(event->key() == Qt::Key_Up)
        setDirection(Up);

    if(event->key() == Qt::Key_Down)
        setDirection(Down);
    // space 키 입력 시 boost 상태 전환
    if(event->key() == Qt::Key_Space)
        boost = !boost;
}
