#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BoatC.h"
using namespace std;

BoatC::BoatC()		//default game constructor
{
	boatCStatus = rand() % 3;

	if (boatCStatus == Sink)	//임의로 status 지정
		setVisibility(Invisible);	//가라앉은 경우 안 보이게 설정
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
	if (boatCStatus == Sink)	//가라앉아 있었던 경우
	{
		BoatC::setVisibility(Visible);	
		boatCStatus = UpOne;
	}
	else if (boatCStatus == UpOne)	//두 턴 뒤에 가라앉는 경우
	{
		boatCStatus = UpTwo;
	}
	else		//바로 뒤에 가라앉는 경우
	{
		BoatC::setVisibility(Invisible);
		boatCStatus = Sink;
	}
}