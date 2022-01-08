#include "task_manager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QImage>
#include <QBuffer>
#include <QtGlobal>
#include <QPixmap>
#include <iostream>
/**
 * Setup intial connections and signals to login and main window entry.
 * @brief Task_manager::Task_manager
 * @param parent
 */
Task_manager::Task_manager(QObject *parent)
    : QObject{parent}
{
        connect(this,SIGNAL(enteredMainWindow()),parent,SLOT(on_EnterMainWindow()));
        connect(this,SIGNAL(cleanUpLoginPage()),parent,SLOT(on_cleanUpLoginPage()));
}
/**
 * Database connections and intialization is done.
 * @brief Task_manager::Init
 */
void Task_manager::Init()
{
    x_db = QSqlDatabase::addDatabase("QPSQL");
    ///setup deatails for database.
    x_db.setHostName("192.168.0.151");
    x_db.setUserName("postgres");
    x_db.setPassword("Sj@&15634");
    x_db.setDatabaseName("Schat");
    x_db.setPort(5432);
    try{
        if(x_db.open()){
            qDebug()<<"DatabaseConnected";
        }
        else{
            //qDebug()<<"failed";
            throw "Database Connection failed";
        }
    }
    catch(...){
        std::cout<<"Database connection failure, Please check the connection";
    }

}
/**
 * Validation for login with database queries.
 * @brief Task_manager::ValidateLoginDetails
 * @param details
 */
void Task_manager::ValidateLoginDetails(const QJsonObject &details)
{
    QSqlQuery query(x_db);
    auto username = details["username"].toString();
    auto password = details["password"].toString();
    query.exec( QString("SELECT username,password FROM public.users WHERE username='"+username+"' AND password='"+password+"';"));
    if(query.next()){
        //qDebug()<<"User details are correct";
        this->SetState(STATUS::LOGIN_SUCCESSFUL);
        query.exec("SELECT id,username,firstname,lastname,contactno,profile_pic FROM public.users WHERE username='"+username+"';");
        if(query.next()){
            ///local details setup.
            profile_details.id = query.value(0).toInt();
            profile_details.user_name = query.value(1).toString().toStdString();
            profile_details.first_name = query.value(2).toString().toStdString();
            profile_details.last_name = query.value(3).toString().toStdString();
            profile_details.contactno = query.value(4).toString().toStdString();
            if(!query.value(5).isNull()){
                //qDebug()<<"feteched image";
                QPixmap image;
                if(image.loadFromData(query.value(5).toByteArray())){
                    profile_details.profile_pic = image;
                }
                //qDebug()<<QString::fromStdString(profile_details.profile_pic);
            }
        }
        /*else{
            qDebug()<<query.lastError().text();
        }*/
    }
    else{
        //qDebug()<<query.lastError();
        this->SetState(STATUS::LOGIN_FAILED);
    }
}
/**
 * Takes ui component from main window class and  validates signup.
 * @brief Task_manager::ValidateSignUpDetails
 * @param details
 * @param status
 */
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
        /*else{
            qDebug()<<query.lastError().text().toStdString();
        }*/
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
/**
 * Validate Group info details.
 * @brief Task_manager::ValidateGroupInfo
 * @param details
 * @param status
 * @param members
 * @param set_members
 */
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
/**
 * If the state is login successful then setuops main page.
 * @brief Task_manager::SetupMainPage
 * @param pager
 */
void Task_manager::SetupMainPage(QStackedWidget *pager)
{
    if(this->GetState()==STATUS::LOGIN_SUCCESSFUL){
        pager->setCurrentIndex(2);
        emit cleanUpLoginPage();
        emit enteredMainWindow();
        x_SetupMainWindowControls();
        if(this->x_db.driver()->hasFeature(QSqlDriver::EventNotifications)){
            this->x_db.driver()->subscribeToNotification("msg");
            //qDebug()<<"got the feature";
            //qDebug()<<this->x_db.driver()->subscribedToNotifications();
            connect(this->x_db.driver(), SIGNAL(notification(const QString&, QSqlDriver::NotificationSource , const QVariant &)),
                    this, SLOT(notificationReceived(const QString&, QSqlDriver::NotificationSource, const QVariant &)));

        }
        else{
            //qDebug()<<"No Event feature";
        }

    }
}
/**
 * Setups login page using ui element from main window class.
 * @brief Task_manager::SetupLoginPage
 * @param pager
 */
void Task_manager::SetupLoginPage(QStackedWidget *pager)
{
    if(this->GetState()==STATUS::SIGNUP_SUCCESSFUL){
        pager->setCurrentIndex(0);
    }

}
/**
 * Setup contacts list and display using ui element from main window class.
 * @brief Task_manager::SetupContacts
 * @param contact_list
 */
void Task_manager::SetupContacts(QListWidget *contact_list)
{
    QSqlQuery query(this->x_db);
    query.exec("SELECT firstname FROM public.users WHERE username!='"+QString::fromStdString(profile_details.user_name)+"';");
    while(query.next()){
     // qDebug()<<query.value(0);
      contact_list->addItem(query.value(0).toString());
    }

}
/**
 * Setup groups list of user subscribed and setup.
 * @brief Task_manager::SetupGroups
 * @param groups
 */
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
   /* else{
        qDebug()<<query.lastError().text();
    }*/

}
/**
 * Return state variable for task manager.
 * @brief Task_manager::GetState
 * @return
 */
