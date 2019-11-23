#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BoatB.h"
using namespace std;

BoatB::BoatB()	//default game constructor
{
	boatBStatus = rand() % 4;	//���Ƿ� status ����
}

int BoatB::getBoatBStatus() const
{
	return BoatB::boatBStatus;
}
void BoatB::setBoatBStatus(int newBoatStatus)
{
	BoatB::boatBStatus = newBoatStatus;
}
void BoatB::move()	//��Ʈ�� ��ġ�� ���� �´� �������� ���� �������� �̵���Ű�� �޼ҵ�
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