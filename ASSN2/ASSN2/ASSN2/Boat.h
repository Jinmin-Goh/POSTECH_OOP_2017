#ifndef __BOAT_H
#define __BOAT_H
#include "Object.h"

class Boat : public Object
{
private:
	bool visibility;
	bool boatStatus;
public:
	Boat();
	Boat(int a, int b) : Object(a, b)
	{
		visibility = Visible;
		boatStatus = Available;
	}
	bool getVisibility() const;
	bool getBoatStatus() const;
	void setVisibility(bool const newVisibility);
	void setBoatStatus(bool const newBoatStatus);
	enum BoatVisibility
	{
		Invisible = false,
		Visible = true
	};
	enum BoatStatus
	{
		Unavailable = false,
		Available = true
	};
};

#endif