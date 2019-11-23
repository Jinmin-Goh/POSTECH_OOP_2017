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
void printMenu();	// 메뉴 출력 함수
int datainit(DoughList *doughlist, EdgeList *edgelist, ToppingList *toppinglist);	// 파일이 있는지 확인하고 있으면 그 파일 데이터를 토대로 초기화. 파일이 있으면 0, 없으면 1 return

int main()
{
	// 변수 정의
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

	// 파일 존재 체크 및 초기화
	filecheck = datainit(&doughlist, &edgelist, &toppinglist);
	if (filecheck) return 0;		// 파일 없으면 프로그램 종료

	// 메뉴 루프
	while (true)
	{
		// 기본 메뉴 출력 후 메뉴 입력받음
		printMenu();
		getline(cin, menunum);

		if (menunum == "0")		// 메뉴 0 - 전체 메뉴 출력
		{
			// 종류별 목록 출력 후 루프 재시작
			toppinglist.show_all_menu();
			doughlist.show_all_menu();
			edgelist.show_all_menu();
			continue;
		}
		else if (menunum == "1")	// 메뉴 1 - 주문하기
		{
			// 종류별 목록 출력
			toppinglist.show_all_menu();
			doughlist.show_all_menu();
			edgelist.show_all_menu();

			// 토핑 입력
			cout << "원하시는 토핑 이름을 입력하세요." << endl << ">> ";
			getline(cin, toppingtitle);
			toppingp = toppinglist.pick(toppingtitle);
			if (toppingp == NULL) // 입력한 내용과 일치하는 메뉴가 없는 경우 초기 메뉴로 귀환
			{
				cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
				continue;
			}

			// 도우
			cout << "원하시는 도우 이름을 입력하세요." << endl << ">> ";
			getline(cin, doughtitle);
			doughp = doughlist.pick(doughtitle);
			if (doughp == NULL)	// 입력한 내용과 일치하는 메뉴가 없는 경우 초기 메뉴로 귀환
			{
				cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
				continue;
			}

			// 에지
			cout << "원하시는 에지 이름을 입력하세요." << endl << ">> ";
			getline(cin, edgetitle);
			edgep = edgelist.pick(edgetitle);
			if (edgep == NULL)	// 입력한 내용과 일치하는 메뉴가 없는 경우 초기 메뉴로 귀환
			{
				cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
				continue;
			}

			// 입력한 값이 모두 존재하는 경우
			cout << endl << "주문하신 피자는 \"" << doughtitle << " " << edgetitle << " " << toppingtitle << "\" 입니다." << endl;

			// 총액 계산 후 출력
			totalprice = 0;
			totalprice = toppingp->get_price() + doughp->get_extra_cost() + edgep->get_extra_cost();
			cout << "가격은 \"" << totalprice << "\"원 입니다." << endl << endl;
			// sellcount 증가
			doughp->inc_sellcount();
			edgep->inc_sellcount();
			toppingp->inc_sellcount();
			continue;
		}
		else if (menunum == "2") // 메뉴 2 - 메뉴 추가
		{
			cout << "추가하고자 하는 메뉴의 종류를 선택하세요." << endl;
			cout << "1: 토핑" << endl << "2: 도우" << endl << "3: 에지" << endl << ">> ";
			getline(cin, menunum);

			// 토핑
			if (menunum == "1")
			{
				// 새로운 인스턴스 동적할당
				topping = new Topping;


				cout << "이름" << endl << ">> ";	// 이름
				getline(cin, toppingtitle);
				if (toppingtitle == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				topping->set_name(toppingtitle);

				cout << "재료" << endl << ">> ";	// 재료
				getline(cin, fullingredient);
				// 재료 부분을 comma에 대해 split해서 개별 string으로 만들어 대입하는 과정
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

				cout << "가격" << endl << ">> ";	// 가격
				getline(cin, pricestring);
				if (pricestring == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				price = atoi(pricestring.c_str());	// 정수로 변환
				topping->set_price(price);
				
				cout << "소개말" << endl << ">> ";	// 소개말
				getline(cin, comment);
				if (comment == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				topping->set_comment(comment);

				toppinglist.add(topping);	// list에 추가
				cout << "메뉴 추가가 완료되었습니다." << endl << endl;
				toppinglist.show_all_menu();	
				continue;
			}
			else if (menunum == "2")
			{
				// 새로운 인스턴스 동적할당
				dough = new Dough;

				cout << "이름" << endl << ">> ";	//이름
				getline(cin, doughtitle);
				if (doughtitle == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				dough->set_name(doughtitle);

				cout << "두께" << endl << ">> ";
				getline(cin, thicknessstring);
				if (thicknessstring == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				thickness = atof(thicknessstring.c_str());	// float로 변환
				dough->set_thickness(thickness);

				cout << "추가비용" << endl << ">> ";	// 추가비용
				getline(cin, extra_coststring);
				if (extra_coststring == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				extra_cost = atoi(extra_coststring.c_str());	// 정수로 변환
				dough->set_extra_cost(extra_cost);
				
				cout << "소개말" << endl << ">> ";	//소개말
				getline(cin, comment);
				if (comment == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				dough->set_comment(comment);

				doughlist.add(dough);	// list에 추가
				cout << "메뉴 추가가 완료되었습니다." << endl << endl;
				doughlist.show_all_menu();
				continue;
			}
			else if (menunum == "3")
			{
				// 새로운 인스턴스 동적할당
				edge = new Edge;
				cout << "이름" << endl << ">> ";	// 이름
				getline(cin, edgetitle);
				if (edgetitle == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				edge->set_name(edgetitle);

				cout << "무스" << endl << ">> ";	// 무스
				getline(cin, fullmousse);
				// 무스를 comma를 기준으로 split 해서 개별 string으로 만들어 대입하는 과정
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

				cout << "추가비용" << endl << ">> ";	// 추가비용
				getline(cin, extra_coststring);
				if (extra_coststring == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				extra_cost = atoi(extra_coststring.c_str());
				edge->set_extra_cost(extra_cost);
				
				cout << "소개말" << endl << ">> ";	// 소개말
				getline(cin, comment);
				if (comment == "")	// 문자 입력 없이 엔터 입력 시 에러 출력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
				edge->set_comment(comment);

				edgelist.add(edge);	// list에 추가
				cout << "메뉴 추가가 완료되었습니다." << endl << endl;
				edgelist.show_all_menu();
				continue;
			}
			else	// 잘못된 메뉴 종류의 입력
			{
				cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
				continue;
			}
		}
		else if (menunum == "3")	// 메뉴 3 - 메뉴 삭제
		{
			cout << "삭제하고자 하는 메뉴 이름을 입력하세요." << endl;
			cout << "1: 토핑" << endl << "2: 도우" << endl << "3: 에지" << endl << ">> ";
			getline(cin, menunum);	// 메뉴 이름 입력
			if (menunum == "1")		// 토핑
			{
				toppinglist.show_all_menu();
				cout << "삭제하고자 하는 메뉴 이름을 입력하세요." << endl << ">> ";
				getline(cin, toppingtitle);
				delcheck = toppinglist.del(toppingtitle);	// 입력받은 이름으로 검색 후 삭제작업
				if (delcheck)	// 1이면 메뉴가 존재해서 삭제 성공
				{
					cout << "메뉴 삭제가 완료되었습니다." << endl << endl;
					toppinglist.show_all_menu();
				}
				else			// 0이면 메뉴가 존재하지 않아서 삭제 실패
				{
					cout << "메뉴가 존재하지 않습니다. 삭제에 실패했습니다." << endl;
				}
				continue;
			}
			else if (menunum == "2")	// 도우
			{
				doughlist.show_all_menu();
				cout << "삭제하고자 하는 메뉴 이름을 입력하세요." << endl << ">> ";
				getline(cin, doughtitle);	// 도우 이름 입력
				delcheck = doughlist.del(doughtitle);	// 입력받은 이름으로 검색 후 삭제작업
				if (delcheck)	// 1이면 메뉴가 존재해서 삭제 성공
				{
					cout << "메뉴 삭제가 완료되었습니다." << endl << endl;
					doughlist.show_all_menu();
				}
				else	// 0이면 메뉴가 존재하지 않아서 삭제 실패
				{
					cout << "메뉴가 존재하지 않습니다. 삭제에 실패했습니다." << endl;
				}
				continue;
			}
			else if (menunum == "3")	// 에지
			{
				edgelist.show_all_menu();
				cout << "삭제하고자 하는 메뉴 이름을 입력하세요." << endl << ">> ";
				getline(cin, edgetitle);	// 에지 이름 입력
				delcheck = edgelist.del(edgetitle);
				if (delcheck)	// 1이면 메뉴가 존재해서 삭제 성공
				{
					cout << "메뉴 삭제가 완료되었습니다." << endl << endl;
					edgelist.show_all_menu();
				}
				else	// 0이면 메뉴가 존재하지 않아서 삭제 실패
				{
					cout << "메뉴가 존재하지 않습니다. 삭제에 실패했습니다." << endl;
				}
				continue;
			}
			else	// 잘못된 메뉴 종류 입력
			{
				cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
				continue;
			}
		}
		else if (menunum == "4")	// 메뉴 4 - 검색
		{
			cout << "검색하고자 하는 메뉴의 종류를 선택하세요." << endl;
			cout << "1: 토핑" << endl << "2: 도우" << endl << "3: 에지" << endl << ">> ";
			getline(cin, menunum);	// 메뉴 종류 입력
			
			if (menunum == "1")		// 토핑
			{
				cout << "검색 기준을 선택하세요." << endl << "1. 재료로 검색" << endl << "2. 가격으로 검색" << endl << ">> ";
				getline(cin, menunum);
				if (menunum == "1")		// 재료로 검색
				{
					cout << "재료 이름을 입력해주세요." << endl << ">> ";
					getline(cin, ingtitle);
					toppinglist.search_by_ingred(ingtitle);
					continue;
				}
				else if (menunum == "2") // 가격으로 검색
				{
					cout << "가격 범위 중 하한을 입력해주세요." << endl << ">> ";
					getline(cin, lpricestring);
					lprice = atoi(lpricestring.c_str());	// 정수로 변환

					cout << "가격 범위 중 상한을 입력해주세요." << endl << ">> ";
					getline(cin, hpricestring);
					hprice = atoi(hpricestring.c_str());	// 정수로 변환
					toppinglist.search_by_price(hprice, lprice);
					continue;
				}
				else	// 잘못된 검색 종류 입력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
			}
			else if (menunum == "2")	// 도우
			{
				cout << "검색 기준을 선택하세요." << endl << "1. 두께로 검색" << endl << ">> ";
				getline(cin, menunum);
				if (menunum == "1")		// 두께로 검색
				{
					cout << "두께 범위 중 하한을 입력해주세요." << endl << ">> ";
					getline(cin, lvaluestring);
					lvalue = atof(lvaluestring.c_str());	// float로 반환
					cout << "두께 범위 중 상한을 입력해주세요." << endl << ">> ";
					getline(cin, hvaluestring);
					hvalue = atof(hvaluestring.c_str());	// float로 반환
					doughlist.search_by_thick(hvalue, lvalue);
					continue;
				}
				else	// 잘못된 검색 종류 입력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
			}
			else if (menunum == "3")	// 에지
			{
				cout << "검색 기준을 선택하세요." << endl << "1. 무스로 검색" << endl << ">> ";
				getline(cin, menunum);
				if (menunum == "1")		// 무스로 검색
				{
					cout << "무스 이름을 입력해주세요." << endl << ">> ";
					getline(cin, moussetitle);
					edgelist.search_by_mousse(moussetitle);
					continue;
				}
				else	// 잘못된 검색 종류 입력
				{
					cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
					continue;
				}
			}
			else		// 잘못된 메뉴 종류 입력
			{
				cout << "잘못된 입력입니다. 초기 메뉴로 돌아갑니다." << endl;
				continue;
			}
		}
		else if (menunum == "5")	// 메뉴 5 - 인기메뉴 출력
		{
			// 토핑, 도우. 에지 순으로 가장 sell count가 높은 메뉴 출력. 같으면 list에 가까운 메뉴 출력.
			toppinglist.show_most_popular();
			doughlist.show_most_popular();
			edgelist.show_most_popular();
			continue;
		}
		else if (menunum == "6")	// 메뉴 6 - 종료
			break;	// 메뉴 루프 탈출
		else	// 잘못된 메뉴 번호 입력
			cout << "잘못된 입력입니다. 다시 입력해 주세요." << endl;
	}
	return 0;
}

void printMenu()	// 기본 메뉴를 출력하는 함수
{
	cout << "-----------------" << endl;
	cout << "0: 모든 메뉴 보기" << endl;
	cout << "1: 주문하기" << endl;
	cout << "2: 메뉴 추가" << endl;
	cout << "3: 메뉴 삭제" << endl;
	cout << "4: 메뉴 검색" << endl;
	cout << "5: 인기메뉴 추천" << endl;
	cout << "6: 프로그램 종료" << endl;
	cout << "-----------------" << endl;
	cout << ">> ";
	return;
}

int datainit(DoughList *doughlist, EdgeList *edgelist, ToppingList *toppinglist)	// 파일이 있는지 확인하고 있으면 그 파일 데이터를 토대로 초기화. 파일이 있으면 0, 없으면 1 return
{
	// 변수 정의
	string s, name, fullingredient, ingredient[10], fullmousse, mousse[3], comment, fullmenu, fullmenu2, checkstring;
	int price, extra_cost, index, index2, index3, index4, cindex, cindex2;
	float thickness;
	Topping *topping;
	Dough *dough;
	Edge *edge;
	char *token, *ch, *token2, *ch2, *dummy;
	int i = 0, flag = 0;
	ifstream in;

	in.open("init_menu.txt");	// 파일 open
	if (in.is_open())	// 파일이 존재해서 열리는 경우
	{
		getline(in,s);	// 첫 줄 입력
		if (s == "-토핑")	// 토핑 구분 문자열인 경우
		{
			while(true)	// 입력 루프
			{
				// ingredient string 배열 초기화
				for (i = 0; i < 10; i++)
					ingredient[i] = "";

				getline(in, fullmenu);			// 줄 전체 입력
				if (fullmenu == "-도우")		// 도우 구분 연산자면 토핑 루프 이탈
					break;
				topping = new Topping;			// 인스턴스 동적할당
						
				fullmenu2 = fullmenu;			// 문자열 복사 - 두 종류의 token을 사용할 예정이기 때문
				ch = (char*)fullmenu.c_str();	// string을 char 배열로 변환
				token2 = strtok(ch, "	");		// 토큰을 tab로 지정 후 split
				topping->set_name(token2);		// 첫 문자열은 이름
				
				token2 = strtok(NULL, "	");		// 문자열 split
				fullingredient = token2;
				token2 = strtok(NULL, "	");		// ingredient 부분 패스
				price = atoi(token2);			// 가격 부분 정수 변환
				topping->set_price(price);
				token2 = strtok(NULL, "	");		// 코멘트 부분으로 이동
				comment = token2;
				topping->set_comment(comment);	// 코멘트 대입

				token = strtok((char*)fullingredient.c_str(), ",");	// 두 번째로 tab에 의해 쪼개진 문자열은 ingredient이므로 comma로 다시 split			
				
				// ingredient 대입 루프. ingredient 부분이 무스처럼 비어있는 경우는 생각하지 않음.(재료가 없는 피자는 없으므로)
				i = 0;
				while (token != NULL)
				{
					ingredient[i] = token;
					i++;
					token = strtok(NULL, ",");
				}
				topping->add_ingredient(ingredient);
								
				toppinglist->add(topping);		// list에 추가
				if (strlen(token2) == 0) continue;		// 줄의 마지막이면 루프 처음으로 돌아감
				

			}
		}
		if (fullmenu == "-도우")	// 도우 구분 문자열인 경우
		{
			while (true)			// 도우 데이터 입력 루프
			{
				getline(in, fullmenu);			// 줄 전체 입력
				if (fullmenu == "-에지")		// 에지 구분 연산자면 토핑 루프 이탈
					break;	
				dough = new Dough;				// 인스턴스 동적할당
				fullmenu2 = fullmenu;
				ch = (char*)fullmenu.c_str();	// char로 변환

				token2 = strtok(ch, "	");		// 이름 부분 split
				dough->set_name(token2);

				token2 = strtok(NULL, "	");		// 두께 부분 split
				thickness = atof(token2);		// float로 변환
				dough->set_thickness(thickness);

				token2 = strtok(NULL, "	");		// 추가금액 부분 split
				extra_cost = atoi(token2);		// 정수로 변환
				dough->set_extra_cost(extra_cost);
				
				token2 = strtok(NULL, "	");		// comment 부분 split
				comment = token2;
				dough->set_comment(comment);

				doughlist->add(dough);			// list에 추가

				if (token2 == "") continue;		// 줄의 끝까지 왔으면 루프 처음으로 이동

			}
		}
		if (fullmenu == "-에지")	// 에지 구분 문자열인 경우
		{
			while (true)			// 데이터 입력 루프
			{				
				// 무스 string 배열 초기화
				flag++;
				for (i = 0; i < 3 ; i++)
				mousse[i] = "";
				getline(in, fullmenu);			// 줄 전체 입력
				
				for(int ii=0; ii<fullmenu.length(); ii++)
					dummy[i] = (int)fullmenu[i];			// 이유는 알 수 없으나 이 처리를 해주지 않으면 find 함수에서 index가 비정상적으로 사용된다.
				
				if(fullmenu.length()==0) break;	// 줄 입력이 NULL이면 즉시 종료
				edge = new Edge;				// 인스턴스 동적할당
				fullmenu2 = fullmenu;			// 문자열 복사 - 두 종류의 token을 사용할 예정이기 때문
				checkstring = fullmenu;			// 문자열 복사 - mousse가 존재하지 않아 연속으로 tab이 나오는지 확인할 때 사용
				ch = (char*)fullmenu.c_str();	// char로 변환
				
				token2 = strtok(ch, "	");		// 이름 부분 split
				edge->set_name(token2);

				token2 = strtok(NULL, "	");		// 무스(무스가 없으면 추가금액) 부분 split


				index = checkstring.find("\t");	// 처음 tab이 나오는 위치를 저장
				index2 = index + 1;
				
				// 만약 첫 tab의 위치와 두 번째 tab의 위치 index가 차이가 1이라면, 즉 연속하다면 무스 데이터가 없다.
				if (index + 1 == checkstring.find("	", index2))
				{
					edge->add_mousse(mousse);		// 무스에 빈 배열 반환
					extra_cost = atoi(token2);		// 정수 변환
					edge->set_extra_cost(extra_cost);// 추가금액 입력
					token2 = strtok(NULL, "	");		// comment split
					comment = token2;
					edge->set_comment(comment);
					edgelist->add(edge);			// list에 추가
				}
				else 	// 무스 데이터가 있는 경우 입력받는다.
				{
					fullmousse = token2;
					token2 = strtok(NULL, "	");		// 추가금액 부분 split
					extra_cost = atoi(token2);		// 정수 변환
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
					edgelist->add(edge);			// list에 추가
				}
				
				if (in.eof())		// 파일의 끝에 도달한 경우, 루프 이탈
					break;
			}
		}
		in.close();	// 파일 닫음
		return 0;
	}
	else	// 파일이 존재하지 않는 경우
	{
		cout << "파일이 존재하지 않습니다. 프로그램을 종료합니다." << endl;
		in.close();
		return 1;
	}
}
