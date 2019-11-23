#include <iostream>
#include <string>
#include "Torpedo.h"

using namespace std;

Torpedo::Torpedo()
{
	torpedoStatus = Unavailable;
}

bool Torpedo::getTorpedoStatus()
{
	return torpedoStatus;
}
void Torpedo::setTorpedoStatus(bool newTorpedoStatus)
{
	torpedoStatus = newTorpedoStatus;
}
void Torpedo::move()
{
	Torpedo::moveUp();
}