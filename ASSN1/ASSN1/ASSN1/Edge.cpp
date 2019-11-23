#include <iostream>
#include <string>
#include "Edge.h"
using namespace std;

Edge::Edge()	// ������ - �ν��Ͻ� ������ �ʱ�ȭ
{
	int i;
	for (i = 0; i < 3 ; i++)
		mousse[i] = "";
	sell_count = 0;
	next = NULL;
}

void Edge::set_name(string newname)				// ���ڿ��� �޾Ƶ鿩 name�� ����
{
	name = newname;
}
void Edge::add_mousse(string *newmousse)		// string �迭�� �ּҸ� �޾� �ش� �迭�� mousse �迭�� ����
{
	int i = 0;
	for (i = 0;i<3;i++)
	{
		if (newmousse[i] == "")
			break;
		mousse[i] = newmousse[i];
	}
}

void Edge::set_extra_cost(int newextra_cost)	// ������ �߰��ݾ��� �޾� extra_cost�� ����
{
	extra_cost = newextra_cost;
}

void Edge::inc_sellcount()						// sell_count�� 1 ������Ŵ
{
	sell_count++;
}

void Edge::set_comment(string newcomment)		// ���ڿ��� �޾� comment�� ����
{
	comment = newcomment;
}

void Edge::set_pointer(Edge* newnext)			// �ּҰ��� �Է¹޾� list ������ ���� ������ ������ next�� ����
{
	next = newnext;
}

// get �Լ����� ���� get �ڿ� ���� ������ ���� ��ȯ�ϴ� �Լ��̴�.
string Edge::get_name()
{
	return name;
}

string* Edge::get_mousse()
{
	return mousse;
}

int Edge::get_extra_cost()
{
	return extra_cost;
}

int Edge::get_sell_count()
{
	return sell_count;
}

string Edge::get_comment()
{
	return comment;
}

Edge* Edge::get_pointer()
{
	return next;
}