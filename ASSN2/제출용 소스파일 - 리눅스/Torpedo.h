#ifndef __TORPEDO_H
#define __TORPEDO_H
#include "Object.h"
using namespace std;

class Torpedo : public Object
{
private:
	bool torpedoStatus;	//����� ��Ȳ(Ȱ��ȭ ����)

public:
	Torpedo();
	Torpedo(int a, int b) : Object(a, b)
	{
		torpedoStatus = Unavailable;	//�⺻������ ��ڴ� ��Ȱ��ȭ(��� ��������)
	}
	bool getTorpedoStatus();
	void setTorpedoStatus(bool newTorpedoStatus);
	void move();
	enum TorpedoStatus	//����� ��Ȳ�� �Ǵ��ϴ� ���
	{
		Unavailable = false,
		Available = true
	};
};

#endif // !__TORPEDO_H
