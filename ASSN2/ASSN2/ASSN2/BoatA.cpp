#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BoatA.h"
using namespace std;

BoatA::BoatA()
{
	boatAStatus = rand() % 4;
}

int BoatA::getBoatAStatus() const
{
	return BoatA::boatAStatus;
}
void BoatA::setBoatAStatus(int newBoatStatus)
{
	BoatA::boatAStatus = newBoatStatus;
}
void BoatA::move()
{
	if (boatAStatus == Left)		//ÇöÀç ¸Ç ¿ÞÂÊ
	{
		BoatA::moveRight();
		boatAStatus = MidRight;
		return;
	}
	else if (boatAStatus == MidRight)
	{
		BoatA::moveRight();
		boatAStatus = Right;
		return;
	}
	else if (boatAStatus == Right)
	{
		BoatA::moveLeft();
		boatAStatus = MidLeft;
		return;
	}
	else
	{
		BoatA::moveLeft();
		boatAStatus = Left;
		return;
	}
}