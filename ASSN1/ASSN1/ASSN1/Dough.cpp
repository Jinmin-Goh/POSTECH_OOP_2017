#include <iostream>
#include <string>
#include "Dough.h"
using namespace std;

Dough::Dough()	// 생성자 - 데이터 초기화
{
	sell_count = 0;
	next = NULL;
}
void Dough::set_name(string newname)			// 이름을 받아들여 name에 저장
{
	name = newname;
}
void Dough::set_thickness(float newthickness)	// float형 두께를 받아 thickness에 저장
{
	thickness = newthickness;
}

void Dough::set_extra_cost(int newextra_cost)	// 정수형 추가금액을 받아 extra_cost에 저장
{
	extra_cost = newextra_cost;
}

void Dough::inc_sellcount()						// sell_count를 1 증가시킴
{
	sell_count++;
}
	
void Dough::set_comment(string newcomment)		// 문자열을 받아 comment에 저장
{
	comment = newcomment;
}

void Dough::set_pointer(Dough* newnext)			// 주소값을 입력받아 list 구현을 위한 포인터 변수인 next에 저장
{
	next = newnext;
}

// get 함수들은 전부 get 뒤에 붙은 변수의 값을 반환하는 함수이다.
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
