#include <QHostAddress>
#include <QMessageBox>
#include "login.h"

Login::Login(QString *myname, QTcpSocket *s, QWidget *parent)
  : QDialog(parent), tcpSocket(s), myname(myname)
{
  setupUi(this);
  groupBox_reg->hide();
  layout()->setSizeConstraint(QLayout::SetFixedSize);
  connect(pushButton_reg, SIGNAL(toggled(bool)), this, SLOT(switchVisible(bool)));
  connect(pushButton_login, SIGNAL(clicked()), this, SLOT(sendMsg()));
}

void Login::sendMsg()
{
  QRegExp r("(\\d{1,3}\\.){3}\\d{1,3}");
  if (!r.exactMatch(lineEdit_ip->text())) {
    QMessageBox::warning(this, tr("输入错误"), tr("IP地址格式错误"));
    return;
  }
  QRegExp r2("[^|\\n]+");
  if (pushButton_reg->isChecked()) {
    if (lineEdit_regname->text().isEmpty()
       || lineEdit_regpass->text().isEmpty()
       || lineEdit_regpass2->text().isEmpty()) {
      QMessageBox::warning(this, tr("输入错误"), tr("用户名和密码不能为空"));
      return;
    }
    if (!r2.exactMatch(lineEdit_regname->text())
       || !r2.exactMatch(lineEdit_regpass->text())
       || !r2.exactMatch(lineEdit_regpass2->text())) {
      QMessageBox::warning(this, tr("输入错误"), tr("用户名或密码包含非法字符"));
      return;
    }
    if (lineEdit_regname->text() == tr("所有人")
	|| lineEdit_regname->text() == "admin") {
      QMessageBox::warning(this, tr("输入错误"), tr("该用户名被系统保留，不得使用"));
      return;
    }
    if (lineEdit_regpass->text() != lineEdit_regpass2->text()) {
      QMessageBox::warning(this, tr("输入错误"), tr("两次输入的密码不相符"));
      return;
    }
  } else {			// pushButton_reg not checked
    if (lineEdit_name->text().isEmpty()
       || lineEdit_pass->text().isEmpty()) {
      QMessageBox::warning(this, tr("输入错误"), tr("用户名和密码不能为空"));
      return;
    }
    if (!r2.exactMatch(lineEdit_name->text())
       || !r2.exactMatch(lineEdit_pass->text())) {
      QMessageBox::warning(this, tr("输入错误"), tr("用户名或密码包含非法字符"));
      return;
    }
    if (lineEdit_name->text() == tr("所有人")) {
      QMessageBox::warning(this, tr("输入错误"), tr("该用户名被系统保留，不得使用"));
      return;
    }
  }

  if (tcpSocket->state() == QAbstractSocket::UnconnectedState) {
    tcpSocket->connectToHost(lineEdit_ip->text(), 4869);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if (!tcpSocket->waitForConnected(3000)) {
      QApplication::restoreOverrideCursor();
      QMessageBox::critical(this, tr("网络错误"), tr("无法连接服务器"));
      tcpSocket->close();
      return;
    }
    QApplication::restoreOverrideCursor();
  }
  QTextStream out(tcpSocket);
  if (pushButton_reg->isChecked()) {
    out << "REG|" << lineEdit_regname->text() << "|" << lineEdit_regpass->text() << endl;
  } else {
    out << "LOGIN|" << lineEdit_name->text() << "|" << lineEdit_pass->text() << endl;
  }
  out.flush();
  QApplication::setOverrideCursor(Qt::WaitCursor);
  if (!tcpSocket->waitForReadyRead(3000)) {
    QApplication::restoreOverrideCursor();
    QMessageBox::critical(this, tr("网络错误"), tr("服务器出错或无响应"));
    tcpSocket->close();
    return;
  }
  QApplication::restoreOverrideCursor();
  if (!tcpSocket->canReadLine()) {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    sleep(3);
    QApplication::restoreOverrideCursor();
  }
  if (!tcpSocket->canReadLine()) {
    QMessageBox::critical(this, tr("网络错误"), tr("服务器无响应"));
    tcpSocket->close();
    return;
  }

  QString response = QString::fromUtf8((tcpSocket->readLine()).data());
  response = response.trimmed();
  if (response != "OK") {
    if (response == "ERRREGEXIST")
      QMessageBox::warning(this, tr("服务器错误"), tr("该用户名已被注册"));
    else if (response == "ERRLOGIN")
      QMessageBox::warning(this, tr("服务器错误"), tr("用户名或密码错误"));
    else if (response == "ERRONLINE")
      QMessageBox::warning(this, tr("服务器错误"), tr("该用户已在线，不能重复登录"));
    return;
  }
  if (pushButton_reg->isChecked()) {
    *myname = lineEdit_regname->text();
  } else {
    *myname = lineEdit_name->text();
  }
  this->accept();
}

void Login::switchVisible(bool s)
{
  if (s) {
    groupBox_login->hide();
    groupBox_reg->show();
  } else {
    groupBox_login->show();
    groupBox_reg->hide();
  }
}
