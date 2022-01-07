#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <task_manager.h>
#include <QJsonObject>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLabel>
#include <set>
#include <emoji_pop_up.h>
#include <profile.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
///Mainwindow to start every other dependency.
/// The main functionality of this class is to maintain the Ui elements of this application and
///  Provide TaskManager class with the essential elements it requires.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    ///This is  a Signal function which will be invoked when a contact element is selected.
    /// Then the contact details are setup with respect to contact.
    void contactSelected(QListWidgetItem* contact,QLabel* name,STATUS mode);
public slots:
    ///This is a slot method which will be invoked by a signal from TaskManager class after login.
    void on_EnterMainWindow();
    ///This is a slot method which will clean up groups page of app.
    void on_cleanUpGroupsPage();
    ///This is a slot method which will clean up login page of app.
    void on_cleanUpLoginPage();
    ///This is a slot method which will shows the emojis.
    void on_emojiSelected(QString emoji);

private slots:
    ///This is a slot method of login Button Method
    void on_login_btn_clicked();

    ///This is a slot method of signup Button Method
    void on_signup_btn_clicked();

    ///This is a slot method of signup's submit Button Method
    void on_submit_btn_signup_clicked();

    ///This is a slot method of send Button Method
    void on_send_btn_chat_clicked();

    ///This is a slot method of contact selected Method
    void on_contacts_list_itemClicked(QListWidgetItem *item);

    ///This is a slot method of groups selected Method
    void on_groups_list_itemClicked(QListWidgetItem *item);

    ///This is a slot method of create new group Button Method
    void on_createGroup_btn_clicked();

    ///This is a slot method of Edit profile Button Method
    void on_editProfile_btn_clicked();

    ///This is a slot method of Edit profile Save Button Method
    void on_save_details_profile_clicked();

    ///This is a slot method of Home page Button Method
    void on_Home_btn_clicked();

    ///This is a slot method of Home page Button Method
    void on_Home_btn_2_clicked();

    ///This is a slot method of Contacts to select in order to add into group Method
    void on_contactListtoAddtoGroup_itemClicked(QListWidgetItem *item);

    ///This is a slot method of for removing added group member Button Method
    void on_removeGroupMember_clicked();

    ///This is a slot method of Create Group Button Method
    void on_create_group_btn_clicked();

    ///This is a slot method of SignOut Button Method
    void on_signout_btn_clicked();

    ///This is a slot method of Login page Button Method
    void on_submit_btn_signup_2_clicked();

    ///This is a slot method of emoji Dialogue Button Method
    void on_emoji_btn_clicked();

    ///This is a slot method of profile photo upload Button Method
    void on_profile_pic_btn_edit_clicked();

private:
    ///Ui element to manage Ui.
    Ui::MainWindow *ui;
    ///Task Manager Object.
    Task_manager* tasker;
    std::set<QString> x_group_members;
    ///Internal cleanup method.
    void x_cleanUpEverything();
    ///Emoji dialoge object.
    emoji_pop_up* emojisWin;
};
#endif // MAINWINDOW_H
