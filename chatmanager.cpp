#include "chatmanager.h"
#include <QDebug>
#include <QLabel>

ChatManager::ChatManager(QObject *parent)
    : QObject{parent}
{

}

void ChatManager::SendChat(std::string msg)
{
   this->x_fetchRecieverDetails();
   query.prepare("INSERT INTO public.messages (message,sender_id,reciever_id) VALUES (?,?,?);");
   query.bindValue(0,QString::fromStdString(msg));
   //qDebug()<<this->x_sender_id;
   query.bindValue(1,this->x_sender_id);
   query.bindValue(2,this->x_profile_details_reciever.id);
   if(query.exec()){
     qDebug()<<"message inserted";
     this->DisplayChat();
   }
   else{
       qDebug()<<query.lastError();
   }
}

void ChatManager::SendGroupChat(std::string msg)
{
    query.prepare("INSERT INTO public.group_messages (message,sender_id,group_id) VALUES (?,?,?);");
    query.bindValue(0,QString::fromStdString(msg));
    //qDebug()<<this->x_sender_id;
    query.bindValue(1,this->x_sender_id);
    query.bindValue(2,this->x_profile_details_reciever.id);
    if(query.exec()){
      qDebug()<<"message inserted";
      this->DisplayGroupChat();
    }
    else{
        qDebug()<<query.lastError();
    }
}

void ChatManager::DisplayChat()
{
    chat_pane->clear();
    query.prepare("SELECT message,sender_id,reciever_id FROM public.messages WHERE (sender_id=? AND reciever_id=?) OR (sender_id=? AND reciever_id=?) ORDER BY id ASC;");
    query.bindValue(0,this->x_sender_id);
    query.bindValue(1,this->x_profile_details_reciever.id);
    query.bindValue(2,this->x_profile_details_reciever.id);
    query.bindValue(3,this->x_sender_id);
    if(query.exec()){
        //qDebug()<<"got messages";
        while(query.next()){
            QListWidgetItem* item =new QListWidgetItem(query.value(0).toString(),chat_pane);
          //qDebug()<<query.value(0).toString()<<" "<<query.value(1).toString()<<" "<<query.value(2).toString();
            if(query.value(1).toInt()==this->x_sender_id){
                item->setTextAlignment(Qt::AlignRight);
                chat_pane->addItem(item);
            }
            else{
                item->setTextAlignment(Qt::AlignLeft);
                chat_pane->addItem(item);
            }
        }
    }
    else{
        qDebug()<<query.lastError();
    }
    //qDebug()<<chat_pane->currentRow();
    chat_pane->scrollToBottom();

}
void ChatManager::DisplayGroupChat()
{
    chat_pane->clear();

    query.prepare("SELECT public.group_messages.message,sender_id,firstname FROM public.group_messages INNER JOIN public.users ON public.users.id = sender_id AND group_id=? ORDER BY public.group_messages.id ASC;");
    query.bindValue(0,this->x_profile_details_reciever.id);
    if(query.exec()){
        //qDebug()<<"got messages";
        while(query.next()){
            QListWidgetItem* item =new QListWidgetItem(chat_pane);
          //qDebug()<<query.value(0).toString()<<" "<<query.value(1).toString()<<" "<<query.value(2).toString();
            if(query.value(1).toInt()==this->x_sender_id){
                item->setText(query.value(0).toString());
                item->setTextAlignment(Qt::AlignRight);
                chat_pane->addItem(item);
            }
            else{
                item->setText("@"+query.value(2).toString()+":-\n  "+query.value(0).toString());
                item->setTextAlignment(Qt::AlignLeft);
                chat_pane->addItem(item);
            }
        }
    }
    else{
        qDebug()<<query.lastError();
    }

    chat_pane->scrollToBottom();

}

void ChatManager::on_SetupChatConnection(QString name,profile details)
{
    this->x_sender_id = details.id;
    //qDebug()<<this->x_profile_details->id;
    this->x_profile_details_reciever.first_name=name.toStdString();
    this->x_fetchRecieverDetails();
    this->DisplayChat();
    //qDebug()<<"contact setup done";
}

void ChatManager::on_SetupGroupChatConnection(QString name, profile details)
{
    this->x_sender_id = details.id;
    //qDebug()<<"Chat connection established"<<name;
    this->x_profile_details_reciever.first_name = name.toStdString();
    this->x_fetchGroupRecieverDetails();
    this->DisplayGroupChat();
}

void ChatManager::x_fetchRecieverDetails()
{

        query.exec("SELECT id FROM public.users WHERE firstname='"+QString::fromStdString(this->x_profile_details_reciever.first_name)+"';");
        if(query.next()){
            this->x_profile_details_reciever.id=query.value(0).toInt();
        }
        else{
            qDebug()<<query.lastError();
        }
}

void ChatManager::x_fetchGroupRecieverDetails()
{
    query.exec("SELECT id FROM public.groups WHERE group_name='"+QString::fromStdString(this->x_profile_details_reciever.first_name)+"';");
    if(query.next()){
        this->x_profile_details_reciever.id=query.value(0).toInt();
    }
    else{
        qDebug()<<query.lastError();
    }
}
