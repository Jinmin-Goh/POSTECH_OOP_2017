#ifndef __BOAT_H
#define __BOAT_H
#include "Object.h"

class Boat : public Object
{
private:
	bool visibility;
	bool boatStatus;
public:
	Boat();		//default game constructor
	Boat(int a, int b) : Object(a, b)	//custom game constructor
	{
		visibility = Visible;		//ó�� ������� ��Ʈ�� ���δ�
		boatStatus = Available;		//ó�� ������� ��Ʈ�� �ı����� �ʾҴ�
	}
	bool getVisibility() const;
	bool getBoatStatus() const;
	void setVisibility(bool const newVisibility);
	void setBoatStatus(bool const newBoatStatus);
	enum BoatVisibility		//��Ʈ�� ���̴��� �� ���̴����� ��Ÿ���� ���
	{
		Invisible = false,
		Visible = true
	};
	enum BoatStatus			//��Ʈ�� �ı��Ǿ������� ��Ÿ���� ���
	{
		Unavailable = false,
		Available = true
	};
};

#endif