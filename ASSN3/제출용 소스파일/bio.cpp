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

void Bio::operator +(Bio* bio)
{
    if(typeid(*bio) == typeid(Feed))
    {
        this->size = this->size + bio->getSize();
    }
    else if(typeid(*bio) == typeid(Enemy))
    {
        this->size = this->size + bio->getSize();
    }
    else if(typeid(*bio) == typeid(Virus))
    {
        this->size = this->size - (bio->getSize()) * 0.8;
    }
}

bool Bio::operator >(Bio* bio)
{
    if((this->size) > (bio->getSize()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Bio::Draw()
{

}
void Bio::Move()
{

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
