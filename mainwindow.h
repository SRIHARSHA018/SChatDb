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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void contactSelected(QListWidgetItem* contact,QLabel* name,STATUS mode);
    void sendMessage(QLineEdit* msg);
public slots:
    void on_EnterMainWindow();
    void on_cleanUpGroupsPage();
    void on_cleanUpLoginPage();
    void on_emojiSelected(QString emoji);

private slots:
    void on_login_btn_clicked();

    void on_signup_btn_clicked();

    void on_submit_btn_signup_clicked();

    void on_send_btn_chat_clicked();

    void on_contacts_list_itemClicked(QListWidgetItem *item);

    void on_groups_list_itemClicked(QListWidgetItem *item);

    void on_createGroup_btn_clicked();

    void on_editProfile_btn_clicked();

    void on_save_details_profile_clicked();

    void on_Home_btn_clicked();

    void on_Home_btn_2_clicked();

    void on_contactListtoAddtoGroup_itemClicked(QListWidgetItem *item);

    void on_removeGroupMember_clicked();

    void on_create_group_btn_clicked();

    void on_signout_btn_clicked();

    void on_submit_btn_signup_2_clicked();

    void on_emoji_btn_clicked();

private:
    Ui::MainWindow *ui;
    Task_manager* tasker;
    std::set<QString> x_group_members;
    void x_cleanUpEverything();
    emoji_pop_up* emojisWin;
};
#endif // MAINWINDOW_H
