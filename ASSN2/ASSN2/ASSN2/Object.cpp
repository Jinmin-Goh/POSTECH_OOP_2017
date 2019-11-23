#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Object.h"
using namespace std;


Object::Object()	//default 게임에 대한 constructor
{
	int xAxisLength =  5, yAxisLength = 10;

	axisX = rand() % xAxisLength;
	axisY = rand() % yAxisLength;

}
Object::Object(int a, int b)	//custom 게임에 대한 constructor
{
	int xAxisLength = a, yAxisLength = b;

	axisX = rand() % xAxisLength;
	axisY = rand() % yAxisLength;
}
void Object::moveUp()
{
	Object::axisY--;
}
void Object::moveDown()
{
	Object::axisY++;
}
void Object::moveLeft()
{
	Object::axisX--;
}
void Object::moveRight()
{
	Object::axisX++;
}
int Object::getAxisX() const
{
	return Object::axisX;
}
int Object::getAxisY() const
{
	return Object::axisY;
}
void Object::setAxisX(int const newAxisX)
{
	Object::axisX = newAxisX;
}
void Object::setAxisY(int const newAxisY)
{
	Object::axisY = newAxisY;
}
