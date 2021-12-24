#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    tasker= new Task_manager(this);

}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_login_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_signup_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_submit_btn_signup_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

