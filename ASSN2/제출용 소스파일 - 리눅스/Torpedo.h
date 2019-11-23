#ifndef __TORPEDO_H
#define __TORPEDO_H
#include "Object.h"
using namespace std;

class Torpedo : public Object
{
private:
	bool torpedoStatus;	//어뢰의 상황(활성화 여부)

public:
	Torpedo();
	Torpedo(int a, int b) : Object(a, b)
	{
		torpedoStatus = Unavailable;	//기본적으로 어뢰는 비활성화(쏘기 전까지는)
	}
	bool getTorpedoStatus();
	void setTorpedoStatus(bool newTorpedoStatus);
	void move();
	enum TorpedoStatus	//어뢰의 상황을 판단하는 상수
	{
		Unavailable = false,
		Available = true
	};
};

#endif // !__TORPEDO_H
