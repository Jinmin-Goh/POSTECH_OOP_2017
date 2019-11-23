#ifndef __EDGELIST_H
#define __EDGELIST_H
#include <string>
#include "Edge.h"

class EdgeList
{
private:
	Edge* head;
	int size;

public:
	EdgeList();
	void add(Edge* edge);
	int del(string menuname);
	Edge* pick(string menuname);
	void show_all_menu();
	void show_most_popular();
	void search_by_mousse(string moussename);
};
#endif