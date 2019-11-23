#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BoatB.h"
using namespace std;

BoatB::BoatB()	//default game constructor
{
	boatBStatus = rand() % 4;	//임의로 status 지정
}

int BoatB::getBoatBStatus() const
{
	return BoatB::boatBStatus;
}
void BoatB::setBoatBStatus(int newBoatStatus)
{
	BoatB::boatBStatus = newBoatStatus;
}
void BoatB::move()	//보트의 위치에 따라서 맞는 방향으로 다음 방향으로 이동시키는 메소드
{
	if (boatBStatus == UpLeft)
	{
		BoatB::moveRight();
		boatBStatus = UpRight;
		return;
	}
	else if (boatBStatus == UpRight)
	{
		BoatB::moveDown();
		boatBStatus = DownRight;
		return;
	}
	else if (boatBStatus == DownRight)
	{
		BoatB::moveLeft();
		boatBStatus = DownLeft;
		return;
	}
	else
	{
		BoatB::moveUp();
		boatBStatus = UpLeft;
		return;
	}
}