#include "emoji_pop_up.h"
#include "ui_emoji_pop_up.h"
/**
 * Setup Ui,signal and slot connection of emoji selection
 * @brief emoji_pop_up::emoji_pop_up
 * @param parent
 */
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
/**
 * on emoji selection emit signals to Main window class.
 * @brief emoji_pop_up::on_tableWidget_itemClicked
 * @param item
 */
void emoji_pop_up::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
    emit emojiSelected(item->text());
}

