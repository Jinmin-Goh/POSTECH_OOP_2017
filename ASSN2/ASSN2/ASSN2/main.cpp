#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include "Object.h"
#include "Torpedo.h"
#include "Boat.h"
#include "BoatA.h"
#include "BoatB.h"
#include "BoatC.h"
using namespace std;


void showInitMenu();
void initMap(char** mapArray, int xAxisLength, int yAxisLength);
void printMap(char **mapArray, int xAxisLength, int yAxisLength, int boatNum, int torpedoNum, int attempt, int score);
bool checkBoatCollision(BoatA **boatAArray, BoatB **boatBArray, BoatC **boatCArray, int boatANum, int boatBNum, int boatCNum, int xAxisLength, int yAxisLength, int attempt);

enum scoreNum		//배의 종류와 상황별 점수 부여 상수 정의
{
	BoatAScore = 100,
	BoatBScore = 200,
	BoatCScore = 300,
	AttemptScore = 50,
	TorpedoScore = 200
};

int main()
{
	//변수 정의
	int xAxisLength, yAxisLength, boatNum, attempt, torpedoNum = 0, score = 0, boatANum = 0, boatBNum = 0, boatCNum = 0, mapBoatANum, mapBoatBNum, mapBoatCNum, leftTorpedoNum = 0, mapTorpedoNum = 0;
	bool endType, flag;
	string menuNum, userInput;
	BoatA **boatAArray = NULL;
	BoatB **boatBArray = NULL;
	BoatC **boatCArray = NULL;
	Torpedo **torpedoArray = NULL;
	Boat user;

	srand(time(NULL));
	
	//메뉴가 1 혹은 2인 경우만 메뉴 실행
	while (true)
	{
		//초기 메뉴 출력
		system("cls");			//linux에서 교체 필요
		showInitMenu();
		getline(cin, menuNum);

		if (menuNum == "1")			//default game
		{
			//값 초기화
			score = 0;
			xAxisLength = 5;
			yAxisLength = 10;
			boatNum = 5;
			torpedoNum = 2 * boatNum;
			attempt = boatNum * (xAxisLength + yAxisLength);
			leftTorpedoNum = torpedoNum;
			mapTorpedoNum = torpedoNum;

			//지도의 동적할당
			char **mapArray = new char*[xAxisLength];
			for (int i = 0; i < xAxisLength; i++) {
				mapArray[i] = new char[yAxisLength + 1];
				mapArray[i][yAxisLength] = 0;
			}
			
			//어뢰 배열 동적할당

			torpedoArray = new Torpedo*[torpedoNum];
			for (int t = 0; t < torpedoNum; t++)
				torpedoArray[t] = new Torpedo;

			//좌표 확인 루프 - 좌표가 배들끼리 서로 안 겹치게 반복하는 루프
			while (true)
			{
				//random으로 보트의 수 결정 - 개수를 나누는 두 개의 벽 설정
				int sep1 = rand() % (boatNum + 1);
				int sep2 = rand() % (boatNum + 1);

				if (sep1 < sep2)
				{
					boatANum = sep1;
					boatBNum = sep2 - sep1;
					boatCNum = boatNum - sep2;
				}
				else
				{
					boatANum = sep2;
					boatBNum = sep1 - sep2;
					boatCNum = boatNum - sep1;
				}

				mapBoatANum = boatANum;
				mapBoatBNum = boatBNum;
				mapBoatCNum = boatCNum;

				//boat 배열 동적할당 - 보트 수가 0이 아니면 할당하고 0이면 포인터에 NULL을 대입
				if (boatANum)
				{
					boatAArray = new BoatA*[boatANum];
					for (int i = 0; i < boatANum; i++)
						boatAArray[i] = new BoatA;
				}
				else boatAArray = NULL;
				
				if (boatBNum)
				{
					boatBArray = new BoatB*[boatBNum];
					for (int i = 0; i < boatBNum; i++)
						boatBArray[i] = new BoatB;
				}
				else boatBArray = NULL;
				
				if (boatCNum)
				{
					boatCArray = new BoatC*[boatCNum];
					for (int i = 0; i < boatCNum; i++)
						boatCArray[i] = new BoatC;
				}
				else boatCArray = NULL;
				
				//충돌 확인
				bool flag = checkBoatCollision(boatAArray, boatBArray, boatCArray, boatANum, boatBNum, boatCNum, xAxisLength, yAxisLength, attempt);
								
				if (flag) break;		//겹치지 않으면 위치 할당 루프 이탈
				else					//겹치는 경우 할당된 메모리 반환 후 루프 재시작
				{
					for (int a = 0; a < boatANum; a++)
						delete boatAArray[a];
					for (int b = 0; b < boatBNum; b++)
						delete boatBArray[b];
					for (int c = 0; c < boatCNum; c++)
						delete boatCArray[c];

					if (boatAArray)
						delete[] boatAArray;
					if (boatBArray)
						delete [] boatBArray;
					if (boatCArray)
						delete [] boatCArray;

					continue;
				}
			}
			
			//user 초기화
			user.setAxisX((int) xAxisLength / 2);
			user.setAxisY(yAxisLength - 1);
			user.setVisibility(Boat::Visible);

			//게임 루프 - 한 루프가 한 턴을 의미
			while (true)
			{
				//게임 승리 조건
				if (!mapBoatANum && !mapBoatBNum && !mapBoatCNum)
				{
					endType = true;
					break;
				}
				
				//게임 패배 조건 - 어뢰 소진 및 map 내 어뢰가 없음
				else if (!leftTorpedoNum && !mapTorpedoNum)
				{
					endType = false;
					break;
				}
				
				//게임 패배 조건 - 턴 없음
				else if (!attempt)
				{
					endType = false;
					break;
				}
				

				//맵 갱신
				initMap(mapArray, xAxisLength, yAxisLength);
				for (int a = 0; a < boatANum; a++)
					if (boatAArray[a]->getBoatStatus() && boatAArray[a]->getVisibility())
						mapArray[boatAArray[a]->getAxisX()][boatAArray[a]->getAxisY()] = 'A';
				for (int b = 0; b < boatBNum; b++)
					if (boatBArray[b]->getBoatStatus() && boatBArray[b]->getVisibility())
						mapArray[boatBArray[b]->getAxisX()][boatBArray[b]->getAxisY()] = 'B';
				for (int c = 0; c < boatCNum; c++)
					if (boatCArray[c]->getBoatStatus() && boatCArray[c]->getVisibility())
						mapArray[boatCArray[c]->getAxisX()][boatCArray[c]->getAxisY()] = 'C';
				mapArray[user.getAxisX()][user.getAxisY()] = 'U';
				
				for (int i = 0; i < torpedoNum; i++)
					if (torpedoArray[i]->getTorpedoStatus())
						mapArray[torpedoArray[i]->getAxisX()][torpedoArray[i]->getAxisY()] = '*';
				printMap(mapArray, xAxisLength, yAxisLength, (mapBoatANum + mapBoatBNum + mapBoatCNum), leftTorpedoNum, attempt, score);

				cout << endl << "Enter Command : ";
				getline(cin, userInput);

				//유저 입력별 수행
				if (userInput == "w" || userInput == "W")
				{
					if (!leftTorpedoNum) continue;	//남아있는 어뢰가 없으면 루프의 처음으로 돌아가 재입력받는다.

					//어뢰 활성화 및 위치 초기화
					torpedoArray[torpedoNum - leftTorpedoNum]->setTorpedoStatus(Torpedo::Available);
					torpedoArray[torpedoNum - leftTorpedoNum]->setAxisX(user.getAxisX());
					torpedoArray[torpedoNum - leftTorpedoNum]->setAxisY(yAxisLength - 1);
					leftTorpedoNum--;
				}
				else if (userInput == "a" || userInput == "A")
				{
					if (user.getAxisX() == 0)	//왼쪽 벽에 붙었는데 왼쪽으로 가려 하는 경우 다시 입력받는다
						continue;
					user.moveLeft();
				}
				else if (userInput == "s" || userInput == "S")
				{}	//변화 없음
				else if (userInput == "d" || userInput == "D")
				{
					if (user.getAxisX() == xAxisLength - 1)	//왼쪽 벽에 붙었는데 왼쪽으로 가려 하는 경우 다시 입력받는다
						continue;
					user.moveRight();
				}
				else continue;	//잘못된 입력이면 배의 이동 없이 게임 루프의 처음으로 돌아감 (재입력)

				//보트 전부 이동
				for (int a = 0; a < boatANum; a++)
					if (boatAArray[a]->getBoatStatus())
						boatAArray[a]->move();
				for (int b = 0; b < boatBNum; b++)
					if (boatBArray[b]->getBoatStatus())
						boatBArray[b]->move();
				for (int c = 0; c < boatCNum; c++)
					if (boatCArray[c]->getBoatStatus())
						boatCArray[c]->move();

				//어뢰 이동 및 검사
				for (int t = 0; t < torpedoNum; t++)
				{
					if (torpedoArray[t]->getTorpedoStatus() && (torpedoArray[t]->getAxisY() != 0))
						torpedoArray[t]->move();
					else if (torpedoArray[t]->getTorpedoStatus() && (torpedoArray[t]->getAxisY() == 0))
					{
						torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
						mapTorpedoNum--;
					}
					else if (torpedoArray[t]->getTorpedoStatus() && torpedoArray[t]->getAxisY() == yAxisLength - 2)	//처음 생성된 어뢰는 이동시키지 않는다. 생성이 이동과 같은 한 턴을 소모하므로.
					{}
				}

				//어뢰와 보트 충돌 검사
				for (int t = 0; t < torpedoNum; t++)
				{
					if (torpedoArray[t]->getTorpedoStatus())
					{
						for (int a = 0; a < boatANum; a++)
						{
							if (boatAArray[a]->getBoatStatus() && (boatAArray[a]->getAxisX() == torpedoArray[t]->getAxisX()) && (boatAArray[a]->getAxisY() == torpedoArray[t]->getAxisY()))
							{
								boatAArray[a]->setBoatStatus(Boat::Unavailable);
								torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
								score = score + BoatAScore;
								mapBoatANum--;
								mapTorpedoNum--;
							}
						}
						for (int b = 0; b < boatBNum; b++)
						{
							if (boatBArray[b]->getBoatStatus() && (boatBArray[b]->getAxisX() == torpedoArray[t]->getAxisX()) && (boatBArray[b]->getAxisY() == torpedoArray[t]->getAxisY()))
							{
								boatBArray[b]->setBoatStatus(Boat::Unavailable);
								torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
								score = score + BoatBScore;
								mapBoatBNum--;
								mapTorpedoNum--;
							}
						}
						for (int c = 0; c < boatCNum; c++)
						{
							if (boatCArray[c]->getVisibility() && boatCArray[c]->getBoatStatus() && (boatCArray[c]->getAxisX() == torpedoArray[t]->getAxisX()) && (boatCArray[c]->getAxisY() == torpedoArray[t]->getAxisY()))
							{
								boatCArray[c]->setBoatStatus(Boat::Unavailable);
								torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
								score = score + BoatCScore;
								mapBoatCNum--;
								mapTorpedoNum--;
							}
						}
					}
				}



				//상황 갱신
				attempt--;

			}

			system("cls");
			if (endType)
			{
				cout << "==================" << endl;
				cout << "    Victory!!!" << endl;
				cout << "==================" << endl << endl;
				score = score + attempt * AttemptScore + leftTorpedoNum * TorpedoScore;
			}
			else
			{
				cout << "==================" << endl;
				cout << "    You Lose.." << endl;
				cout << "==================" << endl << endl;
			}
			cout << "Boat Remain : " << mapBoatANum + mapBoatBNum + mapBoatCNum << endl;
			cout << "Attempt Remain : " << attempt << endl;
			cout << "Torpedo(s) Remain : " << leftTorpedoNum << endl;
			cout << "Score : " << score << endl;
			cout << "U want to play again? Y/N  ";
			while (true)
			{
				getline(cin, userInput);
				if (userInput == "Y" || userInput == "y")
				{
					//할당받은 배열 메모리 모두 반환
					for (int a = 0; a < boatANum; a++)
						delete boatAArray[a];
					for (int b = 0; b < boatBNum; b++)
						delete boatBArray[b];
					for (int c = 0; c < boatCNum; c++)
						delete boatCArray[c];
					for (int t = 0; t < torpedoNum; t++)
						delete torpedoArray[t];
					for (int m = 0; m < xAxisLength; m++)
						delete[] mapArray[m];

					delete[] boatAArray;
					delete[] boatBArray;
					delete[] boatCArray;
					delete[] torpedoArray;
					delete[] mapArray;

					flag = true;
					break;
				}
				else if (userInput == "N" || userInput == "n")
				{
					flag = false;
					cout << "Thank you for playing!" << endl;
					break;
				}
				else continue;
			}
			if (flag) continue;
			else break;
		}

		else if (menuNum == "2")	//custom game
		{
			//custom 메뉴 입력 루프
			while (true)
			{
				cout << "X Axis : ";
				cin >> xAxisLength;
				if (!cin)	//입력이 정수가 아닌 경우
				{
					cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					continue;
				}

				cout << "Y Axis : ";
				cin >> yAxisLength;
				if (!cin || yAxisLength == 1)	//입력이 정수가 아닌 경우 혹은 보트가 배치될 수 없는 경우(높이가 1인 경우)
				{
					cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					continue;
				}
				cout << "Boats : ";
				cin >> boatNum;
				if (!cin || ((xAxisLength) * (yAxisLength - 1) < boatNum))	//입력이 정수가 아닌 경우
				{
					cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					continue;
				}
				cin.clear();
				cin.ignore(256, '\n');	//엔터 버퍼 제거

				break;	//모두 입력이 정수이면 루프 이탈
			}
			//변수 초기화
			score = 0;
			torpedoNum = 2 * boatNum;
			attempt = boatNum * (xAxisLength + yAxisLength);
			leftTorpedoNum = torpedoNum;
			mapTorpedoNum = torpedoNum;

			//지도의 동적할당
			char **mapArray = new char*[xAxisLength];
			for (int i = 0; i < xAxisLength; i++) {
				mapArray[i] = new char[yAxisLength + 1];
				mapArray[i][yAxisLength] = 0;
			}

			

			//어뢰 배열 동적할당
			torpedoArray = new Torpedo *[torpedoNum];
			for (int t = 0; t < torpedoNum; t++)
				torpedoArray[t] = new Torpedo(xAxisLength, yAxisLength);

			//좌표 확인 루프 - 좌표가 배들끼리 서로 안 겹치게 반복하는 루프
			while (true)
			{
				//random으로 보트의 수 결정 - 개수를 나누는 두 개의 벽 설정
				int sep1 = rand() % (boatNum + 1);
				int sep2 = rand() % (boatNum + 1);

				if (sep1 < sep2)
				{
					boatANum = sep1;
					boatBNum = sep2 - sep1;
					boatCNum = boatNum - sep2;
				}
				else
				{
					boatANum = sep2;
					boatBNum = sep1 - sep2;
					boatCNum = boatNum - sep1;
				}

				mapBoatANum = boatANum;
				mapBoatBNum = boatBNum;
				mapBoatCNum = boatCNum;

				//boat 배열 동적할당 - 보트 수가 0이 아니면 할당하고 0이면 포인터에 NULL을 대입
				if (boatANum)
				{
					boatAArray = new BoatA*[boatANum];
					for (int i = 0; i < boatANum; i++)
						boatAArray[i] = new BoatA(xAxisLength, yAxisLength);
				}
				else boatAArray = NULL;

				if (boatBNum)
				{
					boatBArray = new BoatB*[boatBNum];
					for (int i = 0; i < boatBNum; i++)
						boatBArray[i] = new BoatB(xAxisLength, yAxisLength);
				}
				else boatBArray = NULL;

				if (boatCNum)
				{
					boatCArray = new BoatC*[boatCNum];
					for (int i = 0; i < boatCNum; i++)
						boatCArray[i] = new BoatC(xAxisLength, yAxisLength);
				}
				else boatCArray = NULL;

				//충돌 확인
				bool flag = checkBoatCollision(boatAArray, boatBArray, boatCArray, boatANum, boatBNum, boatCNum, xAxisLength, yAxisLength, attempt);

				if (flag) break;		//겹치지 않으면 위치 할당 루프 이탈
				else					//겹치는 경우 할당된 메모리 반환 후 루프 재시작
				{
					for (int a = 0; a < boatANum; a++)
						delete boatAArray[a];
					for (int b = 0; b < boatBNum; b++)
						delete boatBArray[b];
					for (int c = 0; c < boatCNum; c++)
						delete boatCArray[c];

					delete[] boatAArray;
					delete[] boatBArray;
					delete[] boatCArray;

					continue;
				}
			}

			//user 초기화
			user.setAxisX((int)xAxisLength / 2);
			user.setAxisY(yAxisLength - 1);
			user.setVisibility(Boat::Visible);

			//게임 루프 - 한 루프가 한 턴을 의미
			while (true)
			{
				//게임 승리 조건
				if (!mapBoatANum && !mapBoatBNum && !mapBoatCNum)
				{
					endType = true;
					break;
				}

				//게임 패배 조건 - 어뢰 소진 및 map 내 어뢰가 없음
				else if (!leftTorpedoNum && !mapTorpedoNum)
				{
					endType = false;
					break;
				}

				//게임 패배 조건 - 턴 없음
				else if (!attempt)
				{
					endType = false;
					break;
				}


				//맵 갱신
				initMap(mapArray, xAxisLength, yAxisLength);
				for (int a = 0; a < boatANum; a++)
					if (boatAArray[a]->getBoatStatus() && boatAArray[a]->getVisibility())
						mapArray[boatAArray[a]->getAxisX()][boatAArray[a]->getAxisY()] = 'A';
				for (int b = 0; b < boatBNum; b++)
					if (boatBArray[b]->getBoatStatus() && boatBArray[b]->getVisibility())
						mapArray[boatBArray[b]->getAxisX()][boatBArray[b]->getAxisY()] = 'B';
				for (int c = 0; c < boatCNum; c++)
					if (boatCArray[c]->getBoatStatus() && boatCArray[c]->getVisibility())
						mapArray[boatCArray[c]->getAxisX()][boatCArray[c]->getAxisY()] = 'C';
				mapArray[user.getAxisX()][user.getAxisY()] = 'U';

				for (int i = 0; i < torpedoNum; i++)
					if (torpedoArray[i]->getTorpedoStatus())
						mapArray[torpedoArray[i]->getAxisX()][torpedoArray[i]->getAxisY()] = '*';
				printMap(mapArray, xAxisLength, yAxisLength, (mapBoatANum + mapBoatBNum + mapBoatCNum), leftTorpedoNum, attempt, score);

				cout << endl << "Enter Command : ";
				getline(cin, userInput);

				//유저 입력별 수행
				if (userInput == "w" || userInput == "W")
				{
					if (!leftTorpedoNum) continue;	//남아있는 어뢰가 없으면 루프의 처음으로 돌아가 재입력받는다.

													//어뢰 활성화 및 위치 초기화
					torpedoArray[torpedoNum - leftTorpedoNum]->setTorpedoStatus(Torpedo::Available);
					torpedoArray[torpedoNum - leftTorpedoNum]->setAxisX(user.getAxisX());
					torpedoArray[torpedoNum - leftTorpedoNum]->setAxisY(yAxisLength - 1);
					leftTorpedoNum--;
				}
				else if (userInput == "a" || userInput == "A")
				{
					if (user.getAxisX() == 0)	//왼쪽 벽에 붙었는데 왼쪽으로 가려 하는 경우 다시 입력받는다
						continue;
					user.moveLeft();
				}
				else if (userInput == "s" || userInput == "S")
				{
				}	//변화 없음
				else if (userInput == "d" || userInput == "D")
				{
					if (user.getAxisX() == xAxisLength - 1)	//왼쪽 벽에 붙었는데 왼쪽으로 가려 하는 경우 다시 입력받는다
						continue;
					user.moveRight();
				}
				else continue;	//잘못된 입력이면 배의 이동 없이 게임 루프의 처음으로 돌아감 (재입력)

								//보트 전부 이동
				for (int a = 0; a < boatANum; a++)
					if (boatAArray[a]->getBoatStatus())
						boatAArray[a]->move();
				for (int b = 0; b < boatBNum; b++)
					if (boatBArray[b]->getBoatStatus())
						boatBArray[b]->move();
				for (int c = 0; c < boatCNum; c++)
					if (boatCArray[c]->getBoatStatus())
						boatCArray[c]->move();

				//어뢰 이동 및 검사
				for (int t = 0; t < torpedoNum; t++)
				{
					if (torpedoArray[t]->getTorpedoStatus() && (torpedoArray[t]->getAxisY() != 0))
						torpedoArray[t]->move();
					else if (torpedoArray[t]->getTorpedoStatus() && (torpedoArray[t]->getAxisY() == 0))
					{
						torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
						mapTorpedoNum--;
					}
					else if (torpedoArray[t]->getTorpedoStatus() && torpedoArray[t]->getAxisY() == yAxisLength - 2)	//처음 생성된 어뢰는 이동시키지 않는다. 생성이 이동과 같은 한 턴을 소모하므로.
					{
					}
				}

				//어뢰와 보트 충돌 검사
				for (int t = 0; t < torpedoNum; t++)
				{
					if (torpedoArray[t]->getTorpedoStatus())
					{
						for (int a = 0; a < boatANum; a++)
						{
							if (boatAArray[a]->getBoatStatus() && (boatAArray[a]->getAxisX() == torpedoArray[t]->getAxisX()) && (boatAArray[a]->getAxisY() == torpedoArray[t]->getAxisY()))
							{
								boatAArray[a]->setBoatStatus(Boat::Unavailable);
								torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
								score = score + BoatAScore;
								mapBoatANum--;
								mapTorpedoNum--;
							}
						}
						for (int b = 0; b < boatBNum; b++)
						{
							if (boatBArray[b]->getBoatStatus() && (boatBArray[b]->getAxisX() == torpedoArray[t]->getAxisX()) && (boatBArray[b]->getAxisY() == torpedoArray[t]->getAxisY()))
							{
								boatBArray[b]->setBoatStatus(Boat::Unavailable);
								torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
								score = score + BoatBScore;
								mapBoatBNum--;
								mapTorpedoNum--;
							}
						}
						for (int c = 0; c < boatCNum; c++)
						{
							if (boatCArray[c]->getVisibility() && boatCArray[c]->getBoatStatus() && (boatCArray[c]->getAxisX() == torpedoArray[t]->getAxisX()) && (boatCArray[c]->getAxisY() == torpedoArray[t]->getAxisY()))
							{
								boatCArray[c]->setBoatStatus(Boat::Unavailable);
								torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
								score = score + BoatCScore;
								mapBoatCNum--;
								mapTorpedoNum--;
							}
						}
					}
				}



				//상황 갱신
				attempt--;

			}

			system("cls");
			if (endType)
			{
				cout << "==================" << endl;
				cout << "    Victory!!!" << endl;
				cout << "==================" << endl << endl;
				score = score + attempt * AttemptScore + leftTorpedoNum * TorpedoScore;
			}
			else
			{
				cout << "==================" << endl;
				cout << "    You Lose.." << endl;
				cout << "==================" << endl << endl;
			}
			cout << "Boat Remain : " << mapBoatANum + mapBoatBNum + mapBoatCNum << endl;
			cout << "Attempt Remain : " << attempt << endl;
			cout << "Torpedo(s) Remain : " << leftTorpedoNum << endl;
			cout << "Score : " << score << endl;
			cout << "U want to play again? Y/N  ";
			while (true)
			{
				getline(cin, userInput);
				if (userInput == "Y" || userInput == "y")
				{
					//할당받은 배열 메모리 모두 반환
					for (int a = 0; a < boatANum; a++)
						delete boatAArray[a];
					for (int b = 0; b < boatBNum; b++)
						delete boatBArray[b];
					for (int c = 0; c < boatCNum; c++)
						delete boatCArray[c];
					for (int t = 0; t < torpedoNum; t++)
						delete torpedoArray[t];
					for (int m = 0; m < xAxisLength; m++)
						delete[] mapArray[m];

					delete[] boatAArray;
					delete[] boatBArray;
					delete[] boatCArray;
					delete[] torpedoArray;
					delete[] mapArray;
					flag = true;
					break;
				}
				else if (userInput == "N" || userInput == "n")
				{
					flag = false;
					cout << "Thank you for playing!" << endl;
					for (int m = 0; m < xAxisLength; m++)
						delete[] mapArray[m];
					delete[] mapArray;
					break;
				}
				else continue;
			}
			if (flag) continue;
			else break;
		}

		else break; //프로그램 종료
	}

	//할당받은 배열 메모리 모두 반환
	for (int a = 0; a < boatANum; a++)
		delete boatAArray[a];
	for (int b = 0; b < boatBNum; b++)
		delete boatBArray[b];
	for (int c = 0; c < boatCNum; c++)
		delete boatCArray[c];
	for (int t = 0; t < torpedoNum; t++)
		delete torpedoArray[t];

	delete[] boatAArray;
	delete[] boatBArray;
	delete[] boatCArray;
	delete[] torpedoArray;

	return 0;
}

