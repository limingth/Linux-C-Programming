#include <QtNetwork>
#include <QApplication>
#include <QCryptographicHash>
#include "clientsocket.h"

QHash<QString, QByteArray> ClientSocket::passwds;
QHash<QString, ClientSocket *> ClientSocket::clients;

void ClientSocket::loadPasswd()
{
  QFile f("passwd");
  if (!f.open(QIODevice::ReadWrite)) {
    qDebug() << "cannot open passwd file";
    exit(1);
  }
  QList<QByteArray> lines = f.readAll().split('\n');
  for (int i=0; i<lines.count()-1; i++) {
    QList<QByteArray> fields = lines[i].split('|');
    passwds[QString::fromUtf8(fields[0])] = fields[1];
  }
  f.close();
}

ClientSocket::ClientSocket(QObject *parent)
  : QTcpSocket(parent)
{
  connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
  connect(this, SIGNAL(disconnected()), this, SLOT(disconnect()));
}

void ClientSocket::readClient()
{
  if (!canReadLine())
    return;
  QString msg;
  do {
    msg += QString::fromUtf8(readLine().data());
  } while (canReadLine());
  handleMsg(msg);
}

void ClientSocket::loginClient(QString name)
{
  QTextStream out(this);
  out << "OK" << endl;
  QHash<QString, ClientSocket *>::const_iterator i = clients.constBegin();

  if (i != clients.constEnd()) {
    out << "USRL";
    while ( i!= clients.constEnd()) {
      out << "|" << (*i)->name;
      i++;
    }
    out << endl;
  }
  out.flush();
  for (i=clients.constBegin(); i!=clients.constEnd(); i++) {
    out.setDevice(*i);
    out << "ADD|" << name << endl;
    out.flush();
  }
  this->name = name;
  clients[name] = this;
}

void ClientSocket::handleMsg(QString msg)
{
  QStringList requests = msg.split("\n", QString::SkipEmptyParts);
  QTextStream out;
  QHash<QString, ClientSocket *>::const_iterator i;
  foreach (QString req, requests) {
    QStringList reql = req.split("|");
    out.setDevice(this);
    if (reql[0] == "LOGIN") {
      if (passwds.find(reql[1]) == passwds.end()) {
	out << "ERRLOGIN" << endl;
	out.flush();
	continue;
      }
      QByteArray b = QCryptographicHash::hash(reql[2].toUtf8(), QCryptographicHash::Sha1)
	.replace("|", "").replace("\n", "");
      if (passwds[reql[1]] != b) {
	out << "ERRLOGIN" << endl;
	out.flush();
	continue;
      }
      if (clients.find(reql[1]) == clients.end())
	loginClient(reql[1]);
      else {
	out << "ERRONLINE" << endl;
	out.flush();
      }
    } else if (reql[0]=="REG") {
      if (passwds.find(reql[1]) != passwds.end()) {
	out << "ERRREGEXIST" << endl;
	out.flush();
	continue;
      }
      QByteArray b = QCryptographicHash::hash(reql[2].toUtf8(), QCryptographicHash::Sha1)
	.replace("|", "").replace("\n", "");
      passwds[reql[1]]=b;
      QFile f("passwd");
      if (!f.open(QIODevice::Append))
	qApp->exit(1);
      f.write(reql[1].toUtf8());
      f.write("|", 1);
      f.write(b);
      f.write("\n", 1);
      f.close();
      loginClient(reql[1]);
    } else if (reql[0] == "TOALL") {
      for (i=clients.constBegin(); i!=clients.constEnd(); i++) {
	if (*i == this)
	  continue;
	out.setDevice(*i);
	out << "STOALL|" << this->name << "|" << reql[1] << endl;
	out.flush();
      }
    } else if (reql[0] == "PUB") {
      if (clients.find(reql[1]) == clients.end()) {
	out << "ERRTARG" << endl;
	out.flush();
	continue;
      }
      ClientSocket *p = clients[reql[1]];
      out.setDevice(p);
      out << "PUBTOME|" << this->name << "|" << reql[2] << endl;
      out.flush();
      for (i=clients.constBegin(); i!=clients.constEnd(); i++) {
	if ((*i == this)||(*i == p))
	  continue;
	out.setDevice(*i);
	out << "SPUB|" << this->name << "|" << reql[1] << "|" << reql[2] << endl;
	out.flush();
      }
    } else if (reql[0] == "PRIV") {
      if (clients.find(reql[1]) == clients.end()) {
	out << "ERRTARG" << endl;
	out.flush();
	continue;
      }
      out.setDevice(clients[reql[1]]);
      out << "SPRIV|" << this->name << "|" << reql[2] << endl;
      out.flush();
    }
  }
}

void ClientSocket::disconnect()
{
  if (this->name != "") {
    clients.remove(this->name);
    QTextStream out;
    QHash<QString, ClientSocket *>::const_iterator i;
    for (i=clients.constBegin(); i!=clients.constEnd(); i++) {
      out.setDevice(*i);
      out << "DEL|" << this->name << endl;
      out.flush();
    }
  }
  deleteLater();
}
