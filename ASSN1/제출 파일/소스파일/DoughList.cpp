#include <iostream>
#include <string>
#include "DoughList.h"
using namespace std;

DoughList::DoughList()	// 생성자 - 데이터 초기화
{
	head = NULL;
	size = 0;
}

void DoughList::add(Dough* dough)	// 인스턴스 주소를 입력받아 list에 인스턴스 node를 추가하는 함수
{
	Dough *pNew, *pEnd;
	pNew = dough;
	pEnd = head;
	if (head == NULL)		// list가 비어있는 경우에 바로 추가
	{
		head = dough;
	}
	else					// 그 외의 경우
	{
		while (pEnd->get_pointer() != NULL)
		{
			pEnd = pEnd->get_pointer();
		}
		pEnd->set_pointer(pNew);	// list 마지막에 dough 객체를 link
	}
	size++;
	
}

int DoughList::del(string menuname) // 메뉴가 있으면 삭제 후 1 반환, 없으면 그냥 0 반환
{
	Dough *pPre, *pCur;

	if (head == NULL)	// 메뉴가 비어있는 경우
		return 0;
	else if (head->get_name() == menuname)	// 메뉴가 처음과 일치하는 경우
	{
		pPre = head;
		pCur = head->get_pointer();
		head = pCur;
		delete pPre;	// 메모리 해제
		size--;
		return 1;
	}
	else	// 그 외의 경우
	{
		pPre = head;
		pCur = head->get_pointer();
		while ((pCur->get_name() != menuname) && (pCur->get_pointer() != NULL))
		{
			pPre = pPre->get_pointer();
			pCur = pCur->get_pointer();

		}
		if (pCur->get_name() == menuname)	// 중간 혹은 끝에서 메뉴가 일치해서 루프를 빠져나온 경우
		{
			pPre->set_pointer(pCur->get_pointer());
			delete pCur;	// 메모리 해제
			size--;
			return 1;
		}
		else		// 끝에 도달했고, 일치하는 메뉴도 없는 경우
			return 0;
	}
}

Dough* DoughList::pick(string menuname)		// 메뉴의 이름을 입력받아 존재하면 인스턴스의 주소를 반환, 없으면 NULL을 반환
{
	Dough *pPre, *pCur;

	if (head->get_name() == menuname)	// 메뉴가 처음과 일치하는 경우
	{
		return head;
	}
	else	// 그 외의 경우
	{
		pPre = head;
		pCur = head->get_pointer();
		while ((pCur->get_name() != menuname) && (pCur->get_pointer() != NULL))
		{
			pPre = pPre->get_pointer();
			pCur = pCur->get_pointer();
		}
		if (pCur->get_name() == menuname)	// 중간 혹은 끝에서 메뉴가 일치해서 루프를 빠져나온 경우
		{
			return pCur;
		}
		else return NULL;		// 메뉴가 존재하지 않는 경우
	}
}

void DoughList::show_all_menu()	// 전체 메뉴를 출력하는 함수
{
	Dough *pWalk;
	pWalk = head;
	cout << "-DOUGH <" << size << ">" << endl;
	while (pWalk != NULL)	// 끝까지 이동
	{
		cout << "[이름:" << pWalk->get_name() << "]";
		cout << "[두께:" << pWalk->get_thickness() << "mm]";
		cout << "[추가비용:" << pWalk->get_extra_cost() << "원]";
		cout << "[소개말:" << pWalk->get_comment() << "]" << endl;
		pWalk = pWalk->get_pointer();
	}
	cout << endl;
}

void DoughList::show_most_popular()	// 가장 sell count가 높은 메뉴를 찾아 출력
{
	Dough *pWalk, *pBest;
	int popular = 0;
	pBest = head;
	pWalk = head;

	while (pWalk != NULL)
	{
		if (pWalk->get_sell_count() > popular)	// 더 인기있는 메뉴를 찾으면
		{
			pBest = pWalk;	// 포인터에 이는 주소를 바꾼다
			popular = pWalk->get_sell_count();	// sell count를 갱신해 비교할 수 있게 한다
		}
		pWalk = pWalk->get_pointer();
	}
	cout << "-DOUGH 인기메뉴" << endl;
	cout << "[이름:" << pBest->get_name() << "]";
	cout << "[두께:" << pBest->get_thickness() << "mm]";
	cout << "[추가비용:" << pBest->get_extra_cost() << "원]";
	cout << "[소개말:" << pBest->get_comment() << "]" << endl;

}

void DoughList::search_by_thick(float hvalue, float lvalue)		// float형의 상한/하한값을 입력받아 해당 범위 내의 thickness인 메뉴를 찾으면 출력
{
	Dough *pWalk;
	int cnt = 0;
	pWalk = head;
	while (pWalk != NULL)	// 끝까지 이동
	{
		if ((pWalk->get_thickness() >= lvalue) && (pWalk->get_thickness() <= hvalue))	// 범위를 만족하는 메뉴가 존재하는 경우 출력 진행
		{
			cout << "[이름:" << pWalk->get_name() << "]";
			cout << "[두께:" << pWalk->get_thickness() << "mm]";
			cout << "[추가비용:" << pWalk->get_extra_cost() << "원]";
			cout << "[소개말:" << pWalk->get_comment() << "]" << endl;
			cnt++;
		}
		pWalk = pWalk->get_pointer();
	}
	cout << "이상 총 " << cnt << "개가 검색되었습니다." << endl << endl;
}
