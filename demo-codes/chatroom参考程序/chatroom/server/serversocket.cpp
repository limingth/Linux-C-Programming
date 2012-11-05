#include "serversocket.h"
#include "clientsocket.h"

ServerSocket::ServerSocket(QObject *parent)
    : QTcpServer(parent)
{
}

void ServerSocket::incomingConnection(int socketId)
{
  ClientSocket *socket = new ClientSocket(this);
  socket->setSocketDescriptor(socketId);
}
