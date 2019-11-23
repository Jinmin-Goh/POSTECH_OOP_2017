#include <iostream>
#include <string>
#include "Dough.h"
using namespace std;

Dough::Dough()	// ������ - ������ �ʱ�ȭ
{
	sell_count = 0;
	next = NULL;
}
void Dough::set_name(string newname)			// �̸��� �޾Ƶ鿩 name�� ����
{
	name = newname;
}
void Dough::set_thickness(float newthickness)	// float�� �β��� �޾� thickness�� ����
{
	thickness = newthickness;
}

void Dough::set_extra_cost(int newextra_cost)	// ������ �߰��ݾ��� �޾� extra_cost�� ����
{
	extra_cost = newextra_cost;
}

void Dough::inc_sellcount()						// sell_count�� 1 ������Ŵ
{
	sell_count++;
}
	
void Dough::set_comment(string newcomment)		// ���ڿ��� �޾� comment�� ����
{
	comment = newcomment;
}

void Dough::set_pointer(Dough* newnext)			// �ּҰ��� �Է¹޾� list ������ ���� ������ ������ next�� ����
{
	next = newnext;
}

// get �Լ����� ���� get �ڿ� ���� ������ ���� ��ȯ�ϴ� �Լ��̴�.
string Dough::get_name()
{
	return name;
}

float Dough::get_thickness()
{
	return thickness;
}

int Dough::get_extra_cost()
{
	return extra_cost;
}

int Dough::get_sell_count()
{
	return sell_count;
}

string Dough::get_comment()
{
	return comment;
}

Dough* Dough::get_pointer()
{
	return next;
}
