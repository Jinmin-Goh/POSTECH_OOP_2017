#ifndef __DOUGHLIST_H
#define __DOUGHLIST_H
#include <string>
#include "Dough.h"

class DoughList
{
private:
	Dough* head ;
	int size;

public:
	DoughList();
	void add(Dough* dough);
	int del(string menuname);
	Dough* pick(string menuname);
	void show_all_menu();
	void show_most_popular();
	void search_by_thick(float hvalue, float lvalue);
};
#endif