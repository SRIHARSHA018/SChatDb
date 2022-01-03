#include "task_manager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QImage>
#include <QBuffer>
#include <QPixmap>

Task_manager::Task_manager(QObject *parent)
    : QObject{parent}
{
        connect(this,SIGNAL(enteredMainWindow()),parent,SLOT(on_EnterMainWindow()));
        connect(this,SIGNAL(cleanUpLoginPage()),parent,SLOT(on_cleanUpLoginPage()));
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
        query.exec("SELECT id,username,firstname,lastname,contactno,profile_pic FROM public.users WHERE username='"+username+"';");
        if(query.next()){
            profile_details.id = query.value(0).toInt();
            profile_details.user_name = query.value(1).toString().toStdString();
            profile_details.first_name = query.value(2).toString().toStdString();
            profile_details.last_name = query.value(3).toString().toStdString();
            profile_details.contactno = query.value(4).toString().toStdString();
            if(!query.value(5).isNull()){
                qDebug()<<"feteched image";
                QPixmap image;
                if(image.loadFromData(query.value(5).toByteArray())){
                    profile_details.profile_pic = image;
                }
                //qDebug()<<QString::fromStdString(profile_details.profile_pic);
            }
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

void Task_manager::ValidateGroupInfo(const QJsonObject &details, QLabel *status, QListWidget* members,const std::set<QString>& set_members)
{
    if(details["group_name"].toString().length()==0){
        status->setStyleSheet("QLabel{color: red}");
        status->setText(QString::fromStdString("Please Provide Group Name"));
    }
    else if(details["desc"].toString().length()==0){
        status->setStyleSheet("QLabel{color: red}");
        status->setText(QString::fromStdString("Please Provide Group Description"));
    }
    else if(members->count()==0){
        status->setStyleSheet("QLabel{color: red}");
        status->setText(QString::fromStdString("atleast two members are required to create a group including you"));
    }
    else{
        this->x_createGroup(details,status,members,set_members);
    }

}

void Task_manager::SetupMainPage(QStackedWidget *pager)
{
    if(this->GetState()==STATUS::LOGIN_SUCCESSFUL){
        pager->setCurrentIndex(2);
        emit cleanUpLoginPage();
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
     // qDebug()<<query.value(0);
      contact_list->addItem(query.value(0).toString());
    }

}

void Task_manager::SetupGroups(QListWidget *groups)
{

    QSqlQuery query(this->x_db);
    query.prepare("SELECT group_name,participants FROM public.groups;");
    if(query.exec()){
        while(query.next()){
            auto participants = query.value(1).toString().split(',');
            if(participants.contains(QString::number(this->profile_details.id))){
                  //qDebug()<<query.value(0);
                  groups->addItem(query.value(0).toString());

            }
        }
    }
    else{
        qDebug()<<query.lastError().text();
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

void Task_manager::setUpEditProfileWindow(QStackedWidget *pager)
{
    pager->setCurrentIndex(3);
}

void Task_manager::setProfileDetails(const QJsonObject &details)
{
    QSqlQuery query(this->x_db);
    if(details.contains("username")){
        if(query.exec("UPDATE public.users SET username='"+details["username"].toString()+"' WHERE id='"+QString::number(profile_details.id)+"';")){
            this->profile_details.user_name = details["username"].toString().toStdString();
            qDebug()<<"updated username successfully";
        }
        else{
            qDebug()<<query.lastError().text();
        }
    }
    if(details.contains("firstname")){
        if(query.exec("UPDATE public.users SET firstname='"+details["firstname"].toString()+"' WHERE id='"+QString::number(profile_details.id)+"';")){
            this->profile_details.first_name= details["firstname"].toString().toStdString();
            qDebug()<<"updated firstname successfully";
        }
        else{
            qDebug()<<query.lastError().text();
        }
    }
    if(details.contains("lastname")){
        if(query.exec("UPDATE public.users SET lastname='"+details["lastname"].toString()+"' WHERE id='"+QString::number(profile_details.id)+"';")){
            this->profile_details.last_name = details["lastname"].toString().toStdString();
            qDebug()<<"updated lastname successfully";
        }
        else{
            qDebug()<<query.lastError().text();
        }
    }
    if(details.contains("contactno")){
        if(query.exec("UPDATE public.users SET contactno='"+details["contactno"].toString()+"' WHERE id='"+QString::number(profile_details.id)+"';")){
            this->profile_details.contactno = details["contactno"].toString().toStdString();
            qDebug()<<"updated contactno successfully";
        }
        else{
            qDebug()<<query.lastError().text();
        }
    }
    if(details.contains("password")){
        if(query.exec("UPDATE public.users SET password='"+details["password"].toString()+"' WHERE id='"+QString::number(profile_details.id)+"';")){
            qDebug()<<"updated contactno successfully";
        }
        else{
            qDebug()<<query.lastError().text();
        }
    }


}

void Task_manager::displayDetails(QListWidget *preview, QLabel* profile_pic)
{
    preview->clear();
    preview->addItem(QString::fromStdString("Username: "+this->profile_details.user_name));
    preview->addItem(QString::fromStdString("Firstname: "+this->profile_details.first_name));
    preview->addItem(QString::fromStdString("Lastname: "+this->profile_details.last_name));
    preview->addItem(QString::fromStdString("Phone Number: "+this->profile_details.contactno));
    profile_pic->setPixmap(this->profile_details.profile_pic);
}

void Task_manager::setProfilePic(const std::string &filename)
{
    QSqlQuery query(this->x_db);
    query.prepare("UPDATE public.users SET profile_pic= ? WHERE id = ?;");

    QImage image;
    image.load(QString::fromStdString(filename));
    QByteArray image_bytes;
    QBuffer buffer(&image_bytes);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer,"PNG");
    query.bindValue(0,image_bytes);
    query.bindValue(1,this->profile_details.id);
    if(query.exec()){
        qDebug()<<"insertion of image successful";
        if(this->profile_details.profile_pic.loadFromData(image_bytes)){
            qDebug()<<"profile pic updated successfully";
        }
        else{
            qDebug()<<"Failed to update";
        }
    }
    else{
        qDebug()<<query.lastError().text();
    }

}

void Task_manager::cleanUp()
{
    this->profile_details.profile_pic = QPixmap(DEFAULT_PROFILE_PIC);
}

void Task_manager::on_ContactSelected(QListWidgetItem *contact, QLabel* name,STATUS mode)
{
   // qDebug()<<"Contact selected";
    switch(mode)
    {
    case STATUS::REGULAR_CHAT:
        name->setText(contact->text());
        this->SetState(STATUS::REGULAR_CHAT);
        emit setUpChatConnection(contact->text(),profile_details);
        break;
    case STATUS::GROUP_CHAT:
        name->setText(contact->text());
        this->SetState(STATUS::GROUP_CHAT);
        emit setUpGroupChatConnection(contact->text(),profile_details);
        break;
    default:
        break;
    }
}

void Task_manager::on_SendMessage(QLineEdit *msg)
{
    switch(this->GetState())
    {
    case STATUS::REGULAR_CHAT:
        //QSqlQuery query(x_db);
        qDebug()<<"Regular Chat";
        x_chat_manager->SendChat(msg->text().toStdString());
        //qDebug()<<"reached taskmanager send btn";
        msg->clear();
        break;
    case STATUS::GROUP_CHAT:
        qDebug()<<"Group Chat";
        x_chat_manager->SendGroupChat(msg->text().toStdString());
        msg->clear();
        break;
    default:
        break;
    }

}

void Task_manager::x_SetupMainWindowControls()
{
    this->x_chat_manager = new ChatManager(this);
    this->x_chat_manager->query = new QSqlQuery(this->x_db);
    this->x_chat_manager->chat_pane = this->chat_pane;
    connect(this,SIGNAL(setUpChatConnection(QString,profile)),x_chat_manager,SLOT(on_SetupChatConnection(QString,profile)));
    connect(this,SIGNAL(setUpGroupChatConnection(QString,profile)),x_chat_manager,SLOT(on_SetupGroupChatConnection(QString,profile)));

}

void Task_manager::x_createGroup(const QJsonObject &details, QLabel *status, QListWidget *members,const std::set<QString>& set_members)
{
    QSqlQuery query(this->x_db);
    QString ids=QString::number(profile_details.id);
    //qDebug()<<members->count();
    //qDebug()<<members->takeItem(1)->text();
    for(auto it=set_members.begin();it!=set_members.end();it++){
        //qDebug()<<members->takeItem(i)->text();
        //qDebug()<<(*it);
        query.exec("SELECT id FROM public.users WHERE username='"+(*it)+"';");
        if(query.next()){
            ids+=','+query.value(0).toString();
        }
        else{
            qDebug()<<"Error here";
            qDebug()<<query.lastError().text();
        }
    }
    //qDebug()<<ids;
    query.prepare("INSERT INTO public.groups (group_name,description,participants) VALUES (?,?,?);");
    query.bindValue(0,details["group_name"].toString());
    query.bindValue(1,details["desc"].toString());
    query.bindValue(2,ids);
    if(query.exec()){
        status->setStyleSheet("QLabel{color: green}");
        status->setText(QString::fromStdString("successfully created"));
        emit cleanUpGroupsPage();
    }
    else{
            qDebug()<<query.lastError().text();
    }

}


