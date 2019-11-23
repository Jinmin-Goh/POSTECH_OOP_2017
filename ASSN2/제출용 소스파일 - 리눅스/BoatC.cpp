#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BoatC.h"
using namespace std;

BoatC::BoatC()		//default game constructor
{
	boatCStatus = rand() % 3;

	if (boatCStatus == Sink)	//���Ƿ� status ����
		setVisibility(Invisible);	//������� ��� �� ���̰� ����
}

int BoatC::getBoatCStatus() const
{
	return BoatC::boatCStatus;
}
void BoatC::setBoatCStatus(int newBoatStatus)
{
	BoatC::boatCStatus = newBoatStatus;
}
void BoatC::move()
{
	if (boatCStatus == Sink)	//����ɾ� �־��� ���
	{
		BoatC::setVisibility(Visible);	
		boatCStatus = UpOne;
	}
	else if (boatCStatus == UpOne)	//�� �� �ڿ� ����ɴ� ���
	{
		boatCStatus = UpTwo;
	}
	else		//�ٷ� �ڿ� ����ɴ� ���
	{
		BoatC::setVisibility(Invisible);
		boatCStatus = Sink;
	}
}