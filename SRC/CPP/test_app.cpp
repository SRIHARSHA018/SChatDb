#include "test_app.h"
#include <QJsonObject>
#include <QLabel>
#include <task_manager.h>


test_app::test_app(QObject *parent)
    : QObject{parent}
{

}


/**
 * Intializes before test cases run.Setup database details.
 * @brief test_app::initTestCase
 */
void test_app::initTestCase()
{
    t_db = QSqlDatabase::addDatabase("QPSQL");
    t_db.setHostName("localhost");
    t_db.setUserName("postgres");
    t_db.setPassword("root");
    t_db.setDatabaseName("Schat");

}

void test_app::init()
{

}
/**
 * Database Connection test.
 * @brief test_app::DatabaseConnection_test
 */
void test_app::DatabaseConnection_test()
{
    QCOMPARE(t_db.open(),true);
}
/**
 * Signup test using Task manager of the app.
 * @brief test_app::SignUp_test
 */
void test_app::SignUp_test()
{
    QJsonObject details;
    details["username"]=QString("test_dummy");
    details["password"]=QString("password");
    details["firstname"]=QString("dummy_first");
    details["lastname"]=QString("dummy_last");
    details["confirmpassword"]=QString("password");
    details["contactno"] = QString("0000000000");
    Task_manager t_tasker;
    t_tasker.Init();
    t_tasker.ValidateSignUpDetails(details,new QLabel());
    QCOMPARE(t_tasker.IsSignUpSuccessful(),true);
}
/**
 * Uses Dummy varibles to login into app and uses Task Manager.
 * @brief test_app::Login_test
 */
void test_app::Login_test()
{
    QJsonObject details;
    details["username"]=QString("test_dummy");
    details["password"]=QString("password");
    Task_manager t_tasker;
    t_tasker.Init();
    t_tasker.ValidateLoginDetails(details);
    QCOMPARE(t_tasker.IsLoginSuccessful(),true);
}

void test_app::cleanup()
{

}
/**
 * Cleanup Database setup and task manager.
 * @brief test_app::cleanupTestCase
 */
void test_app::cleanupTestCase()
{
    QSqlQuery query(this->t_db);
    query.prepare("DELETE FROM public.users WHERE username=?;");
    query.bindValue(0,QString::fromStdString("test_dummy"));
    QCOMPARE(query.exec(),true);
}
