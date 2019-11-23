#include <iostream>
#include <string>
#include "Edge.h"
using namespace std;

Edge::Edge()	// 생성자 - 인스턴스 데이터 초기화
{
	int i;
	for (i = 0; i < 3 ; i++)
		mousse[i] = "";
	sell_count = 0;
	next = NULL;
}

void Edge::set_name(string newname)				// 문자열을 받아들여 name에 저장
{
	name = newname;
}
void Edge::add_mousse(string *newmousse)		// string 배열의 주소를 받아 해당 배열을 mousse 배열로 복사
{
	int i = 0;
	for (i = 0;i<3;i++)
	{
		if (newmousse[i] == "")
			break;
		mousse[i] = newmousse[i];
	}
}

void Edge::set_extra_cost(int newextra_cost)	// 정수형 추가금액을 받아 extra_cost에 저장
{
	extra_cost = newextra_cost;
}

void Edge::inc_sellcount()						// sell_count를 1 증가시킴
{
	sell_count++;
}

void Edge::set_comment(string newcomment)		// 문자열을 받아 comment에 저장
{
	comment = newcomment;
}

void Edge::set_pointer(Edge* newnext)			// 주소값을 입력받아 list 구현을 위한 포인터 변수인 next에 저장
{
	next = newnext;
}

// get 함수들은 전부 get 뒤에 붙은 변수의 값을 반환하는 함수이다.
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