#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <QObject>
#include <QString>
#include <QSqlDriver>
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

/**
 * The backend validations are done by this class and updates the ui elements of main window.
 * @brief The Task_manager class
 */
class Task_manager : public QObject
{
    Q_OBJECT
public:
    explicit Task_manager(QObject *parent = nullptr);
    ///Setups Database connection.
    void Init();
    ///Validates Login Details.
    void ValidateLoginDetails(const QJsonObject& details);
    ///Validate Signup details.
    void ValidateSignUpDetails(const QJsonObject& details,QLabel* status);
    ///Validate Group info details.
    void ValidateGroupInfo(const QJsonObject& details,QLabel* status,QListWidget* members,const std::set<QString>& set_members);
    ///Setup main page and essentials
    void SetupMainPage(QStackedWidget* pager);
    ///SetupLoginPage and essentials.
    void SetupLoginPage(QStackedWidget* pager);
    ///Setup contacts in main page.
    void SetupContacts(QListWidget* contact_list);
    ///Setup groups in main page.
    void SetupGroups(QListWidget* groups);
    ///This will return state of TaskManager.
    STATUS GetState();
    ///This will set the state of  TaskManager.
    void SetState(STATUS status);
    ///Returns true if login details are valid.
    bool IsLoginSuccessful();
    ///Returns true if signup details are valid.
    bool IsSignUpSuccessful();
    ///Shows the users profile editor window and setup essentials.
    void setUpEditProfileWindow(QStackedWidget* pager);
    ///Setup profile details when login.
    void setProfileDetails(const QJsonObject& details);
    ///Display user chat details and reciever details.
    void displayDetails(QListWidget* preview,QLabel* profile_pic);
    ///Helps in getting the filename from the file explorer.
    void setProfilePic(const std::string& filename);
    ///Message from ui element is extracted and invokes send message of chat manager.
    void SendMessage(QLineEdit* msg);
    ///cleaning up ui and other elements.
    void cleanUp();
    ///user profile info for operations.
    profile profile_details;
    ///Chat pane to display chat history and all.
    QListWidget* chat_pane;
    ///Groups pane display
    QListWidget *groups;
    ///Contacts List pane display
    QListWidget *contacts;

signals:
    ///Make MainWindow class to setup essentials.
    void enteredMainWindow();
    ///Setup Chat connection when contact is selected.
    void setUpChatConnection(QString name,profile profile_details);
    ///Setup Group connection when group is selected.
    void setUpGroupChatConnection(QString name,profile profile_details);
    ///Cleanup for groups page ui elements.
    void cleanUpGroupsPage();
    ///Cleanup for Login page ui elements.
    void cleanUpLoginPage();
public slots:
    ///Setups the Chat Manager's settings to the contact selected.
    void on_ContactSelected(QListWidgetItem* contact,QLabel* name,STATUS mode);
    ///Notification upon any member send message.
    void notificationReceived(const QString& name,  QSqlDriver::NotificationSource source, const QVariant &payload);
private:
    ///Database object for database essentials.
    QSqlDatabase x_db;
    ///Internal method for Login Process.
    void x_LoginSuccessful();
    ///Internal method for Login Process.
    void x_LoginFailed();
    ///On entering main page setups will be done.
    void x_SetupMainWindowControls();
    ///Internal method for Group creation process.
    void x_createGroup(const QJsonObject& details,QLabel* status,QListWidget* members,const std::set<QString>& set_members);
    ///Chat manager object.
    ChatManager* x_chat_manager;
    ///State Varible to track state of Task Manager.
    STATUS x_state;


};

#endif // TASK_MANAGER_H
