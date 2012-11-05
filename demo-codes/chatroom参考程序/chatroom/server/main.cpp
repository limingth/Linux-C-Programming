#include <QApplication>
#include <QTcpServer>
#include <QTextCodec>
#include <QMessageBox>
#include "serversocket.h"
#include "clientsocket.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  ServerSocket s;

  ClientSocket::loadPasswd();
  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  if (!s.listen(QHostAddress::Any, 4869)) {
    qDebug() << "cannot bind address";
    exit(1);
  }
  return app.exec();
}
