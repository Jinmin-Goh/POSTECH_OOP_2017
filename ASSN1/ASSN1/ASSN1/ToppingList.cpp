#include <iostream>
#include <string>
#include "ToppingList.h"
using namespace std;

ToppingList::ToppingList()
{
	head = NULL;
	size = 0;
}

void ToppingList::add(Topping* topping)	// �ν��Ͻ� �ּҸ� �Է¹޾� list�� �ν��Ͻ� node�� �߰��ϴ� �Լ�
{
	Topping *pNew, *pEnd;
	pNew = topping;
	pEnd = head;
	if (head == NULL)		// list�� ����ִ� ��쿡 �ٷ� �߰�
	{
		head = topping;
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

int ToppingList::del(string menuname)	// �޴��� ������ ���� �� 1 ��ȯ, ������ �׳� 0 ��ȯ
{
	Topping *pPre, *pCur;

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

Topping* ToppingList::pick(string menuname)		// �޴��� �̸��� �Է¹޾� �����ϸ� �ν��Ͻ��� �ּҸ� ��ȯ, ������ NULL�� ��ȯ
{
	Topping *pPre, *pCur;
		
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

void ToppingList::show_all_menu()	// ��ü �޴��� ����ϴ� �Լ�
{
	Topping *pWalk;
	int i = 0;
	pWalk = head;
	cout << "-TOPPING <" << size << ">" << endl;
	while (pWalk != NULL)	// ������ �̵�
	{
		cout << "[�̸�:" << pWalk->get_name() << "]";

		cout << "[���:";

		for (i = 0; i < 10; i++)
		{
			if (pWalk->get_ingredient()[i] == "")
				break;
			if (i != 0)
				cout << ",";
			cout << pWalk->get_ingredient()[i];
		}
		cout << "]";

		cout << "[����:" << pWalk->get_price() << "��]";
		cout << "[�Ұ���:" << pWalk->get_comment() << "]" << endl;
		pWalk = pWalk->get_pointer();
	}
	cout << endl;
}

void ToppingList::show_most_popular()	// ���� sell count�� ���� �޴��� ã�� ���
{
	Topping *pWalk, *pBest;
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
	cout << "-TOPPING �α�޴�" << endl;
	cout << "[�̸�:" << pBest->get_name() << "]";
	cout << "[���:";
	for (i = 0; i < 10; i++)
	{
		if (pBest->get_ingredient()[i] == "")
			break;
		if (i != 0)
			cout << ",";
		cout << pBest->get_ingredient()[i];
	}
	cout << "]";
	cout << "[�߰����:" << pBest->get_price() << "��]";
	cout << "[�Ұ���:" << pBest->get_comment() << "]" << endl;

}

void ToppingList::search_by_ingred(string ingname)		// ��� �̸��� �Է¹޾� �޴� ���� ingredient�� �� ��Ḧ ����ϸ� ��� ����
{
	Topping *pWalk;
	int cnt = 0, i = 0, flag = 0;
	pWalk = head;
	while (pWalk != NULL)	// ������ �̵�
	{
		flag = 0;
		for (i = 0; i < 10; i++)		// ��ᰡ �޴� �ȿ� �����ϴ��� �˻�. ������ flag�� 1��.
		{
			if (pWalk->get_ingredient()[i] == "")
				break;
			if (pWalk->get_ingredient()[i] == ingname)
			{
				flag = 1;
				break;
			}
		}
		if (flag)		// ��ᰡ �޴��� ������ �� �޴� ���
		{
			cout << "[�̸�:" << pWalk->get_name() << "]";

			cout << "[���:";

			for (i = 0; i < 10; i++)
			{
				if (pWalk->get_ingredient()[i] == "")
					break;
				if (i != 0)
					cout << ",";
				cout << pWalk->get_ingredient()[i];
			}
			cout << "]";

			cout << "[����:" << pWalk->get_price() << "��]";
			cout << "[�Ұ���:" << pWalk->get_comment() << "]" << endl;
			cnt++;
		}
		pWalk = pWalk->get_pointer();
	}
	cout << "�̻� �� " << cnt << "���� �˻��Ǿ����ϴ�." << endl << endl;
}

void ToppingList::search_by_price(int hprice, int lprice)		// int���� ����/���Ѱ��� �Է¹޾� �ش� ���� ���� price�� �޴��� ã���� ���
{
	Topping *pWalk;
	int cnt = 0, i = 0, flag = 0;
	pWalk = head;
	while (pWalk != NULL)	// ������ �̵�
	{
		if ((hprice >= pWalk->get_price()) && (lprice <= pWalk->get_price()))		// ������ ������ �����ϸ� �� �޴� ���
		{
			cout << "[�̸�:" << pWalk->get_name() << "]";

			cout << "[���:";

			for (i = 0; i < 10; i++)
			{
				if (pWalk->get_ingredient()[i] == "")
					break;
				if (i != 0)
					cout << ",";
				cout << pWalk->get_ingredient()[i];
			}
			cout << "]";

			cout << "[����:" << pWalk->get_price() << "��]";
			cout << "[�Ұ���:" << pWalk->get_comment() << "]" << endl;
			cnt++;
		}
		pWalk = pWalk->get_pointer();
	}
	cout << "�̻� �� " << cnt << "���� �˻��Ǿ����ϴ�." << endl << endl;
}
