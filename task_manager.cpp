#include "task_manager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

Task_manager::Task_manager(QObject *parent)
    : QObject{parent}
{
}

void Task_manager::Init()
{
    x_db = QSqlDatabase::addDatabase("QPSQL");
    x_db.setHostName("localhost");
    x_db.setUserName("postgres");
    x_db.setPassword("Sj@&15634");
    x_db.setDatabaseName("Schat");
    x_db.setPort(5432);
    if(x_db.open()){
        qDebug()<<"DatabaseConnected";
    }
    else{
        qDebug()<<"failed";
    }
}

void Task_manager::ValidateLoginDetails(const QJsonObject &details)
{
    QSqlQuery query(x_db);
    auto username = details["username"].toString();
    auto password = details["password"].toString();
    query.exec( QString("SELECT username,password FROM public.users WHERE username='"+username+"' AND password='"+password+"';"));
    if(query.next()){
        qDebug()<<"User details are correct";
        this->SetState(STATUS::LOGIN_SUCCESSFUL);
    }
    else{
        qDebug()<<query.lastError();
        this->SetState(STATUS::LOGIN_FAILED);
    }
}

void Task_manager::ValidateSignUpDetails(const QJsonObject &details, QLabel* status)
{
    QSqlQuery query(x_db);
    auto username = details["username"].toString();
    auto password = details["password"].toString();
    auto confirmpassword = details["confirmpassword"].toString();
    auto firstname = details["firstname"].toString();
    auto lastname = details["lastname"].toString();
    auto contactno = details["contactno"].toString();
    if(username.length()!=0 && firstname.length()!=0 && lastname.length()!=0 && contactno.length()!=0 && password.length()>=6){
        if(password!=confirmpassword){
            this->SetState(STATUS::SIGNUP_FAILED);
            status->setStyleSheet("QLabel{color: red}");
            status->setText(QString::fromStdString("confirm password and password should be same."));
        }
        else if(query.exec("INSERT INTO public.users (username,password,firstname,lastname,contactno) VALUES ('"+username+"','"+password+"','"+ firstname + "', '" + lastname + "', '" + contactno + "');")){
            this->SetState(STATUS::SIGNUP_SUCCESSFUL);
        }
        else{
            qDebug()<<query.lastError();
        }
    }
    else{
        if(password.length()<6){
            this->SetState(STATUS::SIGNUP_FAILED);
            status->setStyleSheet("QLabel{color: red}");
            status->setText(QString::fromStdString("atleast 6 characters for password"));
        }
        else{
            this->SetState(STATUS::SIGNUP_FAILED);
            status->setStyleSheet("QLabel{color: red}");
            status->setText(QString::fromStdString("All fields are mandatory."));
        }
    }

}

void Task_manager::SetupMainPage(QStackedWidget *pager)
{
    if(this->GetState()==STATUS::LOGIN_SUCCESSFUL){
        pager->setCurrentIndex(2);
    }
}

void Task_manager::SetupLoginPage(QStackedWidget *pager)
{
    if(this->GetState()==STATUS::SIGNUP_SUCCESSFUL){
        pager->setCurrentIndex(0);
    }

}

STATUS Task_manager::GetState()
{
    return this->x_state;
}

void Task_manager::SetState(STATUS status)
{
    this->x_state = status;
}

bool Task_manager::IsLoginSuccessful()
{
    return (this->GetState()==STATUS::LOGIN_SUCCESSFUL);
}

bool Task_manager::IsSignUpSuccessful()
{
    return (this->GetState()==STATUS::SIGNUP_SUCCESSFUL);
}


