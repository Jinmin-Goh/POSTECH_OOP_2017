#ifndef __BOATC_H
#define __BOATC_H
#include "Boat.h"
#include "Object.h"

class BoatC : public Boat
{
private:
	int boatCStatus;	//����ɾҴ��� ���� �Ǵ�

public:
	BoatC();	//default game constructor
	BoatC(int a, int b) : Boat(a, b)	//custom game constructor
	{
		boatCStatus = rand() % 3;	//���Ƿ� status ����
		if (boatCStatus == Sink)	
			setVisibility(Invisible);	//������� ��� �� ���̰� ����
	}
	int getBoatCStatus() const;
	void setBoatCStatus(int newBoatStatus);
	void move();
	enum statusC	//����ɾҴ��� Ȥ�� ����ɱ���� �󸶳� ���Ҵ��� ��Ȳ�� ����
	{
		Sink = 0,
		UpOne,
		UpTwo,	
	};
};

#endif