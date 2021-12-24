#include "task_manager.h"
#include <QDebug>

Task_manager::Task_manager(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("Sj@&15634");
    db.setDatabaseName("postgres");
    db.setPort(8002);
    if(db.open()){
        qDebug()<<"DatabaseConnected";
    }
    else{
        qDebug()<<"failed";
    }
}
