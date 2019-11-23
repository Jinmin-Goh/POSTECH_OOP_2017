#include "mainwindow.h"
#include "bio.h"
#include "cell.h"
#include "enemy.h"
#include "feed.h"
#include "virus.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"
#include <QGraphicsRectItem>
#include <QList>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // constructor에서 scene와 view를 동적할당 받는다
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    // 출력 옵션 지정
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Game()
{
    // 변수 선언 및 초기화
    int random = 0;

    // cell 동적할당 및 flag, focus 설정하여 키 입력 받을 수 있게 설정
    cell = new Cell();
    cell->setFlag(QGraphicsItem::ItemIsFocusable);
    cell->setFocus();
    // cell의 색 지정
    cell->setBrush(QBrush(Qt::blue, Qt::SolidPattern));

    // 초기 30개의 random bio instance 생성
    for(int i = 0; i < 30; i++)
    {
        // 0~99의 난수 생성
        random = rand() % 100;  // 0~99의 난수 생성
        while(1)
        {
            if(random < 70)
            {
                // 70% 확률로 feed
                bio[i] = new Feed();
                bio[i]->setBrush(QBrush(Qt::green, Qt::SolidPattern));  // feed의 색 지정
            }
            else if(random < 85)
            {
                // 15% 확률로 enemy
                bio[i] = new Enemy();
                bio[i]->setBrush(QBrush(Qt::red, Qt::SolidPattern));    // enemy의 색 지정
            }
            else
            {
                // 15% 확률로 virus
                bio[i] = new Virus();
                bio[i]->setBrush(QBrush(Qt::black, Qt::SolidPattern));  // virus의 색 지정
            }

            // 아래 코드는 생성 시 겹치지 않게 생성하려 시도했던 조건문의 흔적. 잘 되지 않고 잔에러를 유발해 제외했다.
            // 원래대로라면, 겹치는 일이 발생하지 않으면 바로 break로 루프를 이탈하고
            // 겹치는 일이 발생하면 할당받은 bio 인스턴스를 delete한 뒤 다시 생성해 안 겹칠때까지 반복한다.
            /*
            float p = bio[i]->x(), q = bio[i]->y(), r = cell->x(), s = cell->y(), a = bio[i]->getSize(), b = cell->getSize();
            if((p > (r + b)) || ((p + a) < r) || (q > (s + b)) || ((q + a) < s))
                break;
            else
                delete bio[i];
                */
            break;

        }
        // scene에 새로 생성된 인스턴스 추가
        scene->addItem(bio[i]);

    }
    totalNum = 30;

    // scene에 cell 추가
    scene->addItem(cell);

    // timer 지정, connection 설정
    QTimer* newTimer = new QTimer();
    connect(newTimer, SIGNAL(timeout()), this, SLOT(New()));
    newTimer->start(5000);
}

void MainWindow::New()
{
    int random;
    // 5개씩 생성
    for(int i = totalNum ; i < totalNum + 5; i++)
    {
        // 0~99의 난수 생성
        random = rand() % 100;
        while(1)
        {
            // 70% 확률로 feed
            if(random < 70)
            {
                bio[i] = new Feed();
                bio[i]->setBrush(QBrush(Qt::green, Qt::SolidPattern));
            }
            // 15% 확률로 enemy
            else if(random < 85)
            {
                bio[i] = new Enemy();
                bio[i]->setBrush(QBrush(Qt::red, Qt::SolidPattern));
            }
            // 15% 확률로 virus
            else
            {
                bio[i] = new Virus();
                bio[i]->setBrush(QBrush(Qt::black, Qt::SolidPattern));
            }

            // 아래 코드는 생성 시 겹치지 않게 생성하려 시도했던 조건문의 흔적. 잘 되지 않고 잔에러를 유발해 제외했다.
            // 원래대로라면, 겹치는 일이 발생하지 않으면 바로 break로 루프를 이탈하고
            // 겹치는 일이 발생하면 할당받은 bio 인스턴스를 delete한 뒤 다시 생성해 안 겹칠때까지 반복한다.
            /*
            float p = bio[i]->x(), q = bio[i]->y(), r = cell->x(), s = cell->y(), a = bio[i]->getSize(), b = cell->getSize();
            if((p > (r + b)) || ((p + a) < r) || (q > (s + b)) || ((q + a) < s))
                break;
            else
                delete bio[i];
                */
            break;
        }

        // scene에 새로 생성된 인스턴스 추가
        scene->addItem(bio[i]);

    }
    // totalNum 갱신
    totalNum = totalNum + 5;
}


void MainWindow::on_pushButton_2_clicked()
{
    // start game 버튼을 누른 후의 행동
    QMainWindow::hide();    // 초기 화면 숨김
    Game();         // 게임 수행
    view->show();   // 게임 화면 출력
    // view와 scene의 크기 지정
    view->setFixedSize(800, 800);
    scene->setSceneRect(0, 0, 800, 800);
}

void MainWindow::on_pushButton_clicked()
{
    // 초기 화면에서 end game 버튼을 누른 후의 수행
    QMessageBox::about(this, "End game", "게임을 종료합니다.");
    exit(0);
}

void MainWindow::GameOver()
{
    // cell이 사멸한 경우의 게임 종료(패배)
    QMessageBox::about(this, "GameOver", "세포가 죽었습니다. 게임을 종료합니다.");
    exit(0);
}

void MainWindow::GameWin()
{
    // cell이 화면을 덮은 경우의 게임 종료(승리)
    QMessageBox::about(this, "GameWin", "세포가 화면을 덮었습니다. 게임을 종료합니다.");
    exit(0);
}
