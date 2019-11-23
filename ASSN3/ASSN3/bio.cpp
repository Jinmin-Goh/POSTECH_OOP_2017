#include "bio.h"

Bio::Bio()
{

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
