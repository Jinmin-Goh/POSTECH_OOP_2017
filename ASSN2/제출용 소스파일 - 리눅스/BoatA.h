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
		boatAStatus = rand() % 4;	//���Ƿ� status ����
	}
	int getBoatAStatus() const;
	void setBoatAStatus(int newBoatStatus);
	void move();
	enum statusA		//���� ���� ��ġ�� ������ ������� ��Ÿ���� ���
	{
		MidLeft = 1,
		MidRight,
		Left,
		Right
	};

};

#endif