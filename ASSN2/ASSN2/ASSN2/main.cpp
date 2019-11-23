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

enum scoreNum		//���� ������ ��Ȳ�� ���� �ο� ��� ����
{
	BoatAScore = 100,
	BoatBScore = 200,
	BoatCScore = 300,
	AttemptScore = 50,
	TorpedoScore = 200
};

int main()
{
	//���� ����
	int xAxisLength, yAxisLength, boatNum, attempt, torpedoNum = 0, score = 0, boatANum = 0, boatBNum = 0, boatCNum = 0, mapBoatANum, mapBoatBNum, mapBoatCNum, leftTorpedoNum = 0, mapTorpedoNum = 0;
	bool endType, flag;
	string menuNum, userInput;
	BoatA **boatAArray = NULL;
	BoatB **boatBArray = NULL;
	BoatC **boatCArray = NULL;
	Torpedo **torpedoArray = NULL;
	Boat user;

	srand(time(NULL));
	
	//�޴��� 1 Ȥ�� 2�� ��츸 �޴� ����
	while (true)
	{
		//�ʱ� �޴� ���
		system("cls");			//linux���� ��ü �ʿ�
		showInitMenu();
		getline(cin, menuNum);

		if (menuNum == "1")			//default game
		{
			//�� �ʱ�ȭ
			score = 0;
			xAxisLength = 5;
			yAxisLength = 10;
			boatNum = 5;
			torpedoNum = 2 * boatNum;
			attempt = boatNum * (xAxisLength + yAxisLength);
			leftTorpedoNum = torpedoNum;
			mapTorpedoNum = torpedoNum;

			//������ �����Ҵ�
			char **mapArray = new char*[xAxisLength];
			for (int i = 0; i < xAxisLength; i++) {
				mapArray[i] = new char[yAxisLength + 1];
				mapArray[i][yAxisLength] = 0;
			}
			
			//��� �迭 �����Ҵ�

			torpedoArray = new Torpedo*[torpedoNum];
			for (int t = 0; t < torpedoNum; t++)
				torpedoArray[t] = new Torpedo;

			//��ǥ Ȯ�� ���� - ��ǥ�� ��鳢�� ���� �� ��ġ�� �ݺ��ϴ� ����
			while (true)
			{
				//random���� ��Ʈ�� �� ���� - ������ ������ �� ���� �� ����
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

				//boat �迭 �����Ҵ� - ��Ʈ ���� 0�� �ƴϸ� �Ҵ��ϰ� 0�̸� �����Ϳ� NULL�� ����
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
				
				//�浹 Ȯ��
				bool flag = checkBoatCollision(boatAArray, boatBArray, boatCArray, boatANum, boatBNum, boatCNum, xAxisLength, yAxisLength, attempt);
								
				if (flag) break;		//��ġ�� ������ ��ġ �Ҵ� ���� ��Ż
				else					//��ġ�� ��� �Ҵ�� �޸� ��ȯ �� ���� �����
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
			
			//user �ʱ�ȭ
			user.setAxisX((int) xAxisLength / 2);
			user.setAxisY(yAxisLength - 1);
			user.setVisibility(Boat::Visible);

			//���� ���� - �� ������ �� ���� �ǹ�
			while (true)
			{
				//���� �¸� ����
				if (!mapBoatANum && !mapBoatBNum && !mapBoatCNum)
				{
					endType = true;
					break;
				}
				
				//���� �й� ���� - ��� ���� �� map �� ��ڰ� ����
				else if (!leftTorpedoNum && !mapTorpedoNum)
				{
					endType = false;
					break;
				}
				
				//���� �й� ���� - �� ����
				else if (!attempt)
				{
					endType = false;
					break;
				}
				

				//�� ����
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

				//���� �Էº� ����
				if (userInput == "w" || userInput == "W")
				{
					if (!leftTorpedoNum) continue;	//�����ִ� ��ڰ� ������ ������ ó������ ���ư� ���Է¹޴´�.

					//��� Ȱ��ȭ �� ��ġ �ʱ�ȭ
					torpedoArray[torpedoNum - leftTorpedoNum]->setTorpedoStatus(Torpedo::Available);
					torpedoArray[torpedoNum - leftTorpedoNum]->setAxisX(user.getAxisX());
					torpedoArray[torpedoNum - leftTorpedoNum]->setAxisY(yAxisLength - 1);
					leftTorpedoNum--;
				}
				else if (userInput == "a" || userInput == "A")
				{
					if (user.getAxisX() == 0)	//���� ���� �پ��µ� �������� ���� �ϴ� ��� �ٽ� �Է¹޴´�
						continue;
					user.moveLeft();
				}
				else if (userInput == "s" || userInput == "S")
				{}	//��ȭ ����
				else if (userInput == "d" || userInput == "D")
				{
					if (user.getAxisX() == xAxisLength - 1)	//���� ���� �پ��µ� �������� ���� �ϴ� ��� �ٽ� �Է¹޴´�
						continue;
					user.moveRight();
				}
				else continue;	//�߸��� �Է��̸� ���� �̵� ���� ���� ������ ó������ ���ư� (���Է�)

				//��Ʈ ���� �̵�
				for (int a = 0; a < boatANum; a++)
					if (boatAArray[a]->getBoatStatus())
						boatAArray[a]->move();
				for (int b = 0; b < boatBNum; b++)
					if (boatBArray[b]->getBoatStatus())
						boatBArray[b]->move();
				for (int c = 0; c < boatCNum; c++)
					if (boatCArray[c]->getBoatStatus())
						boatCArray[c]->move();

				//��� �̵� �� �˻�
				for (int t = 0; t < torpedoNum; t++)
				{
					if (torpedoArray[t]->getTorpedoStatus() && (torpedoArray[t]->getAxisY() != 0))
						torpedoArray[t]->move();
					else if (torpedoArray[t]->getTorpedoStatus() && (torpedoArray[t]->getAxisY() == 0))
					{
						torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
						mapTorpedoNum--;
					}
					else if (torpedoArray[t]->getTorpedoStatus() && torpedoArray[t]->getAxisY() == yAxisLength - 2)	//ó�� ������ ��ڴ� �̵���Ű�� �ʴ´�. ������ �̵��� ���� �� ���� �Ҹ��ϹǷ�.
					{}
				}

				//��ڿ� ��Ʈ �浹 �˻�
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



				//��Ȳ ����
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
					//�Ҵ���� �迭 �޸� ��� ��ȯ
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
			//custom �޴� �Է� ����
			while (true)
			{
				cout << "X Axis : ";
				cin >> xAxisLength;
				if (!cin)	//�Է��� ������ �ƴ� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					continue;
				}

				cout << "Y Axis : ";
				cin >> yAxisLength;
				if (!cin || yAxisLength == 1)	//�Է��� ������ �ƴ� ��� Ȥ�� ��Ʈ�� ��ġ�� �� ���� ���(���̰� 1�� ���)
				{
					cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					continue;
				}
				cout << "Boats : ";
				cin >> boatNum;
				if (!cin || ((xAxisLength) * (yAxisLength - 1) < boatNum))	//�Է��� ������ �ƴ� ���
				{
					cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
					cin.clear();
					cin.ignore(256, '\n');
					continue;
				}
				cin.clear();
				cin.ignore(256, '\n');	//���� ���� ����

				break;	//��� �Է��� �����̸� ���� ��Ż
			}
			//���� �ʱ�ȭ
			score = 0;
			torpedoNum = 2 * boatNum;
			attempt = boatNum * (xAxisLength + yAxisLength);
			leftTorpedoNum = torpedoNum;
			mapTorpedoNum = torpedoNum;

			//������ �����Ҵ�
			char **mapArray = new char*[xAxisLength];
			for (int i = 0; i < xAxisLength; i++) {
				mapArray[i] = new char[yAxisLength + 1];
				mapArray[i][yAxisLength] = 0;
			}

			

			//��� �迭 �����Ҵ�
			torpedoArray = new Torpedo *[torpedoNum];
			for (int t = 0; t < torpedoNum; t++)
				torpedoArray[t] = new Torpedo(xAxisLength, yAxisLength);

			//��ǥ Ȯ�� ���� - ��ǥ�� ��鳢�� ���� �� ��ġ�� �ݺ��ϴ� ����
			while (true)
			{
				//random���� ��Ʈ�� �� ���� - ������ ������ �� ���� �� ����
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

				//boat �迭 �����Ҵ� - ��Ʈ ���� 0�� �ƴϸ� �Ҵ��ϰ� 0�̸� �����Ϳ� NULL�� ����
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

				//�浹 Ȯ��
				bool flag = checkBoatCollision(boatAArray, boatBArray, boatCArray, boatANum, boatBNum, boatCNum, xAxisLength, yAxisLength, attempt);

				if (flag) break;		//��ġ�� ������ ��ġ �Ҵ� ���� ��Ż
				else					//��ġ�� ��� �Ҵ�� �޸� ��ȯ �� ���� �����
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

			//user �ʱ�ȭ
			user.setAxisX((int)xAxisLength / 2);
			user.setAxisY(yAxisLength - 1);
			user.setVisibility(Boat::Visible);

			//���� ���� - �� ������ �� ���� �ǹ�
			while (true)
			{
				//���� �¸� ����
				if (!mapBoatANum && !mapBoatBNum && !mapBoatCNum)
				{
					endType = true;
					break;
				}

				//���� �й� ���� - ��� ���� �� map �� ��ڰ� ����
				else if (!leftTorpedoNum && !mapTorpedoNum)
				{
					endType = false;
					break;
				}

				//���� �й� ���� - �� ����
				else if (!attempt)
				{
					endType = false;
					break;
				}


				//�� ����
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

				//���� �Էº� ����
				if (userInput == "w" || userInput == "W")
				{
					if (!leftTorpedoNum) continue;	//�����ִ� ��ڰ� ������ ������ ó������ ���ư� ���Է¹޴´�.

													//��� Ȱ��ȭ �� ��ġ �ʱ�ȭ
					torpedoArray[torpedoNum - leftTorpedoNum]->setTorpedoStatus(Torpedo::Available);
					torpedoArray[torpedoNum - leftTorpedoNum]->setAxisX(user.getAxisX());
					torpedoArray[torpedoNum - leftTorpedoNum]->setAxisY(yAxisLength - 1);
					leftTorpedoNum--;
				}
				else if (userInput == "a" || userInput == "A")
				{
					if (user.getAxisX() == 0)	//���� ���� �پ��µ� �������� ���� �ϴ� ��� �ٽ� �Է¹޴´�
						continue;
					user.moveLeft();
				}
				else if (userInput == "s" || userInput == "S")
				{
				}	//��ȭ ����
				else if (userInput == "d" || userInput == "D")
				{
					if (user.getAxisX() == xAxisLength - 1)	//���� ���� �پ��µ� �������� ���� �ϴ� ��� �ٽ� �Է¹޴´�
						continue;
					user.moveRight();
				}
				else continue;	//�߸��� �Է��̸� ���� �̵� ���� ���� ������ ó������ ���ư� (���Է�)

								//��Ʈ ���� �̵�
				for (int a = 0; a < boatANum; a++)
					if (boatAArray[a]->getBoatStatus())
						boatAArray[a]->move();
				for (int b = 0; b < boatBNum; b++)
					if (boatBArray[b]->getBoatStatus())
						boatBArray[b]->move();
				for (int c = 0; c < boatCNum; c++)
					if (boatCArray[c]->getBoatStatus())
						boatCArray[c]->move();

				//��� �̵� �� �˻�
				for (int t = 0; t < torpedoNum; t++)
				{
					if (torpedoArray[t]->getTorpedoStatus() && (torpedoArray[t]->getAxisY() != 0))
						torpedoArray[t]->move();
					else if (torpedoArray[t]->getTorpedoStatus() && (torpedoArray[t]->getAxisY() == 0))
					{
						torpedoArray[t]->setTorpedoStatus(Torpedo::Unavailable);
						mapTorpedoNum--;
					}
					else if (torpedoArray[t]->getTorpedoStatus() && torpedoArray[t]->getAxisY() == yAxisLength - 2)	//ó�� ������ ��ڴ� �̵���Ű�� �ʴ´�. ������ �̵��� ���� �� ���� �Ҹ��ϹǷ�.
					{
					}
				}

				//��ڿ� ��Ʈ �浹 �˻�
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



				//��Ȳ ����
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
					//�Ҵ���� �迭 �޸� ��� ��ȯ
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

		else break; //���α׷� ����
	}

	//�Ҵ���� �迭 �޸� ��� ��ȯ
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

void showInitMenu()		//�ʱ� �޴��� ����ϴ� �Լ�
{
	cout << "==========================" << endl;
	cout << "welcome to torpedo game!" << endl << endl;
	cout << "1. start default game!" << endl;
	cout << "2. start custom game!" << endl << endl;
	cout << "else. quit" << endl;
	cout << "==========================" << endl << endl;
	cout << "your command : ";
}
void initMap(char** mapArray, int xAxisLength, int yAxisLength)	//mapArray�� ��� ~�� �ʱ�ȭ�ϴ� �Լ�
{
	for (int i = 0; i < xAxisLength; i++)
	{
		for (int j = 0; j < yAxisLength; j++)
			mapArray[i][j] = '~';
	}
}
void printMap(char **mapArray, int xAxisLength, int yAxisLength, int boatNum, int torpedoNum, int attempt, int score)	//�� ȸ���� mapArray�� ���������� ����ϴ� �Լ�
{
	system("cls");	// linux���� ��ü�Ұ�

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
bool checkBoatCollision(BoatA **boatAArray, BoatB **boatBArray, BoatC **boatCArray, int boatANum, int boatBNum, int boatCNum, int xAxisLength, int yAxisLength, int attempt)	//����� �浹�ϰų�, �� �ʸӷ� ���ų�, ���� �κ��� ħ���ϴ� ��찡 �߻��ϴ��� üũ�ϴ� �Լ�. �浹�ϸ� false, �׷��� ������ true�� ��ȯ
{
	if (attempt >= 12)	//��ü Ƚ���� 12 �̻��� ���� 12ȸ���� ��ü ���� �������� �ݺ��ǹǷ� 12ȸ�� üũ
	{
		for (int i = 0; i < 12; i++)
		{
			//��Ʈ�� ���� �Ѱų� ���� ������ ħ���ϴ��� Ȯ��
			for (int a = 0; a < boatANum; a++)
				if ((boatAArray[a]->getAxisX() < 0) || (boatAArray[a]->getAxisX() >= xAxisLength) || (boatAArray[a]->getAxisY() < 0) || (boatAArray[a]->getAxisY() >= yAxisLength - 1)) return false;
			for (int b = 0; b < boatBNum; b++)
				if ((boatBArray[b]->getAxisX() < 0) || (boatBArray[b]->getAxisX() >= xAxisLength) || (boatBArray[b]->getAxisY() < 0) || (boatBArray[b]->getAxisY() >= yAxisLength - 1)) return false;
			for (int c = 0; c < boatCNum; c++)
				if ((boatCArray[c]->getAxisX() < 0) || (boatCArray[c]->getAxisX() >= xAxisLength) || (boatCArray[c]->getAxisY() < 0) || (boatCArray[c]->getAxisY() >= yAxisLength - 1)) return false;
			
			//A ���� �浹�ϴ��� Ȯ��
			for (int a1 = 0; a1 < boatANum - 1; a1++)
			{
				for (int a2 = a1 + 1; a2 < boatANum; a2++)
				{
					if ((boatAArray[a1]->getAxisX() == boatAArray[a2]->getAxisX()) && (boatAArray[a1]->getAxisY() == boatAArray[a2]->getAxisY()))
						return false;
				}
			}

			//B ���� �浹�ϴ��� Ȯ��
			for (int b1 = 0; b1 < boatBNum - 1; b1++)
			{
				for (int b2 = b1 + 1; b2 < boatBNum; b2++)
				{
					if ((boatBArray[b1]->getAxisX() == boatBArray[b2]->getAxisX()) && (boatBArray[b1]->getAxisY() == boatBArray[b2]->getAxisY()))
						return false;
				}
			}

			//C ���� �浹�ϴ��� Ȯ��
			for (int c1 = 0; c1 < boatCNum - 1; c1++)
			{
				for (int c2 = c1 + 1; c2 < boatCNum; c2++)
				{
					if (boatCArray[c1]->getVisibility() && boatCArray[c2]->getVisibility() && (boatCArray[c1]->getAxisX() == boatCArray[c2]->getAxisX()) && (boatCArray[c1]->getAxisY() == boatCArray[c2]->getAxisY()))
						return false;
				}
			}
			
			//A �� B �� �浹�ϴ��� Ȯ��
			for (int a = 0; a < boatANum; a++)
			{
				for (int b = 0; b < boatBNum; b++)
				{
					if ((boatAArray[a]->getAxisX() == boatBArray[b]->getAxisX()) && (boatAArray[a]->getAxisY() == boatBArray[b]->getAxisY()))
						return false;
				}
			}

			//A �� C �� �浹�ϴ��� Ȯ��
			for (int a = 0; a < boatANum; a++)
			{
				for (int c = 0; c < boatCNum; c++)
				{
					if (boatCArray[c]->getVisibility() && (boatAArray[a]->getAxisX() == boatCArray[c]->getAxisX()) && (boatAArray[a]->getAxisY() == boatCArray[c]->getAxisY()))
						return false;
				}
			}

			//B �� C �� �浹�ϴ��� Ȯ��
			for (int c = 0; c < boatCNum; c++)
			{
				for (int b = 0; b < boatBNum; b++)
				{
					if (boatCArray[c]->getVisibility() && (boatCArray[c]->getAxisX() == boatBArray[b]->getAxisX()) && (boatCArray[c]->getAxisY() == boatBArray[b]->getAxisY()))
						return false;
				}
			}

		
			//�浹�ϴ� ��찡 ������ ��Ʈ�� ���� �̵���Ų��
			for (int a = 0; a < boatANum; a++)
				boatAArray[a]->move();
			for (int b = 0; b < boatBNum; b++)
				boatBArray[b]->move();
			for (int c = 0; c < boatCNum; c++)
				boatCArray[c]->move();
		}

		// ��Ʈ�� 12�� �̵��� ���� �ϳ��� �浹���� �ʴ� ���, �� ��Ʈ�� �浹�� ���� ��� - �� ��� ��Ʈ�� ��ġ�� ó�� �Ҵ�� ��ġ�� ����. �߰� �̵� ���� true ��ȯ �� �Լ� ����
		return true;
	}
	else
	{
		//���� Ƚ����ŭ Ȯ��
		for (int i = 0; i < attempt; i++)
		{
			//��Ʈ�� ���� �Ѱų� ���� ������ ħ���ϴ��� Ȯ��
			for (int a = 0; a < boatANum; a++)
				if ((boatAArray[a]->getAxisX() < 0) || (boatAArray[a]->getAxisX() >= xAxisLength) || (boatAArray[a]->getAxisY() < 0) || (boatAArray[a]->getAxisY() >= yAxisLength - 1)) return false;
			for (int b = 0; b < boatBNum; b++)
				if ((boatBArray[b]->getAxisX() < 0) || (boatBArray[b]->getAxisX() >= xAxisLength) || (boatBArray[b]->getAxisY() < 0) || (boatBArray[b]->getAxisY() >= yAxisLength - 1)) return false;
			for (int c = 0; c < boatCNum; c++)
				if ((boatCArray[c]->getAxisX() < 0) || (boatCArray[c]->getAxisX() >= xAxisLength) || (boatCArray[c]->getAxisY() < 0) || (boatCArray[c]->getAxisY() >= yAxisLength - 1)) return false;

			//A ���� �浹�ϴ��� Ȯ��
			for (int a1 = 0; a1 < boatANum - 1; a1++)
			{
				for (int a2 = a1 + 1; a2 < boatANum; a2++)
				{
					if ((boatAArray[a1]->getAxisX() == boatAArray[a2]->getAxisX()) && (boatAArray[a1]->getAxisY() == boatAArray[a2]->getAxisY()))
						return false;
				}
			}

			//B ���� �浹�ϴ��� Ȯ��
			for (int b1 = 0; b1 < boatBNum - 1; b1++)
			{
				for (int b2 = b1 + 1; b2 < boatBNum; b2++)
				{
					if ((boatBArray[b1]->getAxisX() == boatBArray[b2]->getAxisX()) && (boatBArray[b1]->getAxisY() == boatBArray[b2]->getAxisY()))
						return false;
				}
			}

			//C ���� �浹�ϴ��� Ȯ��
			for (int c1 = 0; c1 < boatCNum - 1; c1++)
			{
				for (int c2 = c1 + 1; c2 < boatCNum; c2++)
				{
					if (boatCArray[c1]->getVisibility() && boatCArray[c2]->getVisibility() && (boatCArray[c1]->getAxisX() == boatCArray[c2]->getAxisX()) && (boatCArray[c1]->getAxisY() == boatCArray[c2]->getAxisY()))
						return false;
				}
			}

			//A �� B �� �浹�ϴ��� Ȯ��
			for (int a = 0; a < boatANum; a++)
			{
				for (int b = 0; b < boatBNum; b++)
				{
					if ((boatAArray[a]->getAxisX() == boatBArray[b]->getAxisX()) && (boatAArray[a]->getAxisY() == boatBArray[b]->getAxisY()))
						return false;
				}
			}

			//A �� C �� �浹�ϴ��� Ȯ��
			for (int a = 0; a < boatANum; a++)
			{
				for (int c = 0; c < boatCNum; c++)
				{
					if (boatCArray[c]->getVisibility() && (boatAArray[a]->getAxisX() == boatCArray[c]->getAxisX()) && (boatAArray[a]->getAxisY() == boatCArray[c]->getAxisY()))
						return false;
				}
			}

			//B �� C �� �浹�ϴ��� Ȯ��
			for (int c = 0; c < boatCNum; c++)
			{
				for (int b = 0; b < boatBNum; b++)
				{
					if (boatCArray[c]->getVisibility() && (boatCArray[c]->getAxisX() == boatBArray[b]->getAxisX()) && (boatCArray[c]->getAxisY() == boatBArray[b]->getAxisY()))
						return false;
				}
			}

			//�浹�ϴ� ��찡 ������ ��Ʈ�� ���� �̵���Ų��
			for (int a = 0; a < boatANum; a++)
				boatAArray[a]->move();
			for (int b = 0; b < boatBNum; b++)
				boatBArray[b]->move();
			for (int c = 0; c < boatANum; c++)
				boatCArray[c]->move();
		}

		//��Ʈ�� attempt �� ���� �̵��� ���� �ϳ��� �浹���� �ʴ� ���, �� ��Ʈ�� �浹�� ���� ���
		//12 - attempt ȸ �̵����� ����ġ �� true ��ȯ �� �Լ� ����
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
