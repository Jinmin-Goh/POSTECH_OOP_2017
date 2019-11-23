#include "mainwindow.h"
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
    // 시간 종록 random seed
    srand(time(NULL));
    QApplication a(argc, argv);
    // MainWindow 클래스 인스턴스 할당
    MainWindow mainWindow;
    // mainwindow를 화면에 출력
    mainWindow.QMainWindow::show();

    return a.exec();
}
