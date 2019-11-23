#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BoatA.h"
using namespace std;

BoatA::BoatA()	//default game constructor
{
	boatAStatus = rand() % 4;	//임의로 status 지정
}

int BoatA::getBoatAStatus() const
{
	return BoatA::boatAStatus;
}
void BoatA::setBoatAStatus(int newBoatStatus)
{
	BoatA::boatAStatus = newBoatStatus;
}
void BoatA::move()	//보트의 위치에 따라서 맞는 방향으로 다음 방향으로 이동시키는 메소드
{
	if (boatAStatus == Left)	
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