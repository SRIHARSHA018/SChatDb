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

/**
 * Chat manager is responsible for managing chat info and setup connections to contact selected.
 * @brief The ChatManager class
 */
class ChatManager : public QObject
{
    Q_OBJECT
public:
    explicit ChatManager(QObject *parent = nullptr);
    ///send message using extracted text from ui element in task manager.
    void SendChat(std::string msg);
    ///send message using extracted text from ui element in task manager(Group).
    void SendGroupChat(std::string msg);
    ///Display chat history in the ui chat element from main window class.
    void DisplayChat();
    ///Display chat history in the ui chat element from main window class(Group chat).
    void DisplayGroupChat();
    ///For making essential queries.
    QSqlQuery query;
    ///Stores the ui element from main window class.
    QListWidget* chat_pane;
signals:
public slots:
    ///Setup chat connection to contact selected.
    void on_SetupChatConnection(QString name,profile details);
    ///Setup chat connection to group selected(group).
    void on_SetupGroupChatConnection(QString name,profile details);
private:
    ///Internal stores the sender id.
    int x_sender_id;
    ///Internal reciever id when contact selected.
    profile x_profile_details_reciever;
    ///Fetch the contact details from Server database.
    void x_fetchRecieverDetails();
    ///Fetch the group contact details from Server database.
    void x_fetchGroupRecieverDetails();
};

#endif // CHATMANAGER_H
