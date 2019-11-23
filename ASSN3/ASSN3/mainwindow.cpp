#include "mainwindow.h"
#include "game.h"
#include "ui_mainwindow.h"
#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
//    Game* game = new Game(this);
//    game->show(); //show the class's new window
    hide();

}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::about(this, "End game", "게임을 종료합니다.");
    exit(0);
}
