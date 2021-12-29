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
#include <QLabel>


enum STATUS{
    LOGIN_SUCCESSFUL,
    LOGIN_FAILED,

    SIGNUP_SUCCESSFUL,
    SIGNUP_FAILED,
};


class Task_manager : public QObject
{
    Q_OBJECT
public:
    explicit Task_manager(QObject *parent = nullptr);
    void Init();
    void ValidateLoginDetails(const QJsonObject& details);
    void ValidateSignUpDetails(const QJsonObject& details,QLabel* status);
    void SetupMainPage(QStackedWidget* pager);
    void SetupLoginPage(QStackedWidget* pager);
    void SetupContacts(QListWidget* contact_list);
    STATUS GetState();
    void SetState(STATUS status);
    bool IsLoginSuccessful();
    bool IsSignUpSuccessful();
    profile profile_details;
    QListWidget* chat_pane;

signals:
    void enteredMainWindow();
    void setUpChatConnection(QString name,profile profile_details);

public slots:
    void on_ContactSelected(QListWidgetItem* contact,QLabel* name);
    void on_SendMessage(QLineEdit* msg);
private:
    QSqlDatabase x_db;
    void x_LoginSuccessful();
    void x_LoginFailed();
    void x_SetupMainWindowControls();
    ChatManager* x_chat_manager;
    STATUS x_state;

};

#endif // TASK_MANAGER_H
