#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include <QHash>

class ClientSocket : public QTcpSocket
{
     Q_OBJECT

public:
     ClientSocket(QObject *parent = 0);
     static void loadPasswd();

private slots:
     void readClient();
     void disconnect();

private:
     void handleMsg(QString);
     void loginClient(QString name);
     QString name;
     static QHash<QString, ClientSocket *> clients;
     static QHash<QString, QByteArray> passwds;
};

#endif
