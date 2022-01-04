#include "mainwindow.h"

#include <QApplication>
#include <QTest>
#include <Testing/test_app.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test_app Tester;
    QTest::qExec(&Tester);

    MainWindow w;
    w.show();
    return a.exec();
}
