#ifndef __BOATC_H
#define __BOATC_H
#include "Boat.h"
#include "Object.h"

class BoatC : public Boat
{
private:
	int boatCStatus;	//가라앉았는지 여부 판단

public:
	BoatC();	//default game constructor
	BoatC(int a, int b) : Boat(a, b)	//custom game constructor
	{
		boatCStatus = rand() % 3;	//임의로 status 지정
		if (boatCStatus == Sink)	
			setVisibility(Invisible);	//가라앉은 경우 안 보이게 설정
	}
	int getBoatCStatus() const;
	void setBoatCStatus(int newBoatStatus);
	void move();
	enum statusC	//가라앉았는지 혹은 가라앉기까지 얼마나 남았는지 상황을 저장
	{
		Sink = 0,
		UpOne,
		UpTwo,	
	};
};

#endif