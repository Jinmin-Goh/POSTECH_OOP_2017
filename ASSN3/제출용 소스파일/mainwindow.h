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
    QGraphicsScene* getScene();
    QGraphicsView* getView();
    void Game();
    void GameOver();
    void GameWin();

public slots:
    void New();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    int totalNum;
    Bio* bio[10000];
    Cell* cell;
};

#endif // MAINWINDOW_H
