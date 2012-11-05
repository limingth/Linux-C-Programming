#ifndef CHAT_H
#define CHAT_H
#include <QTcpSocket>
#include <QDialog>
#include <QStringListModel>
#include <QHash>
#include "ui_chat.h"
#include "privchat.h"

class Chat : public QDialog, public Ui_Chat
{
    Q_OBJECT

public:
     Chat(QString myname, QTcpSocket *s, QWidget *parent = 0);

private slots:
    void sendMsg();
    void recvMsg();
    void error();
    void updateWhom(const QModelIndex &);
    void openPriv(const QModelIndex &);

private:
    void handleMsg(QString);
    void appendMsg(QString);
    QTcpSocket *tcpSocket;
    QStringListModel *model;
    QStringList userList;
    QString msgBuffer;
    QString myname;
    QHash<QString, PrivChat *> privs;
};

#endif
