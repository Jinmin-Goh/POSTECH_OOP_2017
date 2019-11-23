#ifndef __TOPPING_H
#define __TOPPING_H
#include <string>
using namespace std;

class Topping
{
private:
	string name, ingredient[10], comment;
	int price, sell_count;
	Topping *next;

public:
	Topping();
	void set_name(string newname);
	void add_ingredient(string* newingredient);
	void set_price(int newprice);
	void inc_sellcount();
	void set_comment(string newcomment);
	void set_pointer(Topping* newnext);
	
	string get_name();
	string* get_ingredient();
	int get_price();
	int get_sell_count();
	string get_comment();
	Topping* get_pointer();
};
#endif