#ifndef __BOATB_H
#define __BOATB_H
#include "Boat.h"
#include "Object.h"

class BoatB : public Boat
{
private:
	int boatBStatus;

public:
	BoatB();
	BoatB(int a, int b) : Boat(a, b)
	{
		boatBStatus = rand() % 4;
	}
	int getBoatBStatus() const;
	void setBoatBStatus(int newBoatStatus);
	void move();
	enum statusB
	{
		UpLeft = 1,
		UpRight,
		DownRight,
		DownLeft
	};
};

#endif