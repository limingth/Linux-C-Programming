#ifndef PRIVCHAT_H
#define PRIVCHAT_H
#include <QTcpSocket>
#include <QDialog>

#include "ui_privchat.h"

class PrivChat : public QDialog, public Ui_PrivChat
{
    Q_OBJECT

public:
     PrivChat(QString myname, QString yourname, QTcpSocket *s, QWidget *parent = 0);
     QString msgBuffer;
    
private slots:
    void sendMsg();

private:
    QString yourname;
    QTcpSocket *tcpSocket;
};

#endif
