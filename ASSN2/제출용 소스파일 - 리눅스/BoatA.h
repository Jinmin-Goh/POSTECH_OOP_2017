#ifndef __BOATA_H
#define __BOATA_H
#include "Boat.h"
#include "Object.h"

class BoatA : public Boat
{
private:
	int boatAStatus;

public:
	BoatA();	//default game constructor
	BoatA(int a, int b) : Boat(a, b)	//custom game constructor
	{
		boatAStatus = rand() % 4;	//임의로 status 지정
	}
	int getBoatAStatus() const;
	void setBoatAStatus(int newBoatStatus);
	void move();
	enum statusA		//현재 배의 위치와 다음의 방향까지 나타내는 상수
	{
		MidLeft = 1,
		MidRight,
		Left,
		Right
	};

};

#endif