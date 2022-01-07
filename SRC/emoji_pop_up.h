#ifndef EMOJI_POP_UP_H
#define EMOJI_POP_UP_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>

namespace Ui {
class emoji_pop_up;
}

class emoji_pop_up : public QDialog
{
    Q_OBJECT

signals:
    void emojiSelected(QString emoji);
public:
    explicit emoji_pop_up(QWidget *parent = nullptr);
    ~emoji_pop_up();

private slots:
    void on_tableWidget_itemClicked(QTableWidgetItem *item);

private:
    Ui::emoji_pop_up *ui;
};

#endif // EMOJI_POP_UP_H
