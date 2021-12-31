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
    ui->centralwidget=ui->stackedWidget;
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_EnterMainWindow()
{
    connect(this,SIGNAL(contactSelected(QListWidgetItem*,QLabel*,STATUS)),tasker,SLOT(on_ContactSelected(QListWidgetItem*,QLabel*,STATUS)));
    connect(this,SIGNAL(sendMessage(QLineEdit*)),tasker,SLOT(on_SendMessage(QLineEdit*)));
    ui->username_label_chat->setText(QString(" hiiii \xF0\x9F\x98\x81"));
    tasker->chat_pane = ui->chat_pane;
}

void MainWindow::on_cleanUpGroupsPage()
{
    ui->group_name_box->clear();
    ui->group_desc_box->clear();
    ui->group_members->clear();
    this->x_group_members.clear();
    tasker->SetupGroups(ui->groups_list);
}

void MainWindow::on_cleanUpLoginPage()
{
    ui->username_box->clear();
    ui->password_box->clear();
}

void MainWindow::on_emojiSelected(QString emoji)
{
    ui->message_box_chat->setText(ui->message_box_chat->text()+emoji);
}


void MainWindow::on_login_btn_clicked()
{

    QJsonObject details;
    details["username"]=ui->username_box->text();
    details["password"]=ui->password_box->text();
    tasker->ValidateLoginDetails(details);
    if(tasker->IsLoginSuccessful()){
       tasker->SetupMainPage(ui->stackedWidget);
       tasker->SetupContacts(ui->contacts_list);
       tasker->SetupGroups(ui->groups_list);
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


void MainWindow::on_send_btn_chat_clicked()
{
    //qDebug()<<"send clicked";
    emit sendMessage(ui->message_box_chat);
}


void MainWindow::on_contacts_list_itemClicked(QListWidgetItem *item)
{

    emit contactSelected(item,ui->username_label_chat,STATUS::REGULAR_CHAT);
   // qDebug()<<"Contact selected main window";
}


void MainWindow::on_groups_list_itemClicked(QListWidgetItem *item)
{
    emit contactSelected(item,ui->username_label_chat,STATUS::GROUP_CHAT);
}


void MainWindow::on_createGroup_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    tasker->SetupContacts(ui->contactListtoAddtoGroup);
}

void MainWindow::on_editProfile_btn_clicked()
{
    tasker->setUpEditProfileWindow(ui->stackedWidget);
    tasker->displayDetails(ui->PreviewDetails_list);
}


void MainWindow::on_save_details_profile_clicked()
{

    QJsonObject changed_profile_details;
    if(ui->profileEdit_username_box->text().length()!=0){
        changed_profile_details["username"] = ui->profileEdit_username_box->text();
    }
    if(ui->profileEdit_firstname_box->text().length()!=0){
        changed_profile_details["firstname"] = ui->profileEdit_firstname_box->text();

    }
    if(ui->profileEdit_lastname_box->text().length()!=0){
        changed_profile_details["lastname"] = ui->profileEdit_lastname_box->text();

    }
    if(ui->profileEdit_contactno_box->text().length()!=0){
        changed_profile_details["contactno"] = ui->profileEdit_contactno_box->text();

    }
    if(ui->profileEdit_password_box->text().length()!=0 && ui->profileEdit_confirmpass_box->text().length()!=0){
        if(ui->profileEdit_confirmpass_box->text()==ui->profileEdit_password_box->text()){
            changed_profile_details["password"] = ui->profileEdit_password_box->text();
        }
        else{
            ui->status_profileEdit->setStyleSheet("QLabel{color: red}");
            ui->status_profileEdit->setText(QString::fromStdString("confirm password and password should be same."));
        }
    }
    tasker->setProfileDetails(changed_profile_details);
    tasker->displayDetails(ui->PreviewDetails_list);
}


void MainWindow::on_Home_btn_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_Home_btn_2_clicked()
{
  ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_contactListtoAddtoGroup_itemClicked(QListWidgetItem *item)
{
//    qDebug()<<"contact clicked"<<item->text();
    if(ui->group_members->findItems(item->text(),Qt::MatchExactly).length()==0){
        ui->group_members->addItem(item->text());
        this->x_group_members.insert(item->text());
    }
}


void MainWindow::on_removeGroupMember_clicked()
{
    if(ui->group_members->selectedItems().length()>0){
        //qDebug()<<ui->group_members->selectedItems()[0]->text();
        ui->group_members->removeItemWidget(ui->group_members->selectedItems()[0]);
        this->x_group_members.erase(this->x_group_members.find(ui->group_members->selectedItems()[0]->text()));
        delete ui->group_members->selectedItems()[0];
    }
}



void MainWindow::on_create_group_btn_clicked()
{
    QJsonObject details;
    details["group_name"]=ui->group_name_box->text();
    details["desc"] = ui->group_desc_box->toPlainText();
    connect(tasker,SIGNAL(cleanUpGroupsPage()),this,SLOT(on_cleanUpGroupsPage()));
    tasker->ValidateGroupInfo(details,ui->status_group_create,ui->group_members,this->x_group_members);

}


void MainWindow::on_signout_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    this->x_cleanUpEverything();
}


void MainWindow::on_submit_btn_signup_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::x_cleanUpEverything()
{
    ui->contacts_list->clear();
    ui->groups_list->clear();
    ui->chat_pane->clear();
}

void MainWindow::on_emoji_btn_clicked()
{
    this->emojisWin =new emoji_pop_up(this);
    emojisWin->show();
}

