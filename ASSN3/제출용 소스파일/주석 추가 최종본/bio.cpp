#include <iostream>
#include <QDebug>
#include "bio.h"
#include "cell.h"
#include "enemy.h"
#include "feed.h"
#include "virus.h"
using namespace std;

Bio::Bio()
{

}

void Bio::operator +(Bio* bio)      // + operator overloading
{
    // feed인 경우 feed의 size만큼 더한다
    if(typeid(*bio) == typeid(Feed))
    {
        this->size = this->size + bio->getSize();
    }
    // enemy인 경우 enemy의 size만큼 더한다
    else if(typeid(*bio) == typeid(Enemy))
    {
        this->size = this->size + bio->getSize();
    }
    // virus인 경우 virus의 size의 0.8배만큼 더한다
    else if(typeid(*bio) == typeid(Virus))
    {
        this->size = this->size - (bio->getSize()) * 0.8;
    }
}

bool Bio::operator >(Bio* bio)
{
    // bio 객체와의 size를 비교해 this의 size가 더 크면 true, 같거나 작으면 false를 반환
    if((this->size) > (bio->getSize()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Bio::getDirection()
{
    return this->direction;
}
void Bio::setDirection(int direction)
{
    this->direction = direction;
}

float Bio::getSize()
{
    return this->size;
}

void Bio::setSize(float size)
{
    this->size = size;
}
