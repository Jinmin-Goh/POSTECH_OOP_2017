#include <iostream>
#include <string>
#include <fstream>
#include "Dough.h"
#include "DoughList.h"
#include "Edge.h"
#include "EdgeList.h"
#include "Topping.h"
#include "ToppingList.h"
using namespace std;
void printMenu();	// �޴� ��� �Լ�
int datainit(DoughList *doughlist, EdgeList *edgelist, ToppingList *toppinglist);	// ������ �ִ��� Ȯ���ϰ� ������ �� ���� �����͸� ���� �ʱ�ȭ. ������ ������ 0, ������ 1 return

int main()
{
	// ���� ����
	int totalprice, price, extra_cost, delcheck, menunum2, hprice, lprice, filecheck, flag = 0;
	float thickness, lvalue, hvalue;
	string menunum, toppingtitle, doughtitle, edgetitle, fullingredient, ingredient[10], fullmousse, mousse[3], comment, ingtitle, moussetitle,
		pricestring, thicknessstring, extra_coststring, lpricestring, hpricestring, lvaluestring, hvaluestring;
	Dough *dough, *doughp;
	DoughList doughlist;
	Edge *edge, *edgep;
	EdgeList edgelist;
	Topping *topping, *toppingp;
	ToppingList toppinglist;
	char *token, *ch;
	int i = 0;

	// ���� ���� üũ �� �ʱ�ȭ
	filecheck = datainit(&doughlist, &edgelist, &toppinglist);
	if (filecheck) return 0;		// ���� ������ ���α׷� ����

	// �޴� ����
	while (true)
	{
		// �⺻ �޴� ��� �� �޴� �Է¹���
		printMenu();
		getline(cin, menunum);

		if (menunum == "0")		// �޴� 0 - ��ü �޴� ���
		{
			// ������ ��� ��� �� ���� �����
			toppinglist.show_all_menu();
			doughlist.show_all_menu();
			edgelist.show_all_menu();
			continue;
		}
		else if (menunum == "1")	// �޴� 1 - �ֹ��ϱ�
		{
			// ������ ��� ���
			toppinglist.show_all_menu();
			doughlist.show_all_menu();
			edgelist.show_all_menu();

			// ���� �Է�
			cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl << ">> ";
			getline(cin, toppingtitle);
			toppingp = toppinglist.pick(toppingtitle);
			if (toppingp == NULL) // �Է��� ����� ��ġ�ϴ� �޴��� ���� ��� �ʱ� �޴��� ��ȯ
			{
				cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
				continue;
			}

			// ����
			cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl << ">> ";
			getline(cin, doughtitle);
			doughp = doughlist.pick(doughtitle);
			if (doughp == NULL)	// �Է��� ����� ��ġ�ϴ� �޴��� ���� ��� �ʱ� �޴��� ��ȯ
			{
				cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
				continue;
			}

			// ����
			cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl << ">> ";
			getline(cin, edgetitle);
			edgep = edgelist.pick(edgetitle);
			if (edgep == NULL)	// �Է��� ����� ��ġ�ϴ� �޴��� ���� ��� �ʱ� �޴��� ��ȯ
			{
				cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
				continue;
			}

			// �Է��� ���� ��� �����ϴ� ���
			cout << endl << "�ֹ��Ͻ� ���ڴ� \"" << doughtitle << " " << edgetitle << " " << toppingtitle << "\" �Դϴ�." << endl;

			// �Ѿ� ��� �� ���
			totalprice = 0;
			totalprice = toppingp->get_price() + doughp->get_extra_cost() + edgep->get_extra_cost();
			cout << "������ \"" << totalprice << "\"�� �Դϴ�." << endl << endl;
			// sellcount ����
			doughp->inc_sellcount();
			edgep->inc_sellcount();
			toppingp->inc_sellcount();
			continue;
		}
		else if (menunum == "2") // �޴� 2 - �޴� �߰�
		{
			cout << "�߰��ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
			cout << "1: ����" << endl << "2: ����" << endl << "3: ����" << endl << ">> ";
			getline(cin, menunum);

			// ����
			if (menunum == "1")
			{
				// ���ο� �ν��Ͻ� �����Ҵ�
				topping = new Topping;


				cout << "�̸�" << endl << ">> ";	// �̸�
				getline(cin, toppingtitle);
				if (toppingtitle == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				topping->set_name(toppingtitle);

				cout << "���" << endl << ">> ";	// ���
				getline(cin, fullingredient);
				// ��� �κ��� comma�� ���� split�ؼ� ���� string���� ����� �����ϴ� ����
				ch = (char*)fullingredient.c_str();
				token = strtok(ch, ",");
				i = 0;
				while (token != NULL)
				{
					ingredient[i] = token;
					i++;
					//	cout << token << endl;
					token = strtok(NULL, ",");
				}
				topping->add_ingredient(ingredient);

				cout << "����" << endl << ">> ";	// ����
				getline(cin, pricestring);
				if (pricestring == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				price = atoi(pricestring.c_str());	// ������ ��ȯ
				topping->set_price(price);
				
				cout << "�Ұ���" << endl << ">> ";	// �Ұ���
				getline(cin, comment);
				if (comment == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				topping->set_comment(comment);

				toppinglist.add(topping);	// list�� �߰�
				cout << "�޴� �߰��� �Ϸ�Ǿ����ϴ�." << endl << endl;
				toppinglist.show_all_menu();	
				continue;
			}
			else if (menunum == "2")
			{
				// ���ο� �ν��Ͻ� �����Ҵ�
				dough = new Dough;

				cout << "�̸�" << endl << ">> ";	//�̸�
				getline(cin, doughtitle);
				if (doughtitle == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				dough->set_name(doughtitle);

				cout << "�β�" << endl << ">> ";
				getline(cin, thicknessstring);
				if (thicknessstring == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				thickness = atof(thicknessstring.c_str());	// float�� ��ȯ
				dough->set_thickness(thickness);

				cout << "�߰����" << endl << ">> ";	// �߰����
				getline(cin, extra_coststring);
				if (extra_coststring == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				extra_cost = atoi(extra_coststring.c_str());	// ������ ��ȯ
				dough->set_extra_cost(extra_cost);
				
				cout << "�Ұ���" << endl << ">> ";	//�Ұ���
				getline(cin, comment);
				if (comment == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				dough->set_comment(comment);

				doughlist.add(dough);	// list�� �߰�
				cout << "�޴� �߰��� �Ϸ�Ǿ����ϴ�." << endl << endl;
				doughlist.show_all_menu();
				continue;
			}
			else if (menunum == "3")
			{
				// ���ο� �ν��Ͻ� �����Ҵ�
				edge = new Edge;
				cout << "�̸�" << endl << ">> ";	// �̸�
				getline(cin, edgetitle);
				if (edgetitle == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				edge->set_name(edgetitle);

				cout << "����" << endl << ">> ";	// ����
				getline(cin, fullmousse);
				// ������ comma�� �������� split �ؼ� ���� string���� ����� �����ϴ� ����
				ch = (char*)fullmousse.c_str();
				token = strtok(ch, ",");
				i = 0;
				while (token != NULL)
				{
					mousse[i] = token;
					i++;
					//cout << token << endl;
					token = strtok(NULL, ",");
				}
				edge->add_mousse(mousse);

				cout << "�߰����" << endl << ">> ";	// �߰����
				getline(cin, extra_coststring);
				if (extra_coststring == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				extra_cost = atoi(extra_coststring.c_str());
				edge->set_extra_cost(extra_cost);
				
				cout << "�Ұ���" << endl << ">> ";	// �Ұ���
				getline(cin, comment);
				if (comment == "")	// ���� �Է� ���� ���� �Է� �� ���� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
				edge->set_comment(comment);

				edgelist.add(edge);	// list�� �߰�
				cout << "�޴� �߰��� �Ϸ�Ǿ����ϴ�." << endl << endl;
				edgelist.show_all_menu();
				continue;
			}
			else	// �߸��� �޴� ������ �Է�
			{
				cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
				continue;
			}
		}
		else if (menunum == "3")	// �޴� 3 - �޴� ����
		{
			cout << "�����ϰ��� �ϴ� �޴� �̸��� �Է��ϼ���." << endl;
			cout << "1: ����" << endl << "2: ����" << endl << "3: ����" << endl << ">> ";
			getline(cin, menunum);	// �޴� �̸� �Է�
			if (menunum == "1")		// ����
			{
				toppinglist.show_all_menu();
				cout << "�����ϰ��� �ϴ� �޴� �̸��� �Է��ϼ���." << endl << ">> ";
				getline(cin, toppingtitle);
				delcheck = toppinglist.del(toppingtitle);	// �Է¹��� �̸����� �˻� �� �����۾�
				if (delcheck)	// 1�̸� �޴��� �����ؼ� ���� ����
				{
					cout << "�޴� ������ �Ϸ�Ǿ����ϴ�." << endl << endl;
					toppinglist.show_all_menu();
				}
				else			// 0�̸� �޴��� �������� �ʾƼ� ���� ����
				{
					cout << "�޴��� �������� �ʽ��ϴ�. ������ �����߽��ϴ�." << endl;
				}
				continue;
			}
			else if (menunum == "2")	// ����
			{
				doughlist.show_all_menu();
				cout << "�����ϰ��� �ϴ� �޴� �̸��� �Է��ϼ���." << endl << ">> ";
				getline(cin, doughtitle);	// ���� �̸� �Է�
				delcheck = doughlist.del(doughtitle);	// �Է¹��� �̸����� �˻� �� �����۾�
				if (delcheck)	// 1�̸� �޴��� �����ؼ� ���� ����
				{
					cout << "�޴� ������ �Ϸ�Ǿ����ϴ�." << endl << endl;
					doughlist.show_all_menu();
				}
				else	// 0�̸� �޴��� �������� �ʾƼ� ���� ����
				{
					cout << "�޴��� �������� �ʽ��ϴ�. ������ �����߽��ϴ�." << endl;
				}
				continue;
			}
			else if (menunum == "3")	// ����
			{
				edgelist.show_all_menu();
				cout << "�����ϰ��� �ϴ� �޴� �̸��� �Է��ϼ���." << endl << ">> ";
				getline(cin, edgetitle);	// ���� �̸� �Է�
				delcheck = edgelist.del(edgetitle);
				if (delcheck)	// 1�̸� �޴��� �����ؼ� ���� ����
				{
					cout << "�޴� ������ �Ϸ�Ǿ����ϴ�." << endl << endl;
					edgelist.show_all_menu();
				}
				else	// 0�̸� �޴��� �������� �ʾƼ� ���� ����
				{
					cout << "�޴��� �������� �ʽ��ϴ�. ������ �����߽��ϴ�." << endl;
				}
				continue;
			}
			else	// �߸��� �޴� ���� �Է�
			{
				cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
				continue;
			}
		}
		else if (menunum == "4")	// �޴� 4 - �˻�
		{
			cout << "�˻��ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
			cout << "1: ����" << endl << "2: ����" << endl << "3: ����" << endl << ">> ";
			getline(cin, menunum);	// �޴� ���� �Է�
			
			if (menunum == "1")		// ����
			{
				cout << "�˻� ������ �����ϼ���." << endl << "1. ���� �˻�" << endl << "2. �������� �˻�" << endl << ">> ";
				getline(cin, menunum);
				if (menunum == "1")		// ���� �˻�
				{
					cout << "��� �̸��� �Է����ּ���." << endl << ">> ";
					getline(cin, ingtitle);
					toppinglist.search_by_ingred(ingtitle);
					continue;
				}
				else if (menunum == "2") // �������� �˻�
				{
					cout << "���� ���� �� ������ �Է����ּ���." << endl << ">> ";
					getline(cin, lpricestring);
					lprice = atoi(lpricestring.c_str());	// ������ ��ȯ

					cout << "���� ���� �� ������ �Է����ּ���." << endl << ">> ";
					getline(cin, hpricestring);
					hprice = atoi(hpricestring.c_str());	// ������ ��ȯ
					toppinglist.search_by_price(hprice, lprice);
					continue;
				}
				else	// �߸��� �˻� ���� �Է�
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
			}
			else if (menunum == "2")	// ����
			{
				cout << "�˻� ������ �����ϼ���." << endl << "1. �β��� �˻�" << endl << ">> ";
				getline(cin, menunum);
				if (menunum == "1")		// �β��� �˻�
				{
					cout << "�β� ���� �� ������ �Է����ּ���." << endl << ">> ";
					getline(cin, lvaluestring);
					lvalue = atof(lvaluestring.c_str());	// float�� ��ȯ
					cout << "�β� ���� �� ������ �Է����ּ���." << endl << ">> ";
					getline(cin, hvaluestring);
					hvalue = atof(hvaluestring.c_str());	// float�� ��ȯ
					doughlist.search_by_thick(hvalue, lvalue);
					continue;
				}
				else	// �߸��� �˻� ���� �Է�
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
			}
			else if (menunum == "3")	// ����
			{
				cout << "�˻� ������ �����ϼ���." << endl << "1. ������ �˻�" << endl << ">> ";
				getline(cin, menunum);
				if (menunum == "1")		// ������ �˻�
				{
					cout << "���� �̸��� �Է����ּ���." << endl << ">> ";
					getline(cin, moussetitle);
					edgelist.search_by_mousse(moussetitle);
					continue;
				}
				else	// �߸��� �˻� ���� �Է�
				{
					cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
					continue;
				}
			}
			else		// �߸��� �޴� ���� �Է�
			{
				cout << "�߸��� �Է��Դϴ�. �ʱ� �޴��� ���ư��ϴ�." << endl;
				continue;
			}
		}
		else if (menunum == "5")	// �޴� 5 - �α�޴� ���
		{
			// ����, ����. ���� ������ ���� sell count�� ���� �޴� ���. ������ list�� ����� �޴� ���.
			toppinglist.show_most_popular();
			doughlist.show_most_popular();
			edgelist.show_most_popular();
			continue;
		}
		else if (menunum == "6")	// �޴� 6 - ����
			break;	// �޴� ���� Ż��
		else	// �߸��� �޴� ��ȣ �Է�
			cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��� �ּ���." << endl;
	}
	return 0;
}

void printMenu()	// �⺻ �޴��� ����ϴ� �Լ�
{
	cout << "-----------------" << endl;
	cout << "0: ��� �޴� ����" << endl;
	cout << "1: �ֹ��ϱ�" << endl;
	cout << "2: �޴� �߰�" << endl;
	cout << "3: �޴� ����" << endl;
	cout << "4: �޴� �˻�" << endl;
	cout << "5: �α�޴� ��õ" << endl;
	cout << "6: ���α׷� ����" << endl;
	cout << "-----------------" << endl;
	cout << ">> ";
	return;
}

int datainit(DoughList *doughlist, EdgeList *edgelist, ToppingList *toppinglist)	// ������ �ִ��� Ȯ���ϰ� ������ �� ���� �����͸� ���� �ʱ�ȭ. ������ ������ 0, ������ 1 return
{
	// ���� ����
	string s, name, fullingredient, ingredient[10], fullmousse, mousse[3], comment, fullmenu, fullmenu2, checkstring;
	int price, extra_cost, index, index2, index3, index4, cindex, cindex2;
	float thickness;
	Topping *topping;
	Dough *dough;
	Edge *edge;
	char *token, *ch, *token2, *ch2, *dummy;
	int i = 0, flag = 0;
	ifstream in;

	in.open("init_menu.txt");	// ���� open
	if (in.is_open())	// ������ �����ؼ� ������ ���
	{
		getline(in,s);	// ù �� �Է�
		if (s == "-����")	// ���� ���� ���ڿ��� ���
		{
			while(true)	// �Է� ����
			{
				// ingredient string �迭 �ʱ�ȭ
				for (i = 0; i < 10; i++)
					ingredient[i] = "";

				getline(in, fullmenu);			// �� ��ü �Է�
				if (fullmenu == "-����")		// ���� ���� �����ڸ� ���� ���� ��Ż
					break;
				topping = new Topping;			// �ν��Ͻ� �����Ҵ�
						
				fullmenu2 = fullmenu;			// ���ڿ� ���� - �� ������ token�� ����� �����̱� ����
				ch = (char*)fullmenu.c_str();	// string�� char �迭�� ��ȯ
				token2 = strtok(ch, "	");		// ��ū�� tab�� ���� �� split
				topping->set_name(token2);		// ù ���ڿ��� �̸�
				
				token2 = strtok(NULL, "	");		// ���ڿ� split
				fullingredient = token2;
				token2 = strtok(NULL, "	");		// ingredient �κ� �н�
				price = atoi(token2);			// ���� �κ� ���� ��ȯ
				topping->set_price(price);
				token2 = strtok(NULL, "	");		// �ڸ�Ʈ �κ����� �̵�
				comment = token2;
				topping->set_comment(comment);	// �ڸ�Ʈ ����

				token = strtok((char*)fullingredient.c_str(), ",");	// �� ��°�� tab�� ���� �ɰ��� ���ڿ��� ingredient�̹Ƿ� comma�� �ٽ� split			
				
				// ingredient ���� ����. ingredient �κ��� ����ó�� ����ִ� ���� �������� ����.(��ᰡ ���� ���ڴ� �����Ƿ�)
				i = 0;
				while (token != NULL)
				{
					ingredient[i] = token;
					i++;
					token = strtok(NULL, ",");
				}
				topping->add_ingredient(ingredient);
								
				toppinglist->add(topping);		// list�� �߰�
				if (strlen(token2) == 0) continue;		// ���� �������̸� ���� ó������ ���ư�
				

			}
		}
		if (fullmenu == "-����")	// ���� ���� ���ڿ��� ���
		{
			while (true)			// ���� ������ �Է� ����
			{
				getline(in, fullmenu);			// �� ��ü �Է�
				if (fullmenu == "-����")		// ���� ���� �����ڸ� ���� ���� ��Ż
					break;	
				dough = new Dough;				// �ν��Ͻ� �����Ҵ�
				fullmenu2 = fullmenu;
				ch = (char*)fullmenu.c_str();	// char�� ��ȯ

				token2 = strtok(ch, "	");		// �̸� �κ� split
				dough->set_name(token2);

				token2 = strtok(NULL, "	");		// �β� �κ� split
				thickness = atof(token2);		// float�� ��ȯ
				dough->set_thickness(thickness);

				token2 = strtok(NULL, "	");		// �߰��ݾ� �κ� split
				extra_cost = atoi(token2);		// ������ ��ȯ
				dough->set_extra_cost(extra_cost);
				
				token2 = strtok(NULL, "	");		// comment �κ� split
				comment = token2;
				dough->set_comment(comment);

				doughlist->add(dough);			// list�� �߰�

				if (token2 == "") continue;		// ���� ������ ������ ���� ó������ �̵�

			}
		}
		if (fullmenu == "-����")	// ���� ���� ���ڿ��� ���
		{
			while (true)			// ������ �Է� ����
			{				
				// ���� string �迭 �ʱ�ȭ
				flag++;
				for (i = 0; i < 3 ; i++)
				mousse[i] = "";
				getline(in, fullmenu);			// �� ��ü �Է�
				
				for(int ii=0; ii<fullmenu.length(); ii++)
					dummy[i] = (int)fullmenu[i];			// ������ �� �� ������ �� ó���� ������ ������ find �Լ����� index�� ������������ ���ȴ�.
				
				if(fullmenu.length()==0) break;	// �� �Է��� NULL�̸� ��� ����
				edge = new Edge;				// �ν��Ͻ� �����Ҵ�
				fullmenu2 = fullmenu;			// ���ڿ� ���� - �� ������ token�� ����� �����̱� ����
				checkstring = fullmenu;			// ���ڿ� ���� - mousse�� �������� �ʾ� �������� tab�� �������� Ȯ���� �� ���
				ch = (char*)fullmenu.c_str();	// char�� ��ȯ
				
				token2 = strtok(ch, "	");		// �̸� �κ� split
				edge->set_name(token2);

				token2 = strtok(NULL, "	");		// ����(������ ������ �߰��ݾ�) �κ� split


				index = checkstring.find("\t");	// ó�� tab�� ������ ��ġ�� ����
				index2 = index + 1;
				
				// ���� ù tab�� ��ġ�� �� ��° tab�� ��ġ index�� ���̰� 1�̶��, �� �����ϴٸ� ���� �����Ͱ� ����.
				if (index + 1 == checkstring.find("	", index2))
				{
					edge->add_mousse(mousse);		// ������ �� �迭 ��ȯ
					extra_cost = atoi(token2);		// ���� ��ȯ
					edge->set_extra_cost(extra_cost);// �߰��ݾ� �Է�
					token2 = strtok(NULL, "	");		// comment split
					comment = token2;
					edge->set_comment(comment);
					edgelist->add(edge);			// list�� �߰�
				}
				else 	// ���� �����Ͱ� �ִ� ��� �Է¹޴´�.
				{
					fullmousse = token2;
					token2 = strtok(NULL, "	");		// �߰��ݾ� �κ� split
					extra_cost = atoi(token2);		// ���� ��ȯ
					edge->set_extra_cost(extra_cost);
					token2 = strtok(NULL, "	");		// comment split
					comment = token2;
					edge->set_comment(comment);

					token = strtok((char*)fullmousse.c_str(), ",");
					i = 0;
					while (token != NULL)
					{
						mousse[i] = token;
						i++;
						token = strtok(NULL, ",");
					}
					edge->add_mousse(mousse);
					edgelist->add(edge);			// list�� �߰�
				}
				
				if (in.eof())		// ������ ���� ������ ���, ���� ��Ż
					break;
			}
		}
		in.close();	// ���� ����
		return 0;
	}
	else	// ������ �������� �ʴ� ���
	{
		cout << "������ �������� �ʽ��ϴ�. ���α׷��� �����մϴ�." << endl;
		in.close();
		return 1;
	}
}
