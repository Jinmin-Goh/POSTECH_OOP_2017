#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "BoatC.h"
using namespace std;

BoatC::BoatC()
{
	boatCStatus = rand() % 3;

	if (boatCStatus == Sink)
		setVisibility(Invisible);
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
	if (boatCStatus == Sink)
	{
		BoatC::setVisibility(Visible);
		boatCStatus = UpOne;
	}
	else if (boatCStatus == UpOne)
	{
		boatCStatus = UpTwo;
	}
	else
	{
		BoatC::setVisibility(Invisible);
		boatCStatus = Sink;
	}
}