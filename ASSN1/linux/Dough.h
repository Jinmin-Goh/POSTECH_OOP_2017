#ifndef __DOUGH_H
#define __DOUGH_H
#include <string>
using namespace std;


class Dough
{
private:
	string name, comment;
	int sell_count, extra_cost;
	float thickness;
	Dough *next;

public:
	Dough();
	void set_name(string newname);
	void set_thickness(float newthickness);
	void set_extra_cost(int newextra_cost);
	void inc_sellcount();
	void set_comment(string newcomment);
	void set_pointer(Dough *newnext);

	string get_name();
	float get_thickness();
	int get_extra_cost();
	int get_sell_count();
	string get_comment();
	Dough* get_pointer();
};
#endif