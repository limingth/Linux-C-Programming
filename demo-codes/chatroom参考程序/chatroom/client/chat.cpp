#include <QHostAddress>
#include <QMessageBox>
#include "chat.h"
#include "privchat.h"

Chat::Chat(QString myname, QTcpSocket *s, QWidget *parent)
  : QDialog(parent), tcpSocket(s), myname(myname)
{
  setupUi(this);
  setWindowTitle(windowTitle()+" - "+myname);
  model = new QStringListModel(this);
  userList.append(tr("所有人"));
  model->setStringList(userList);
  listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  connect(listView, SIGNAL(doubleClicked(const QModelIndex &)),
	  this, SLOT(openPriv(const QModelIndex &)));
  connect(listView, SIGNAL(clicked(const QModelIndex &)),
	  this, SLOT(updateWhom(const QModelIndex &)));
  listView->setModel(model);
  connect(pushButton, SIGNAL(clicked()), this, SLOT(sendMsg()));
  disconnect(tcpSocket, 0, 0, 0);
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvMsg()));
  connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(error()));

  if (tcpSocket->canReadLine()) {
    QString msg;
    do {
      msg += QString::fromUtf8((tcpSocket->readLine()).data());
    } while (tcpSocket->canReadLine());
    handleMsg(msg);
  }
}

void Chat::sendMsg()
{
  if (lineEdit->text().isEmpty()) {
      QMessageBox::warning(this, tr("输入错误"), tr("发送消息不能为空"));
      return;
  }
  QRegExp r("[^|\\n]+");
  if (!r.exactMatch(lineEdit->text())) {
      QMessageBox::warning(this, tr("输入错误"), tr("发送消息中包含非法字符"));
      return;
  }

  QTextStream out(tcpSocket);
  if (label_whom->text() == tr("所有人"))
    out << "TOALL|" << lineEdit->text() << endl;
  else
    out << "PUB|" << label_whom->text() << "|" << lineEdit->text() << endl;
  out.flush();
  appendMsg(tr("<font color='blue'>我</font>对<font color='blue'>")
	    + label_whom->text() + tr("</font>说：") + lineEdit->text() + "<br />");
  lineEdit->clear();
}

void Chat::recvMsg()
{
  if (!tcpSocket->canReadLine())
    return;
  QString msg;
  do {
    msg += QString::fromUtf8((tcpSocket->readLine()).data());
  } while (tcpSocket->canReadLine());
  handleMsg(msg);
}

void Chat::handleMsg(QString msg)
{
  QStringList responses = msg.split("\n", QString::SkipEmptyParts);
  foreach (QString res, responses) {
    QStringList resl = res.split("|");
    if (resl[0] == "USRL"){
      resl.removeAt(0);
      userList += resl;
      model->setStringList(userList);
    } else if (resl[0] == "ADD") {
      userList << resl[1];
      model->setStringList(userList);
      appendMsg(tr("欢迎<font color='green'>") + resl[1]
		+ tr("</font>登陆聊天室") + "<br />");
    } else if (resl[0] == "DEL") {
      if (label_whom->text() == resl[1]) {
	QMessageBox::warning(this, tr("服务器错误"),
			     resl[1] + tr("已下线，不能和他/她公聊了"));
	label_whom->setText(tr("所有人"));
      }
      if (privs.find(resl[1]) != privs.end()) {
	PrivChat *p = privs[resl[1]];
	if (p->isVisible())
	  QMessageBox::warning(this, tr("服务器错误"),
			       resl[1] + tr("已下线，不能和他/她私聊了"));
	privs.remove(resl[1]);
	delete p;
      }
      userList.removeAt(userList.indexOf(resl[1]));
      model->setStringList(userList);
      appendMsg(tr("<font color='green'>") + resl[1]
		+ tr("</font>离开聊天室") + "<br />");
    } else if (resl[0]=="STOALL")
      appendMsg(resl[1] + tr("对所有人说：") + resl[2] + "<br />");
    else if (resl[0] == "PUBTOME")
      appendMsg("<font color='blue'>" + resl[1]
		+ tr("</font>对<font color='blue'>我</font>说：")
		+ resl[2] + "<br />");
    else if (resl[0] == "SPUB")
      appendMsg(resl[1] + tr("对") + resl[2] + tr("说：") + resl[3] + "<br />");
    else if (resl[0] == "SPRIV") {
      if (!privs[resl[1]])
	privs[resl[1]] = new PrivChat(myname, resl[1], tcpSocket);
      PrivChat *p = privs[resl[1]];
      p->show();
      p->msgBuffer += "<font color='blue'>" + resl[1]
	+ tr("</font>对<font color='blue'>我</font>说：") + resl[2] + "<br />";
      p->textBrowser->setText(p->msgBuffer);
      p->textBrowser->moveCursor(QTextCursor::End);
    } else if (resl[0] == "ERRTARG") {/* nothing to do */}
  }
}

void Chat::updateWhom(const QModelIndex &idx)
{
  label_whom->setText(model->data(idx, Qt::EditRole).toString());
}

void Chat::openPriv(const QModelIndex &idx)
{
  QString yourname = model->data(idx, Qt::EditRole).toString();
  if (yourname == tr("所有人"))
    return;
  if (!privs[yourname])
    privs[yourname] = new PrivChat(myname, yourname, tcpSocket);
  PrivChat *p = privs[yourname];
  p->show();
  p->activateWindow();
  p->raise();
}

void Chat::error()
{
  QMessageBox::critical(this, tr("网络错误"),
			tr("socket出错：")+tcpSocket->errorString());
  tcpSocket->close();
}

void Chat::appendMsg(QString msg)
{
  msgBuffer += msg;
  textBrowser->setText(msgBuffer);
  textBrowser->moveCursor(QTextCursor::End);
}
