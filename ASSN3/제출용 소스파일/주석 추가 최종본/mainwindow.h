#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QObject>
#include "bio.h"
#include "cell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Game();        // 실제 게임이 진행되는 함수
    void GameOver();    // 세포가 사멸하면 messagebox를 띄운다.
    void GameWin();     // 세포가 화면을 덮으면 messagebox를 띄운다.

public slots:
    void New();     // 5개씩 새로운 cell을 제외한 bio 객체를 생

private slots:
    void on_pushButton_2_clicked();     // Play Game 버튼 클릭 시 행동
    void on_pushButton_clicked();       // End Game 버튼 클릭 시 행동

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;  // 메인 게임의 scene
    QGraphicsView* view;    // 메인 게임의 view
    int totalNum;           // 총 생성된 객체의 수를 저장
    Bio* bio[10000];        // 객체의 본체 인스턴스를 저장하는 배열
    Cell* cell;             // 사용자 cell
};

#endif // MAINWINDOW_H
