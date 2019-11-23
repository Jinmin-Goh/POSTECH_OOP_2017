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
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Game()
{
    int random = 0;

    cell = new Cell();
    cell->setFlag(QGraphicsItem::ItemIsFocusable);
    cell->setFocus();
    cell->setBrush(QBrush(Qt::blue, Qt::SolidPattern));

    for(int i = 0; i < 30; i++)
    {
        random = rand() % 100;
        while(1)
        {
            if(random < 70)
            {
                bio[i] = new Feed();
                bio[i]->setBrush(QBrush(Qt::green, Qt::SolidPattern));
            }
            else if(random < 85)
            {
                bio[i] = new Enemy();
                bio[i]->setBrush(QBrush(Qt::red, Qt::SolidPattern));
            }
            else
            {
                bio[i] = new Virus();
                bio[i]->setBrush(QBrush(Qt::black, Qt::SolidPattern));
            }
            float p = bio[i]->x(), q = bio[i]->y(), r = cell->x(), s = cell->y(), a = bio[i]->getSize(), b = cell->getSize();
            if((p > (r + b)) || ((p + a) < r) || (q > (s + b)) || ((q + a) < s))
                break;
            else
                delete bio[i];

        }
        scene->addItem(bio[i]);

    }
    totalNum = 30;
    for(int i = 0; i < 30; i++)
        scene->addItem(bio[i]);

    scene->addItem(cell);

    QTimer* newTimer = new QTimer();
    connect(newTimer, SIGNAL(timeout()), this, SLOT(New()));
    newTimer->start(5000);
}

QGraphicsScene* MainWindow::getScene()
{
    return this->scene;
}

QGraphicsView* MainWindow::getView()
{
    return this->view;
}
void MainWindow::New()
{
    int random;
    for(int i = totalNum ; i < totalNum + 5; i++)
    {
        random = rand() % 100;
        while(1)
        {
            if(random < 70)
            {
                bio[i] = new Feed();
                bio[i]->setBrush(QBrush(Qt::green, Qt::SolidPattern));
            }
            else if(random < 85)
            {
                bio[i] = new Enemy();
                bio[i]->setBrush(QBrush(Qt::red, Qt::SolidPattern));
            }
            else
            {
                bio[i] = new Virus();
                bio[i]->setBrush(QBrush(Qt::black, Qt::SolidPattern));
            }
            float p = bio[i]->x(), q = bio[i]->y(), r = cell->x(), s = cell->y(), a = bio[i]->getSize(), b = cell->getSize();
            if((p > (r + b)) || ((p + a) < r) || (q > (s + b)) || ((q + a) < s))
                break;
            else
                delete bio[i];
        }
        scene->addItem(bio[i]);

    }
    totalNum = totalNum + 5;
}


void MainWindow::on_pushButton_2_clicked()
{
    QMainWindow::hide();
    Game();
    view->show();
    view->setFixedSize(800, 800);
    scene->setSceneRect(0, 0, 800, 800);

}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::about(this, "End game", "게임을 종료합니다.");
    exit(0);
}

void MainWindow::GameOver()
{
    QMessageBox::about(this, "GameOver", "세포가 죽었습니다. 게임을 종료합니다.");
    exit(0);
}

void MainWindow::GameWin()
{
    QMessageBox::about(this, "GameWin", "세포가 화면을 덮었습니다. 게임을 종료합니다.");
    exit(0);
}
