#ifndef __BOATB_H
#define __BOATB_H
#include "Boat.h"
#include "Object.h"

class BoatB : public Boat
{
private:
	int boatBStatus;	//보트의 위치를 저장하는 변수

public:
	BoatB();	//default game constructor
	BoatB(int a, int b) : Boat(a, b)	//custom game constructor
	{
		boatBStatus = rand() % 4;	//임의로 status 지정
	}
	int getBoatBStatus() const;
	void setBoatBStatus(int newBoatStatus);
	void move();
	enum statusB	//보트의 위치(이동 방향)를 나타내는 상수
	{
		UpLeft = 1,
		UpRight,
		DownRight,
		DownLeft
	};
};

#endif