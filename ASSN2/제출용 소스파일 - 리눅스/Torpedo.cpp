#include <iostream>
#include <string>
#include "Torpedo.h"

using namespace std;

Torpedo::Torpedo()
{
	torpedoStatus = Unavailable;	//�⺻������ ��ڴ� ��Ȱ��ȭ(��� ��������)
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