#include <QMessageBox>
#include "privchat.h"

PrivChat::PrivChat(QString myname, QString yourname, QTcpSocket *s, QWidget *parent)
  : QDialog(parent), yourname(yourname), tcpSocket(s)
{
  setupUi(this);
  setWindowTitle(myname + tr("和") + yourname + windowTitle());
  connect(pushButton, SIGNAL(clicked()), this, SLOT(sendMsg()));
}

void PrivChat::sendMsg()
{
  if (lineEdit->text().isEmpty()) {
    QMessageBox::critical(this, tr("输入错误"), tr("发送消息不能为空"));
    return;
  }
  QRegExp r("[^|\\n]+");
  if (!r.exactMatch(lineEdit->text())) {
    QMessageBox::critical(this, tr("输入错误"), tr("发送消息中包含非法字符"));
    return;
  }
  QTextStream out(tcpSocket);
  out << "PRIV|" << yourname << "|" << lineEdit->text() << endl;
  out.flush();
  msgBuffer += tr("<font color='blue'>我</font>对<font color='blue'>")
    + yourname + tr("</font>说：") + lineEdit->text()+"<br />";
  textBrowser->setText(msgBuffer);
  textBrowser->moveCursor(QTextCursor::End);
  lineEdit->clear();
}
