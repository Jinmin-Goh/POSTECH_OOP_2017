#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

void ShowMenu();
void CalcRank(int gameCode, int score);
void ShowRank(int gameCode);
void ShowCode();
int GameCheck(string game);

int main()
{
	int gameCode, flag, score;
	string game, menu, dummy;
	while (true)
	{
		ShowMenu();
		cin >> menu;
		cout << endl;
		
		if (menu == "1")
		{
			cout << "********************* 랭크 계산 시스템 *********************" << endl << endl;
			cout << "게임 코드 : ";
			cin >> game;
			gameCode = GameCheck(game);
			if (!gameCode)
			{
				cout << "잘못된 입력입니다. " << endl;
			}
			else
			{
				cout << "게임 스코어 : ";
				cin >> score;
				CalcRank(gameCode, score);
			}
			cout << "메뉴로 돌아가려면 아무 글자나 입력하세요.";
			cin >> dummy;
			continue;
		}
		else if (menu == "2")
		{
			cout << "******************** 게임별 랭크 시스템 ********************" << endl;
			cout << "게임 코드 : ";
			cin >> game;
			gameCode = GameCheck(game);
			ShowRank(gameCode);
			cout << "메뉴로 돌아가려면 아무 글자나 입력하세요.";
			cin >> dummy;
			continue;
		}
		else if (menu == "3")
		{
			cout << "*********************** 게임별 코드 ***********************" << endl;
			ShowCode();
			cout << "메뉴로 돌아가려면 아무 글자나 입력하세요.";
			cin >> dummy;
			continue;
		}
		else if (menu == "0")
			break;
		else continue;
	}
	return 0;
}

void ShowMenu()
{
	// 메뉴 출력 함수
	
	system("cls");
	cout << "*************** Rythm Game Rank Info Program ***************" << endl;
	cout << endl;
	cout << "     * 이 코드는 2017년 9월 23일 시점의 기준을 따릅니다." << endl;
	cout << endl;
	cout << "              >>>>>  메뉴를 선택하세요  <<<<<" << endl;
	cout << endl;
	cout << endl;
	cout << "1. 랭크 확인" << endl;
	cout << "2. 게임별 랭크 시스템 확인" << endl;
	cout << "3. 게임 코드 확인" << endl;
	cout << "0. 종료" << endl;
	cout << endl;
	cout << "메뉴 : ";
	
}

