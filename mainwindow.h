#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <task_manager.h>
#include <QJsonObject>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_btn_clicked();

    void on_signup_btn_clicked();

    void on_submit_btn_signup_clicked();

private:
    Ui::MainWindow *ui;
    Task_manager* tasker;

};
#endif // MAINWINDOW_H
