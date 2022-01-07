#include "mainwindow.h"

#include <QApplication>
#include <QTest>
#include <test_app.h>

///Entry point,
/// First test cases will run before the main app
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    test_app Tester;
    QTest::qExec(&Tester);


    MainWindow w;
    w.show();
    return a.exec();
}