void CalcRank(int gameCode, int score)
{
	//cout << "랭크 계산 함수" << endl;

	cout << endl;
	if (gameCode == 1)
	{
		if (score > 1000000 || score < 0) 
		{
			cout << "잘못된 입력입니다." << endl;
			return;
		}
		cout << "Your game : jubeat" << endl << "Your score : " << score << endl;
		if (score == 1000000) cout << "Your rank : EXC" << endl;
		else if (score > 980000) cout << "Your rank : SSS" << endl;
		else if (score > 950000) cout << "Your rank : SS" << endl;
		else if (score > 900000) cout << "Your rank : S" << endl;
		else if (score > 850000) cout << "Your rank : A" << endl;
		else if (score > 800000) cout << "Your rank : B" << endl;
		else if (score > 700000) cout << "Your rank : C" << endl;
		else if (score > 500000) cout << "Your rank : D" << endl;
		else cout << "Your rank : E" << endl;
	}
	if (gameCode == 2)
	{

		if (score > 10000000 || score < 0)
		{
			cout << "잘못된 입력입니다." << endl;
			return;
		}
		cout << "Your game : SOUND VOLTEX" << endl << "Your score : " << score << endl;
		
		if (score == 10000000) cout << "Your rank : PUC" << endl;
		else if (score > 9900000) cout << "Your rank : S" << endl;
		else if (score > 9800000) cout << "Your rank : AAA+" << endl;
		else if (score > 9700000) cout << "Your rank : AAA" << endl;
		else if (score > 9500000) cout << "Your rank : AA+" << endl;
		else if (score > 9300000) cout << "Your rank : AA" << endl;
		else if (score > 9000000) cout << "Your rank : A+" << endl;
		else if (score > 8700000) cout << "Your rank : A" << endl;
		else if (score > 7500000) cout << "Your rank : B" << endl;
		else if (score > 6500000) cout << "Your rank : C" << endl;
		else cout << "Your rank : D" << endl;
	}
	if (gameCode == 3)
	{
		if (score > 100000 || score < 0) 
		{
			cout << "잘못된 입력입니다." << endl;
			return;
		}
		cout << "Your game : pop'n music" << endl << "Your score : " << score << endl;
		if (score > 98000) cout << "Your rank : S" << endl;
		else if (score > 95000) cout << "Your rank : AAA" << endl;
		else if (score > 90000) cout << "Your rank : AA" << endl;
		else if (score > 82000) cout << "Your rank : A" << endl;
		else if (score > 72000) cout << "Your rank : B" << endl;
		else if (score > 62000) cout << "Your rank : C" << endl;
		else if (score > 50000) cout << "Your rank : D" << endl;
		else cout << "Your rank : E" << endl;
	}
	if (gameCode == 4)
	{
		
		if (score > 1000000 || score < 0)
		{
			cout << "잘못된 입력입니다." << endl;
			return;
		}
		cout << "Your game : Dance Dance Revolution" << endl << "Your score : " << score << endl;
		if (score > 980000) cout << "Your rank : AAA" << endl;
		else if (score > 950000) cout << "Your rank : AA+" << endl;
		else if (score > 900000) cout << "Your rank : AA" << endl;
		else if (score > 890000) cout << "Your rank : AA-" << endl;
		else if (score > 850000) cout << "Your rank : A+" << endl;
		else if (score > 800000) cout << "Your rank : A" << endl;
		else if (score > 790000) cout << "Your rank : A-" << endl;
		else if (score > 750000) cout << "Your rank : B+" << endl;
		else if (score > 700000) cout << "Your rank : B" << endl;
		else if (score > 690000) cout << "Your rank : B-" << endl;
		else if (score > 650000) cout << "Your rank : C+" << endl;
		else if (score > 600000) cout << "Your rank : C" << endl;
		else if (score > 590000) cout << "Your rank : C-" << endl;
		else if (score > 550000) cout << "Your rank : D+" << endl;
		else cout << "Your rank : D" << endl;
	}
	if (gameCode == 5)
	{
		
		if (score > 1000000 || score < 0)
		{
			cout << "잘못된 입력입니다." << endl;
			return;
		}
		cout << "Your game : MÚSECA" << endl << "Your score : " << score << endl;
		if (score == 1000000) cout << "Your rank : 傑(금색)" << endl;
		else if (score > 975000) cout << "Your rank : 傑" << endl;
		else if (score > 950000) cout << "Your rank : 秀" << endl;
		else if (score > 900000) cout << "Your rank : 優" << endl;
		else if (score > 850000) cout << "Your rank : 良" << endl;
		else if (score > 800000) cout << "Your rank : 佳" << endl;
		else if (score > 700000) cout << "Your rank : 凡" << endl;
		else if (score > 600000) cout << "Your rank : 没" << endl;
		else cout << "Your rank : 傑" << endl;
	}
	if (gameCode == 6)
	{
		
		if (score > 1000000 || score < 0)
		{
			cout << "잘못된 입력입니다." << endl;
			return;
		}
		cout << "Your game : NOSTALGIA" << endl << "Your score : " << score << endl;
		if (score == 1000000) cout << "Your rank : Pianist" << endl;
		else if (score > 950000) cout << "Your rank : S" << endl;
		else if (score > 900000) cout << "Your rank : A+" << endl;
		else if (score > 850000) cout << "Your rank : A" << endl;
		else if (score > 800000) cout << "Your rank : B+" << endl;
		else if (score > 750000) cout << "Your rank : B" << endl;
		else if (score > 700000) cout << "Your rank : C" << endl;
		else cout << "Your rank : Failed" << endl;
	}
	if (gameCode == 0)
	{
		cout << "잘못된 입력입니다. " << endl;
	}
	cout << endl;
}

