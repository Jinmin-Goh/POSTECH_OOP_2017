#ifndef __BOATB_H
#define __BOATB_H
#include "Boat.h"
#include "Object.h"

class BoatB : public Boat
{
private:
	int boatBStatus;	//��Ʈ�� ��ġ�� �����ϴ� ����

public:
	BoatB();	//default game constructor
	BoatB(int a, int b) : Boat(a, b)	//custom game constructor
	{
		boatBStatus = rand() % 4;	//���Ƿ� status ����
	}
	int getBoatBStatus() const;
	void setBoatBStatus(int newBoatStatus);
	void move();
	enum statusB	//��Ʈ�� ��ġ(�̵� ����)�� ��Ÿ���� ���
	{
		UpLeft = 1,
		UpRight,
		DownRight,
		DownLeft
	};
};

#endif