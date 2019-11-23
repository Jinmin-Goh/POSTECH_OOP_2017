#include "mainwindow.h"
#include "game.h"
#include "bio.h"
#include "cell.h"
#include "enemy.h"
#include "feed.h"
#include "virus.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(800, 800);
    scene->setSceneRect(0, 0, 800, 800);
    MainWindow mainWindow;
    Game gameWindow;


    int random = 0;
    Bio** bio;
    Cell* cell = new Cell();

    srand(time(NULL));

    for(int i = 0; i < 30; i++)
    {
        random = rand() % 100;
        if(rand() < 70)
            bio[i] = new Feed();
        else if(rand() < 85)
            bio[i] = new Enemy();
        else bio[i] = new Virus();
    }
    for(int i = 0; i < 30; i++)
//        scene->addItem(bio[i]);

    scene->addItem(cell);

//    mainWindow.show();

    view->show();

    return a.exec();
}
