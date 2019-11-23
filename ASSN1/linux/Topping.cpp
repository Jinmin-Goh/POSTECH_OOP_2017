#include <iostream>
#include <string>
#include "Topping.h"
using namespace std;

Topping::Topping()		// ������ - �ν��Ͻ� ������ �ʱ�ȭ
{
	int i;
	for (i = 0; i < 10; i++)
		ingredient[i] = "";
	next = NULL;
	sell_count = 0;
}

void Topping::set_name(string newname)				// ���ڿ��� �޾Ƶ鿩 name�� ����
{
	name = newname;
}
void Topping::add_ingredient(string* newingredient)	// string �迭�� �ּҸ� �޾� �ش� �迭�� ingredient �迭�� ����
{
	int i = 0;
	for (i = 0; i<10; i++)
	{
		if (newingredient[i] == "")
			break;
		ingredient[i] = newingredient[i];
	}
}
void Topping::set_price(int newprice)				// ������ �ݾ��� �޾� price�� ����
{
	price = newprice;
}
		
void Topping::inc_sellcount()						// sell_count�� 1 ������Ŵ
{
	sell_count++;
}

void Topping::set_comment(string newcomment)		// ���ڿ��� �޾� comment�� ����
{
	comment = newcomment;
}

void Topping::set_pointer(Topping* newnext)			// �ּҰ��� �Է¹޾� list ������ ���� ������ ������ next�� ����
{
	next = newnext;
}


// get �Լ����� ���� get �ڿ� ���� ������ ���� ��ȯ�ϴ� �Լ��̴�.
string Topping::get_name()
{
	return name;
}

string* Topping::get_ingredient()
{
	return ingredient;
}

int Topping::get_price()
{
	return price;
}

int Topping::get_sell_count()
{
	return sell_count;
}

string Topping::get_comment()
{
	return comment;
}

Topping* Topping::get_pointer()
{
	return next;
}