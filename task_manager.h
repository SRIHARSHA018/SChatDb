#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <QObject>
#include <QString>
#include <string>
#include <QSqlDatabase>
#include <QJsonObject>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QListWidget>
#include <chatmanager.h>
#include <profile.h>
#include <set>
#include <QLabel>

class Task_manager : public QObject
{
    Q_OBJECT
public:
    explicit Task_manager(QObject *parent = nullptr);
    void Init();
    void ValidateLoginDetails(const QJsonObject& details);
    void ValidateSignUpDetails(const QJsonObject& details,QLabel* status);
    void ValidateGroupInfo(const QJsonObject& details,QLabel* status,QListWidget* members,const std::set<QString>& set_members);
    void SetupMainPage(QStackedWidget* pager);
    void SetupLoginPage(QStackedWidget* pager);
    void SetupContacts(QListWidget* contact_list);
    void SetupGroups(QListWidget* groups);
    STATUS GetState();
    void SetState(STATUS status);
    bool IsLoginSuccessful();
    bool IsSignUpSuccessful();
    void setUpEditProfileWindow(QStackedWidget* pager);
    void setProfileDetails(const QJsonObject& details);
    void displayDetails(QListWidget* preview);
    profile profile_details;
    QListWidget* chat_pane;

signals:
    void enteredMainWindow();
    void setUpChatConnection(QString name,profile profile_details);
    void setUpGroupChatConnection(QString name,profile profile_details);
    void cleanUpGroupsPage();
    void cleanUpLoginPage();
public slots:
    void on_ContactSelected(QListWidgetItem* contact,QLabel* name,STATUS mode);
    void on_SendMessage(QLineEdit* msg);
private:
    QSqlDatabase x_db;
    void x_LoginSuccessful();
    void x_LoginFailed();
    void x_SetupMainWindowControls();
    void x_createGroup(const QJsonObject& details,QLabel* status,QListWidget* members,const std::set<QString>& set_members);
    ChatManager* x_chat_manager;
    STATUS x_state;

};

#endif // TASK_MANAGER_H
