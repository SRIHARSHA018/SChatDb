#ifndef TEST_APP_H
#define TEST_APP_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QTest>
#include <QtTest/QtTest>

/**
 * Testing class for SChat.
 * @brief The test_app class
 */
class test_app : public QObject
{
    Q_OBJECT
public:
    explicit test_app(QObject *parent = nullptr);
signals:

private slots:
    /// called before the first test function
    void initTestCase();
    /// called before every test function
    void init();

    ///Testing Datatbase connection request
    void DatabaseConnection_test();

    ///Testing signup through app
    void SignUp_test();

    ///Testing signup through app
    void Login_test();

    /// called after every test function
    void cleanup();
    /// called after the last test function
    void cleanupTestCase();

private:
    QSqlDatabase t_db;
};

#endif // TEST_APP_H
