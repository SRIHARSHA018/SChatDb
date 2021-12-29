#include "task_manager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

Task_manager::Task_manager(QObject *parent)
    : QObject{parent}
{
        connect(this,SIGNAL(enteredMainWindow()),parent,SLOT(on_EnterMainWindow()));
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
        query.exec("SELECT id,username,firstname,lastname,contactno FROM public.users WHERE username='"+username+"';");
        if(query.next()){
            profile_details.id = query.value(0).toInt();
            profile_details.user_name = query.value(1).toString().toStdString();
            profile_details.first_name = query.value(2).toString().toStdString();
            profile_details.last_name = query.value(3).toString().toStdString();
            profile_details.contactno = query.value(4).toString().toStdString();
        }
        else{
            qDebug()<<query.lastError().text();
        }
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
        emit enteredMainWindow();
        x_SetupMainWindowControls();

    }
}

void Task_manager::SetupLoginPage(QStackedWidget *pager)
{
    if(this->GetState()==STATUS::SIGNUP_SUCCESSFUL){
        pager->setCurrentIndex(0);
    }

}

void Task_manager::SetupContacts(QListWidget *contact_list)
{
    QSqlQuery query(this->x_db);
    query.exec("SELECT username FROM public.users WHERE username!='"+QString::fromStdString(profile_details.user_name)+"';");
    while(query.next()){
      qDebug()<<query.value(0);
      contact_list->addItem(query.value(0).toString());
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

void Task_manager::on_ContactSelected(QListWidgetItem *contact, QLabel* name)
{
   // qDebug()<<"Contact selected";
    name->setText(contact->text());
    emit setUpChatConnection(contact->text(),profile_details);

}

void Task_manager::on_SendMessage(QLineEdit *msg)
{
    QSqlQuery query(x_db);
    x_chat_manager->SendChat(msg->text().toStdString());
    //qDebug()<<"reached taskmanager send btn";
    msg->clear();
}

void Task_manager::x_SetupMainWindowControls()
{
    this->x_chat_manager = new ChatManager(this);
    this->x_chat_manager->query = new QSqlQuery(this->x_db);
    this->x_chat_manager->chat_pane = this->chat_pane;
    connect(this,SIGNAL(setUpChatConnection(QString,profile)),x_chat_manager,SLOT(on_SetupChatConnection(QString,profile)));
}