void ShowRank(int gameCode)
{
	//cout << "게임별 랭크 기준 안내 함수" << endl;
	
	cout << endl;
	if (gameCode == 1)
	{
		cout << "1000000		 : EXC" << endl;
		cout << "999999 ~ 980000 : SSS" << endl;
		cout << "979999 ~ 950000 : SS" << endl;
		cout << "949999 ~ 900000 : S" << endl;
		cout << "899999 ~ 850000 : A" << endl;
		cout << "849999 ~ 800000 : B" << endl;
		cout << "799999 ~ 700000 : C" << endl;
		cout << "699999 ~ 500000 : D" << endl;
		cout << "499999 ~        : E" << endl;
	}
	if (gameCode == 2)
	{
		cout << "10000000          : PUC" << endl;
		cout << "9999999 ~ 9900000 : S" << endl;
		cout << "9899999 ~ 9800000 : AAA+" << endl;
		cout << "9799999 ~ 9700000 : AAA" << endl;
		cout << "9699999 ~ 9500000 : AA+" << endl;
		cout << "9499999 ~ 9300000 : AA" << endl;
		cout << "9299999 ~ 9000000 : A+" << endl;
		cout << "8999999 ~ 8700000 : A" << endl;
		cout << "8699999 ~ 7500000 : B" << endl;
		cout << "7499999 ~ 6500000 : C" << endl;
		cout << "6499999 ~         : D" << endl;
	}
	if (gameCode == 3)
	{
		cout << "100000 ~ 98000 : S" << endl;
		cout << "97999 ~ 95000  : AAA" << endl;
		cout << "94999 ~ 90000  : AA" << endl;
		cout << "89999 ~ 82000  : A" << endl;
		cout << "81999 ~ 72000  : B" << endl;
		cout << "71999 ~ 62000  : C" << endl;
		cout << "61999 ~ 50000  : D" << endl;
		cout << "49999 ~        : E" << endl;
	}
	if (gameCode == 4)
	{
		cout << "1000000 ~ 990000 : AAA" << endl;
		cout << "989999 ~ 950000  : AA+" << endl;
		cout << "949999 ~ 900000  : AA" << endl;
		cout << "899999 ~ 890000  : AA-" << endl;
		cout << "889999 ~ 850000  : A+" << endl;
		cout << "849999 ~ 800000  : A" << endl;
		cout << "799999 ~ 790000  : A-" << endl;
		cout << "789999 ~ 750000  : B+" << endl;
		cout << "749999 ~ 700000  : B" << endl;
		cout << "699999 ~ 690000  : B-" << endl;
		cout << "689999 ~ 650000  : C+" << endl;
		cout << "649999 ~ 600000  : C" << endl;
		cout << "599999 ~ 590000  : C-" << endl;
		cout << "589999 ~ 550000  : D+" << endl;
		cout << "549999 ~         : D" << endl;
	}
	if (gameCode == 5)
	{
		cout << "1000000         : 傑(금색)" << endl;
		cout << "999999 ~ 975000 : 傑" << endl;
		cout << "974999 ~ 950000 : 秀" << endl;
		cout << "949999 ~ 900000 : 優" << endl;
		cout << "899999 ~ 850000 : 良" << endl;
		cout << "849999 ~ 800000 : 佳" << endl;
		cout << "799999 ~ 700000 : 凡" << endl;
		cout << "699999 ~ 600000 : 拙" << endl;
		cout << "599999 ~        : 没" << endl;
	}
	if (gameCode == 6)
	{
		cout << "1000000         : Pianist" << endl;
		cout << "999999 ~ 950000 : S" << endl;
		cout << "949999 ~ 900000 : A+" << endl;
		cout << "899999 ~ 850000 : A" << endl;
		cout << "849999 ~ 800000 : B+" << endl;
		cout << "799999 ~ 750000 : B" << endl;
		cout << "749999 ~ 700000 : C" << endl;
		cout << "699999 ~        : Failed" << endl;
	}
	if (gameCode == 0)
	{
		cout << "잘못된 입력입니다. " << endl;
	}
	cout << endl;
}

void ShowCode()
{
	//cout << "게임별 약어 안내 함수" << endl;
	cout << endl;
	cout << "JUBT - jubeat (유비트)" << endl;
	cout << "SDVX - SOUND VOLTEX (사볼)" << endl;
	cout << "POPN - popn' music (팝픈)" << endl;
	cout << "DDRV - Dance Dance Revolution (디디알)" << endl;
	cout << "MUSC - MÚSECA (뮤제카)" << endl;
	cout << "NSTL - NOSTALGIA (노스텔지아)" << endl;
	cout << endl;

}

int GameCheck(string game)
{
	if (game == "JUBT") return 1;
	else if (game == "SDVX") return 2;
	else if (game == "POPN") return 3;
	else if (game == "DDRV") return 4;
	else if (game == "MUSC") return 5;
	else if (game == "NSTL") return 6;
	else return 0;
}

/*
gameCode

1 : JUBT (유비트)
2 : SDVX (사볼)
3 : POPN (팝픈)
4 : DDRV (디디알)
5 : MUSC (뮤제카)
6 : NSTL (노스텔지아)
*/