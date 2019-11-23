#include <iostream>
#include <string>
#include "Boat.h"

using namespace std;

Boat::Boat()	//default game constructor
{
	visibility = Visible;		//처음 만들어진 보트는 보인다
	boatStatus = Available;		//처음 만들어진 보트는 파괴되지 않았다
}

bool Boat::getBoatStatus() const
{
	return boatStatus;
}
bool Boat::getVisibility() const
{
	return Boat::visibility;
}
void Boat::setBoatStatus(bool const newBoatStatus)
{
	Boat::boatStatus = newBoatStatus;
}
void Boat::setVisibility(bool const newVisibility)
{
	Boat::visibility = newVisibility;
}