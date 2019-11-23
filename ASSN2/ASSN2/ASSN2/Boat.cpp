#include <iostream>
#include <string>
#include "Boat.h"

using namespace std;

Boat::Boat()
{
	visibility = Visible;
	boatStatus = Available;
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