#ifndef __TOPPINGLIST_H
#define __TOPPINGLIST_H
#include <string>
#include "Topping.h"

class ToppingList
{
private:
	Topping* head;
	int size;
	
public:
	ToppingList();
	void add(Topping* topping);
	int del(string menuname);
	Topping* pick(string menuname);
	void show_all_menu();
	void show_most_popular();
	void search_by_ingred(string ingname);
	void search_by_price(int hprice, int lprice);
};
#endif