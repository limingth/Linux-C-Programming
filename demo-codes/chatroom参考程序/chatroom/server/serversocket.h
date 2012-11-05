#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include <QTcpServer>

class ServerSocket : public QTcpServer
{
  Q_OBJECT
public:
     ServerSocket(QObject *parent = 0);
private:
     void incomingConnection(int socketId);
};
#endif
