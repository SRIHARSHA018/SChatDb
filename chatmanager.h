#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QObject>
#include <string>
#include <QSqlDatabase>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include <vector>
#include <algorithm>
#include <profile.h>


class ChatManager : public QObject
{
    Q_OBJECT
public:
    explicit ChatManager(QObject *parent = nullptr);
    void SendChat(std::string msg);
    void SendGroupChat(std::string msg);
    void DisplayChat();
    void DisplayGroupChat();
    QSqlQuery* query;
    QListWidget* chat_pane;
signals:
public slots:
    void on_SetupChatConnection(QString name,profile details);
    void on_SetupGroupChatConnection(QString name,profile details);
private:
    int x_sender_id;
    profile x_profile_details_reciever;
    void x_fetchRecieverDetails();
    void x_fetchGroupRecieverDetails();
};

#endif // CHATMANAGER_H
