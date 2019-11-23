#include <iostream>
#include <string>
#include "Torpedo.h"

using namespace std;

Torpedo::Torpedo()
{
	torpedoStatus = Unavailable;	//기본적으로 어뢰는 비활성화(쏘기 전까지는)
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