void showInitMenu()		//초기 메뉴를 출력하는 함수
{
	cout << "==========================" << endl;
	cout << "welcome to torpedo game!" << endl << endl;
	cout << "1. start default game!" << endl;
	cout << "2. start custom game!" << endl << endl;
	cout << "else. quit" << endl;
	cout << "==========================" << endl << endl;
	cout << "your command : ";
}
void initMap(char** mapArray, int xAxisLength, int yAxisLength)	//mapArray를 모두 ~로 초기화하는 함수
{
	for (int i = 0; i < xAxisLength; i++)
	{
		for (int j = 0; j < yAxisLength; j++)
			mapArray[i][j] = '~';
	}
}
void printMap(char **mapArray, int xAxisLength, int yAxisLength, int boatNum, int torpedoNum, int attempt, int score)	//매 회마다 mapArray를 가시적으로 출력하는 함수
{
	system("cls");	// linux에서 교체할것

	cout << "Boat(s) Remain : " << boatNum << endl;
	cout << "Attempt(s) Remain : " << attempt << endl;
	cout << "Torpedo(s) Remain : " << torpedoNum << endl;
	cout << "Score : " << score << endl;

	for (int i = 0; i < (2 * xAxisLength + 5); i++)
		cout << "=";
	cout << endl;

	for (int i = 0; i < yAxisLength; i++)
	{
		cout << "|| ";
		for (int j = 0; j < xAxisLength; j++)
		{
			cout << mapArray[j][i] << " ";
		}
		cout << "||"<< endl;
	}
	for (int i = 0; i < (2 * xAxisLength + 5); i++)
		cout << "=";
	cout << endl;
}
bool checkBoatCollision(BoatA **boatAArray, BoatB **boatBArray, BoatC **boatCArray, int boatANum, int boatBNum, int boatCNum, int xAxisLength, int yAxisLength, int attempt)	//배들이 충돌하거나, 벽 너머로 가거나, 유저 부분을 침범하는 경우가 발생하는지 체크하는 함수. 충돌하면 false, 그렇지 않으면 true를 반환
{
	if (attempt >= 12)	//전체 횟수가 12 이상인 경우는 12회마다 전체 배의 움직임이 반복되므로 12회만 체크
	{
		for (int i = 0; i < 12; i++)
		{
			//보트가 벽을 넘거나 유저 영역을 침범하는지 확인
			for (int a = 0; a < boatANum; a++)
				if ((boatAArray[a]->getAxisX() < 0) || (boatAArray[a]->getAxisX() >= xAxisLength) || (boatAArray[a]->getAxisY() < 0) || (boatAArray[a]->getAxisY() >= yAxisLength - 1)) return false;
			for (int b = 0; b < boatBNum; b++)
				if ((boatBArray[b]->getAxisX() < 0) || (boatBArray[b]->getAxisX() >= xAxisLength) || (boatBArray[b]->getAxisY() < 0) || (boatBArray[b]->getAxisY() >= yAxisLength - 1)) return false;
			for (int c = 0; c < boatCNum; c++)
				if ((boatCArray[c]->getAxisX() < 0) || (boatCArray[c]->getAxisX() >= xAxisLength) || (boatCArray[c]->getAxisY() < 0) || (boatCArray[c]->getAxisY() >= yAxisLength - 1)) return false;
			
			//A 끼리 충돌하는지 확인
			for (int a1 = 0; a1 < boatANum - 1; a1++)
			{
				for (int a2 = a1 + 1; a2 < boatANum; a2++)
				{
					if ((boatAArray[a1]->getAxisX() == boatAArray[a2]->getAxisX()) && (boatAArray[a1]->getAxisY() == boatAArray[a2]->getAxisY()))
						return false;
				}
			}

			//B 끼리 충돌하는지 확인
			for (int b1 = 0; b1 < boatBNum - 1; b1++)
			{
				for (int b2 = b1 + 1; b2 < boatBNum; b2++)
				{
					if ((boatBArray[b1]->getAxisX() == boatBArray[b2]->getAxisX()) && (boatBArray[b1]->getAxisY() == boatBArray[b2]->getAxisY()))
						return false;
				}
			}

			//C 끼리 충돌하는지 확인
			for (int c1 = 0; c1 < boatCNum - 1; c1++)
			{
				for (int c2 = c1 + 1; c2 < boatCNum; c2++)
				{
					if (boatCArray[c1]->getVisibility() && boatCArray[c2]->getVisibility() && (boatCArray[c1]->getAxisX() == boatCArray[c2]->getAxisX()) && (boatCArray[c1]->getAxisY() == boatCArray[c2]->getAxisY()))
						return false;
				}
			}
			
			//A 와 B 가 충돌하는지 확인
			for (int a = 0; a < boatANum; a++)
			{
				for (int b = 0; b < boatBNum; b++)
				{
					if ((boatAArray[a]->getAxisX() == boatBArray[b]->getAxisX()) && (boatAArray[a]->getAxisY() == boatBArray[b]->getAxisY()))
						return false;
				}
			}

			//A 와 C 가 충돌하는지 확인
			for (int a = 0; a < boatANum; a++)
			{
				for (int c = 0; c < boatCNum; c++)
				{
					if (boatCArray[c]->getVisibility() && (boatAArray[a]->getAxisX() == boatCArray[c]->getAxisX()) && (boatAArray[a]->getAxisY() == boatCArray[c]->getAxisY()))
						return false;
				}
			}

			//B 와 C 가 충돌하는지 확인
			for (int c = 0; c < boatCNum; c++)
			{
				for (int b = 0; b < boatBNum; b++)
				{
					if (boatCArray[c]->getVisibility() && (boatCArray[c]->getAxisX() == boatBArray[b]->getAxisX()) && (boatCArray[c]->getAxisY() == boatBArray[b]->getAxisY()))
						return false;
				}
			}

		
			//충돌하는 경우가 없으면 보트를 전부 이동시킨다
			for (int a = 0; a < boatANum; a++)
				boatAArray[a]->move();
			for (int b = 0; b < boatBNum; b++)
				boatBArray[b]->move();
			for (int c = 0; c < boatCNum; c++)
				boatCArray[c]->move();
		}

		// 보트가 12번 이동할 동안 하나도 충돌하지 않는 경우, 즉 보트의 충돌이 없는 경우 - 이 경우 보트의 위치는 처음 할당된 위치와 동일. 추가 이동 없이 true 반환 후 함수 종료
		return true;
	}
	else
	{
		//가능 횟수만큼 확인
		for (int i = 0; i < attempt; i++)
		{
			//보트가 벽을 넘거나 유저 영역을 침범하는지 확인
			for (int a = 0; a < boatANum; a++)
				if ((boatAArray[a]->getAxisX() < 0) || (boatAArray[a]->getAxisX() >= xAxisLength) || (boatAArray[a]->getAxisY() < 0) || (boatAArray[a]->getAxisY() >= yAxisLength - 1)) return false;
			for (int b = 0; b < boatBNum; b++)
				if ((boatBArray[b]->getAxisX() < 0) || (boatBArray[b]->getAxisX() >= xAxisLength) || (boatBArray[b]->getAxisY() < 0) || (boatBArray[b]->getAxisY() >= yAxisLength - 1)) return false;
			for (int c = 0; c < boatCNum; c++)
				if ((boatCArray[c]->getAxisX() < 0) || (boatCArray[c]->getAxisX() >= xAxisLength) || (boatCArray[c]->getAxisY() < 0) || (boatCArray[c]->getAxisY() >= yAxisLength - 1)) return false;

			//A 끼리 충돌하는지 확인
			for (int a1 = 0; a1 < boatANum - 1; a1++)
			{
				for (int a2 = a1 + 1; a2 < boatANum; a2++)
				{
					if ((boatAArray[a1]->getAxisX() == boatAArray[a2]->getAxisX()) && (boatAArray[a1]->getAxisY() == boatAArray[a2]->getAxisY()))
						return false;
				}
			}

			//B 끼리 충돌하는지 확인
			for (int b1 = 0; b1 < boatBNum - 1; b1++)
			{
				for (int b2 = b1 + 1; b2 < boatBNum; b2++)
				{
					if ((boatBArray[b1]->getAxisX() == boatBArray[b2]->getAxisX()) && (boatBArray[b1]->getAxisY() == boatBArray[b2]->getAxisY()))
						return false;
				}
			}

			//C 끼리 충돌하는지 확인
			for (int c1 = 0; c1 < boatCNum - 1; c1++)
			{
				for (int c2 = c1 + 1; c2 < boatCNum; c2++)
				{
					if (boatCArray[c1]->getVisibility() && boatCArray[c2]->getVisibility() && (boatCArray[c1]->getAxisX() == boatCArray[c2]->getAxisX()) && (boatCArray[c1]->getAxisY() == boatCArray[c2]->getAxisY()))
						return false;
				}
			}

			//A 와 B 가 충돌하는지 확인
			for (int a = 0; a < boatANum; a++)
			{
				for (int b = 0; b < boatBNum; b++)
				{
					if ((boatAArray[a]->getAxisX() == boatBArray[b]->getAxisX()) && (boatAArray[a]->getAxisY() == boatBArray[b]->getAxisY()))
						return false;
				}
			}

			//A 와 C 가 충돌하는지 확인
			for (int a = 0; a < boatANum; a++)
			{
				for (int c = 0; c < boatCNum; c++)
				{
					if (boatCArray[c]->getVisibility() && (boatAArray[a]->getAxisX() == boatCArray[c]->getAxisX()) && (boatAArray[a]->getAxisY() == boatCArray[c]->getAxisY()))
						return false;
				}
			}

			//B 와 C 가 충돌하는지 확인
			for (int c = 0; c < boatCNum; c++)
			{
				for (int b = 0; b < boatBNum; b++)
				{
					if (boatCArray[c]->getVisibility() && (boatCArray[c]->getAxisX() == boatBArray[b]->getAxisX()) && (boatCArray[c]->getAxisY() == boatBArray[b]->getAxisY()))
						return false;
				}
			}

			//충돌하는 경우가 없으면 보트를 전부 이동시킨다
			for (int a = 0; a < boatANum; a++)
				boatAArray[a]->move();
			for (int b = 0; b < boatBNum; b++)
				boatBArray[b]->move();
			for (int c = 0; c < boatANum; c++)
				boatCArray[c]->move();
		}

		//보트가 attempt 수 동안 이동할 동안 하나도 충돌하지 않는 경우, 즉 보트의 충돌이 없는 경우
		//12 - attempt 회 이동시켜 원위치 후 true 반환 후 함수 종료
		for (int i = 0; i < 12 - attempt; i++)
		{
			for (int a = 0; a < boatANum; a++)
				boatAArray[a]->move();
			for (int b = 0; b < boatBNum; b++)
				boatBArray[b]->move();
			for (int c = 0; c < boatANum; c++)
				boatCArray[c]->move();
		}	
		return true;
	}
}
