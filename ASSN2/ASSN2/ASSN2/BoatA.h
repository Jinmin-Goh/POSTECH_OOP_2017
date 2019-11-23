#ifndef __BOATA_H
#define __BOATA_H
#include "Boat.h"
#include "Object.h"

class BoatA : public Boat
{
private:
	int boatAStatus;

public:
	BoatA();
	BoatA(int a, int b) : Boat(a, b)
	{
		boatAStatus = rand() % 4;
	}
	int getBoatAStatus() const;
	void setBoatAStatus(int newBoatStatus);
	void move();
	enum statusA		//현재 배의 위치와 다음의 방향까지 나타내는 status
	{
		MidLeft = 1,
		MidRight,
		Left,
		Right
	};

};

#endif