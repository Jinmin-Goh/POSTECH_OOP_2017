#include <iostream>
#include <string>
#include "DoughList.h"
using namespace std;

DoughList::DoughList()	// ������ - ������ �ʱ�ȭ
{
	head = NULL;
	size = 0;
}

void DoughList::add(Dough* dough)	// �ν��Ͻ� �ּҸ� �Է¹޾� list�� �ν��Ͻ� node�� �߰��ϴ� �Լ�
{
	Dough *pNew, *pEnd;
	pNew = dough;
	pEnd = head;
	if (head == NULL)		// list�� ����ִ� ��쿡 �ٷ� �߰�
	{
		head = dough;
	}
	else					// �� ���� ���
	{
		while (pEnd->get_pointer() != NULL)
		{
			pEnd = pEnd->get_pointer();
		}
		pEnd->set_pointer(pNew);	// list �������� dough ��ü�� link
	}
	size++;
	
}

int DoughList::del(string menuname) // �޴��� ������ ���� �� 1 ��ȯ, ������ �׳� 0 ��ȯ
{
	Dough *pPre, *pCur;

	if (head == NULL)	// �޴��� ����ִ� ���
		return 0;
	else if (head->get_name() == menuname)	// �޴��� ó���� ��ġ�ϴ� ���
	{
		pPre = head;
		pCur = head->get_pointer();
		head = pCur;
		delete pPre;	// �޸� ����
		size--;
		return 1;
	}
	else	// �� ���� ���
	{
		pPre = head;
		pCur = head->get_pointer();
		while ((pCur->get_name() != menuname) && (pCur->get_pointer() != NULL))
		{
			pPre = pPre->get_pointer();
			pCur = pCur->get_pointer();

		}
		if (pCur->get_name() == menuname)	// �߰� Ȥ�� ������ �޴��� ��ġ�ؼ� ������ �������� ���
		{
			pPre->set_pointer(pCur->get_pointer());
			delete pCur;	// �޸� ����
			size--;
			return 1;
		}
		else		// ���� �����߰�, ��ġ�ϴ� �޴��� ���� ���
			return 0;
	}
}

Dough* DoughList::pick(string menuname)		// �޴��� �̸��� �Է¹޾� �����ϸ� �ν��Ͻ��� �ּҸ� ��ȯ, ������ NULL�� ��ȯ
{
	Dough *pPre, *pCur;

	if (head->get_name() == menuname)	// �޴��� ó���� ��ġ�ϴ� ���
	{
		return head;
	}
	else	// �� ���� ���
	{
		pPre = head;
		pCur = head->get_pointer();
		while ((pCur->get_name() != menuname) && (pCur->get_pointer() != NULL))
		{
			pPre = pPre->get_pointer();
			pCur = pCur->get_pointer();
		}
		if (pCur->get_name() == menuname)	// �߰� Ȥ�� ������ �޴��� ��ġ�ؼ� ������ �������� ���
		{
			return pCur;
		}
		else return NULL;		// �޴��� �������� �ʴ� ���
	}
}

void DoughList::show_all_menu()	// ��ü �޴��� ����ϴ� �Լ�
{
	Dough *pWalk;
	pWalk = head;
	cout << "-DOUGH <" << size << ">" << endl;
	while (pWalk != NULL)	// ������ �̵�
	{
		cout << "[�̸�:" << pWalk->get_name() << "]";
		cout << "[�β�:" << pWalk->get_thickness() << "mm]";
		cout << "[�߰����:" << pWalk->get_extra_cost() << "��]";
		cout << "[�Ұ���:" << pWalk->get_comment() << "]" << endl;
		pWalk = pWalk->get_pointer();
	}
	cout << endl;
}

void DoughList::show_most_popular()	// ���� sell count�� ���� �޴��� ã�� ���
{
	Dough *pWalk, *pBest;
	int popular = 0;
	pBest = head;
	pWalk = head;

	while (pWalk != NULL)
	{
		if (pWalk->get_sell_count() > popular)	// �� �α��ִ� �޴��� ã����
		{
			pBest = pWalk;	// �����Ϳ� �̴� �ּҸ� �ٲ۴�
			popular = pWalk->get_sell_count();	// sell count�� ������ ���� �� �ְ� �Ѵ�
		}
		pWalk = pWalk->get_pointer();
	}
	cout << "-DOUGH �α�޴�" << endl;
	cout << "[�̸�:" << pBest->get_name() << "]";
	cout << "[�β�:" << pBest->get_thickness() << "mm]";
	cout << "[�߰����:" << pBest->get_extra_cost() << "��]";
	cout << "[�Ұ���:" << pBest->get_comment() << "]" << endl;

}

void DoughList::search_by_thick(float hvalue, float lvalue)		// float���� ����/���Ѱ��� �Է¹޾� �ش� ���� ���� thickness�� �޴��� ã���� ���
{
	Dough *pWalk;
	int cnt = 0;
	pWalk = head;
	while (pWalk != NULL)	// ������ �̵�
	{
		if ((pWalk->get_thickness() >= lvalue) && (pWalk->get_thickness() <= hvalue))	// ������ �����ϴ� �޴��� �����ϴ� ��� ��� ����
		{
			cout << "[�̸�:" << pWalk->get_name() << "]";
			cout << "[�β�:" << pWalk->get_thickness() << "mm]";
			cout << "[�߰����:" << pWalk->get_extra_cost() << "��]";
			cout << "[�Ұ���:" << pWalk->get_comment() << "]" << endl;
			cnt++;
		}
		pWalk = pWalk->get_pointer();
	}
	cout << "�̻� �� " << cnt << "���� �˻��Ǿ����ϴ�." << endl << endl;
}
