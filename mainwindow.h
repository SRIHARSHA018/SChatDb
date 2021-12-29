#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <task_manager.h>
#include <QJsonObject>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void contactSelected(QListWidgetItem* contact,QLabel* name);
    void sendMessage(QLineEdit* msg);
public slots:
    void on_EnterMainWindow();

private slots:
    void on_login_btn_clicked();

    void on_signup_btn_clicked();

    void on_submit_btn_signup_clicked();

    void on_send_btn_chat_clicked();

    void on_contacts_list_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Task_manager* tasker;

};
#endif // MAINWINDOW_H