STATUS Task_manager::GetState()
{
    return this->x_state;
}
/**
 * Set state variable for task manager.
 * @brief Task_manager::SetState
 * @param status
 */
void Task_manager::SetState(STATUS status)
{
    this->x_state = status;
}
/**
 * check weather login is successful.
 * @brief Task_manager::IsLoginSuccessful
 * @return
 */
bool Task_manager::IsLoginSuccessful()
{
    return (this->GetState()==STATUS::LOGIN_SUCCESSFUL);
}

/**
 * Check weather signup successful.
 * @brief Task_manager::IsSignUpSuccessful
 * @return
 */
bool Task_manager::IsSignUpSuccessful()
{
    return (this->GetState()==STATUS::SIGNUP_SUCCESSFUL);
}
/**
 * Setup Edit window for profile details using ui element from main window class.
 * @brief Task_manager::setUpEditProfileWindow
 * @param pager
 */
void Task_manager::setUpEditProfileWindow(QStackedWidget *pager)
{
    pager->setCurrentIndex(3);
}

/**
 * Upadate profile details. So it will modify details in server end.
 * @brief Task_manager::setProfileDetails
 * @param details
 */
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
/**
 * Display profile details using ui elements from main window class.
 * @brief Task_manager::displayDetails
 * @param preview
 * @param profile_pic
 */
void Task_manager::displayDetails(QListWidget *preview, QLabel* profile_pic)
{
    preview->clear();
    preview->addItem(QString::fromStdString("Username: "+this->profile_details.user_name));
    preview->addItem(QString::fromStdString("Firstname: "+this->profile_details.first_name));
    preview->addItem(QString::fromStdString("Lastname: "+this->profile_details.last_name));
    preview->addItem(QString::fromStdString("Phone Number: "+this->profile_details.contactno));
    profile_pic->setPixmap(this->profile_details.profile_pic);
}
/**
 * Setup profile picture using filename in local device and uploads to server ends.
 * @brief Task_manager::setProfilePic
 * @param filename
 */
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
       // qDebug()<<"insertion of image successful";
        if(this->profile_details.profile_pic.loadFromData(image_bytes)){
        //    qDebug()<<"profile pic updated successfully";
        }
        //else{
        //    qDebug()<<"Failed to update";
       // }
    }
    /*else{
        qDebug()<<query.lastError().text();
    }*/

}
/**
 * Cleaup profile struct.
 * @brief Task_manager::cleanUp
 */
void Task_manager::cleanUp()
{
    this->profile_details.profile_pic = QPixmap(DEFAULT_PROFILE_PIC);
}
/**
 * Setup connection essentials to the contact selected using ui elements from main window class.
 * @brief Task_manager::on_ContactSelected
 * @param contact
 * @param name
 * @param mode
 */
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
/**
 * Notifies whenever a message is recieved into server end. This will notify clients as a signal.
 * @brief Task_manager::notificationReceived
 * @param name
 * @param source
 * @param payload
 */
void Task_manager::notificationReceived(const QString &name,  QSqlDriver::NotificationSource source, const QVariant &payload)
{
    //qDebug()<<name<<" "<<source<<" "<<payload;
    switch(this->GetState())
    {
    case STATUS::REGULAR_CHAT:
        if(name=="msg"){
           // qDebug()<<"got notify";
            this->x_chat_manager->DisplayChat();
           // qDebug()<<"updated chat";
        }
        break;
    case STATUS::GROUP_CHAT:
        if(name=="msg"){
            this->x_chat_manager->DisplayGroupChat();
        }
        break;
    default:
        break;
    }
}
/**
 * Sends message to the contact selected.
 * @brief Task_manager::SendMessage
 * @param msg
 */
void Task_manager::SendMessage(QLineEdit *msg)
{
    switch(this->GetState())
    {
    case STATUS::REGULAR_CHAT:
        //QSqlQuery query(x_db);
       // qDebug()<<"Regular Chat";
        x_chat_manager->SendChat(msg->text().toStdString());
        //qDebug()<<"reached taskmanager send btn";
        msg->clear();
        break;
    case STATUS::GROUP_CHAT:
        //qDebug()<<"Group Chat";
        x_chat_manager->SendGroupChat(msg->text().toStdString());
        msg->clear();
        break;
    default:
        break;
    }

}
/**
 * Setup main windows ui controls and chat manager setups.
 * @brief Task_manager::x_SetupMainWindowControls
 */
void Task_manager::x_SetupMainWindowControls()
{

    this->x_chat_manager = new ChatManager(this);
    this->x_chat_manager->query = QSqlQuery(this->x_db);
    try{
        this->x_chat_manager->chat_pane = this->chat_pane;
    }catch(const std::exception& e){
        std::cout<<e.what();
    }

    connect(this,SIGNAL(setUpChatConnection(QString,profile)),x_chat_manager,SLOT(on_SetupChatConnection(QString,profile)));
    connect(this,SIGNAL(setUpGroupChatConnection(QString,profile)),x_chat_manager,SLOT(on_SetupGroupChatConnection(QString,profile)));

}
/**
 * Create a group this is a internal function which is called by this class.
 * @brief Task_manager::x_createGroup
 * @param details
 * @param status
 * @param members
 * @param set_members
 */
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
        /*else{
            qDebug()<<"Error here";
            qDebug()<<query.lastError().text();
        }*/
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
    /*else{
            qDebug()<<query.lastError().text();
    }*/

}


