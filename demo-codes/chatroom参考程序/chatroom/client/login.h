#ifndef LOGIN_H
#define LOGIN_H
#include <QTcpSocket>
#include <QDialog>

#include "ui_login.h"

class Login : public QDialog, public Ui_Login
{
    Q_OBJECT

public:
     Login(QString *myname, QTcpSocket *s, QWidget *parent = 0);

private slots:
     void sendMsg();
     void switchVisible(bool);
     
private:
     QTcpSocket *tcpSocket;
     QString *myname;
};

#endif
