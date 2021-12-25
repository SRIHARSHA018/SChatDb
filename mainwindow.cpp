#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    tasker= new Task_manager(this);
    tasker->Init();
}

MainWindow::~MainWindow()
{
    delete ui;

}


void MainWindow::on_login_btn_clicked()
{

    QJsonObject details;
    details["username"]=ui->username_box->text();
    details["password"]=ui->password_box->text();
    tasker->ValidateLoginDetails(details);
    if(tasker->IsLoginSuccessful()){
       tasker->SetupMainPage(ui->stackedWidget);
    }
    else{
        ui->status_label_login->setStyleSheet("QLabel{color: red}");
        ui->status_label_login->setText(QString::fromStdString("login failed check your username/password and try again"));
    }
}


void MainWindow::on_signup_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_submit_btn_signup_clicked()
{
    QJsonObject details;
    details["username"]=ui->username_box_signup->text();
    details["password"]=ui->password_box_signup->text();
    details["firstname"]=ui->firstname_box_signup->text();
    details["lastname"]=ui->lastname_box_signup->text();
    details["confirmpassword"]=ui->confirmpass_box_signup->text();
    details["contactno"] = ui->mobileno_box_signup->text();
    tasker->ValidateSignUpDetails(details,ui->status_label_signup);
    if(tasker->IsSignUpSuccessful()){
        tasker->SetupLoginPage(ui->stackedWidget);
    }
}

