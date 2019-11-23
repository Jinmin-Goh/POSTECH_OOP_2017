#include <iostream>
#include <string>
#include "Topping.h"
using namespace std;

Topping::Topping()		// 생성자 - 인스턴스 데이터 초기화
{
	int i;
	for (i = 0; i < 10; i++)
		ingredient[i] = "";
	next = NULL;
	sell_count = 0;
}

void Topping::set_name(string newname)				// 문자열을 받아들여 name에 저장
{
	name = newname;
}
void Topping::add_ingredient(string* newingredient)	// string 배열의 주소를 받아 해당 배열을 ingredient 배열로 복사
{
	int i = 0;
	for (i = 0; i<10; i++)
	{
		if (newingredient[i] == "")
			break;
		ingredient[i] = newingredient[i];
	}
}
void Topping::set_price(int newprice)				// 정수형 금액을 받아 price에 저장
{
	price = newprice;
}
		
void Topping::inc_sellcount()						// sell_count를 1 증가시킴
{
	sell_count++;
}

void Topping::set_comment(string newcomment)		// 문자열을 받아 comment에 저장
{
	comment = newcomment;
}

void Topping::set_pointer(Topping* newnext)			// 주소값을 입력받아 list 구현을 위한 포인터 변수인 next에 저장
{
	next = newnext;
}


// get 함수들은 전부 get 뒤에 붙은 변수의 값을 반환하는 함수이다.
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