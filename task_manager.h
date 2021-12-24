#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <QObject>
#include <QSqlDatabase>


class Task_manager : public QObject
{
    Q_OBJECT
public:
    explicit Task_manager(QObject *parent = nullptr);

signals:

private:
    QSqlDatabase db;
};

#endif // TASK_MANAGER_H
