#include "emoji_pop_up.h"
#include "ui_emoji_pop_up.h"

emoji_pop_up::emoji_pop_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::emoji_pop_up)
{
    ui->setupUi(this);
    connect(this,SIGNAL(emojiSelected(QString)),parent,SLOT(on_emojiSelected(QString)));
}

emoji_pop_up::~emoji_pop_up()
{
    delete ui;
}

void emoji_pop_up::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    emit emojiSelected(item->text());
}

