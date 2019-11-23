#ifndef __BOATC_H
#define __BOATC_H
#include "Boat.h"
#include "Object.h"

class BoatC : public Boat
{
private:
	int boatCStatus;

public:
	BoatC();
	BoatC(int a, int b) : Boat(a, b)
	{
		boatCStatus = rand() % 3;
		if (boatCStatus == Sink)
			setVisibility(Invisible);
	}
	int getBoatCStatus() const;
	void setBoatCStatus(int newBoatStatus);
	void move();
	enum statusC
	{
		Sink = 0,
		UpOne,
		UpTwo,	
	};
};

#endif