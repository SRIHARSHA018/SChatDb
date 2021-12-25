#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QJsonObject>
#include <QStackedWidget>
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
    STATUS GetState();
    void SetState(STATUS status);
    bool IsLoginSuccessful();
    bool IsSignUpSuccessful();

signals:

private:
    QSqlDatabase x_db;
    void x_LoginSuccessful();
    void x_LoginFailed();
    STATUS x_state;
};

#endif // TASK_MANAGER_H
