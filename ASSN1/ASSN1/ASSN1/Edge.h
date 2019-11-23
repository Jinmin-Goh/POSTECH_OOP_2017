#ifndef __EDGE_H
#define __EDGE_H
#include <string>
using namespace std;

class Edge
{
private:
	string name, mousse[3], comment;
	int sell_count, extra_cost;
	Edge *next;

public:
	Edge();
	void set_name(string newname);
	void add_mousse(string *newmousse);
	void set_extra_cost(int newextra_cost);
	void inc_sellcount();
	void set_comment(string newcomment);
	void set_pointer(Edge* newnext);

	string get_name();
	string* get_mousse();
	int get_extra_cost();
	int get_sell_count();
	string get_comment();
	Edge* get_pointer();
};
#endif