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
		visibility = Visible;		//처음 만들어진 보트는 보인다
		boatStatus = Available;		//처음 만들어진 보트는 파괴되지 않았다
	}
	bool getVisibility() const;
	bool getBoatStatus() const;
	void setVisibility(bool const newVisibility);
	void setBoatStatus(bool const newBoatStatus);
	enum BoatVisibility		//보트가 보이는지 안 보이는지를 나타내는 상수
	{
		Invisible = false,
		Visible = true
	};
	enum BoatStatus			//보트가 파괴되었는지를 나타내는 상수
	{
		Unavailable = false,
		Available = true
	};
};

#endif