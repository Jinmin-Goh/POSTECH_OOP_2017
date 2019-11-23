#include <iostream>
#include <string>
#include "EdgeList.h"
using namespace std;

EdgeList::EdgeList()
{
	head = NULL;
	size = 0;
}

void EdgeList::add(Edge* edge)	// �ν��Ͻ� �ּҸ� �Է¹޾� list�� �ν��Ͻ� node�� �߰��ϴ� �Լ�
{
	Edge *pNew, *pEnd;
	pNew = edge;
	pEnd = head;
	if (head == NULL)		// list�� ����ִ� ��쿡 �ٷ� �߰�
	{
		head = edge;
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

int EdgeList::del(string menuname)	// �޴��� ������ ���� �� 1 ��ȯ, ������ �׳� 0 ��ȯ
{
	Edge *pPre, *pCur;

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

Edge* EdgeList::pick(string menuname)	// �޴��� �̸��� �Է¹޾� �����ϸ� �ν��Ͻ��� �ּҸ� ��ȯ, ������ NULL�� ��ȯ
{
	Edge *pPre, *pCur;

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

void EdgeList::show_all_menu()	// ��ü �޴��� ����ϴ� �Լ�
{
	Edge *pWalk;
	int i = 0;
	pWalk = head;
	cout << "-EDGE <" << size << ">" << endl;
	while (pWalk != NULL)	// ������ �̵�
	{
		cout << "[�̸�:" << pWalk->get_name() << "]";
		
		cout << "[����:";
		
		for (i = 0; i < 3; i++)
		{
			if (pWalk->get_mousse()[i] == "")
				break;
			if (i != 0)
				cout << ",";
			cout << pWalk->get_mousse()[i];
		}
			cout << "]";
		
		cout << "[�߰����:" << pWalk->get_extra_cost() << "��]";
		cout << "[�Ұ���:" << pWalk->get_comment() << "]" << endl;
		pWalk = pWalk->get_pointer();
	}
	cout << endl;
}

void EdgeList::show_most_popular()	// ���� sell count�� ���� �޴��� ã�� ���
{
	Edge *pWalk, *pBest;
	int popular = 0, i = 0;
	pBest = head;
	pWalk = head;

	while (pWalk != NULL)
	{
		if (pWalk->get_sell_count() > popular)	// �� �α��ִ� �޴��� ã����
		{
			pBest = pWalk;		// �����Ϳ� �̴� �ּҸ� �ٲ۴�
			popular = pWalk->get_sell_count();	// sell count�� ������ ���� �� �ְ� �Ѵ�
		}
		pWalk = pWalk->get_pointer();
	}
	cout << "-EDGE �α�޴�" << endl;
	cout << "[�̸�:" << pBest->get_name() << "]";
	cout << "[����:";
	for (i = 0; i < 3; i++)
	{
		if (pBest->get_mousse()[i] == "")
			break;
		if (i != 0)
			cout << ",";
		cout << pBest->get_mousse()[i];
	}
	cout << "]";
	cout << "[�߰����:" << pBest->get_extra_cost() << "��]";
	cout << "[�Ұ���:" << pBest->get_comment() << "]" << endl;

}

void EdgeList::search_by_mousse(string moussename)		// ���� �̸��� �Է¹޾� �޴� ���� mousse�� �� ��Ḧ ����ϸ� ��� ����
{
	Edge *pWalk;
	int cnt = 0, i = 0, flag = 0;
	pWalk = head;
	while (pWalk != NULL)	// ������ �̵�
	{
		flag = 0;
		for (i = 0; i < 3; i++)		// ������ �޴� �ȿ� �����ϴ��� �˻�. ������ flag�� 1��.
		{
			if (pWalk->get_mousse()[i] == "")
				break;
			if (pWalk->get_mousse()[i] == moussename)
			{
				flag = 1;
				break;
			}
		}
		if (flag)		// ������ �޴��� ������ �� �޴� ���
		{
			cout << "[�̸�:" << pWalk->get_name() << "]";

			cout << "[����:";

			for (i = 0; i < 3; i++)
			{
				if (pWalk->get_mousse()[i] == "")
					break;
				if (i != 0)
					cout << ",";
				cout << pWalk->get_mousse()[i];
			}
			cout << "]";

			cout << "[�߰����:" << pWalk->get_extra_cost() << "��]";
			cout << "[�Ұ���:" << pWalk->get_comment() << "]" << endl;
			cnt++;
		}
		pWalk = pWalk->get_pointer();
	}
	cout << "�̻� �� " << cnt << "���� �˻��Ǿ����ϴ�." << endl << endl;
}
