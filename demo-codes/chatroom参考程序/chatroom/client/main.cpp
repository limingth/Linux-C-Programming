#include <QTextCodec>
#include <QApplication>
#include "login.h"
#include "chat.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QTcpSocket s;
  QString myname;

  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  Login l(&myname, &s);
  if(l.exec() == QDialog::Accepted) {
    Chat c(myname, &s);
    c.show();
    return app.exec();
  }
  return 0;
}
