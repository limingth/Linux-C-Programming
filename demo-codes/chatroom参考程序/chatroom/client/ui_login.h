/********************************************************************************
** Form generated from reading ui file 'login.ui'
**
** Created: Sun May 25 11:18:13 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_login;
    QGridLayout *gridLayout1;
    QLabel *label_name;
    QLineEdit *lineEdit_name;
    QLabel *label_pass;
    QLineEdit *lineEdit_pass;
    QGroupBox *groupBox_reg;
    QGridLayout *gridLayout2;
    QLabel *label_regname;
    QLineEdit *lineEdit_regname;
    QLabel *label_regpass;
    QLineEdit *lineEdit_regpass;
    QLabel *label_regpass2;
    QLineEdit *lineEdit_regpass2;
    QLabel *label_ip;
    QLineEdit *lineEdit_ip;
    QPushButton *pushButton_login;
    QPushButton *pushButton_reg;

    void setupUi(QDialog *Login)
    {
    if (Login->objectName().isEmpty())
        Login->setObjectName(QString::fromUtf8("Login"));
    Login->resize(412, 288);
    gridLayout = new QGridLayout(Login);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    groupBox_login = new QGroupBox(Login);
    groupBox_login->setObjectName(QString::fromUtf8("groupBox_login"));
    gridLayout1 = new QGridLayout(groupBox_login);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    label_name = new QLabel(groupBox_login);
    label_name->setObjectName(QString::fromUtf8("label_name"));

    gridLayout1->addWidget(label_name, 0, 0, 1, 1);

    lineEdit_name = new QLineEdit(groupBox_login);
    lineEdit_name->setObjectName(QString::fromUtf8("lineEdit_name"));
    lineEdit_name->setMaxLength(10);

    gridLayout1->addWidget(lineEdit_name, 0, 1, 1, 1);

    label_pass = new QLabel(groupBox_login);
    label_pass->setObjectName(QString::fromUtf8("label_pass"));

    gridLayout1->addWidget(label_pass, 1, 0, 1, 1);

    lineEdit_pass = new QLineEdit(groupBox_login);
    lineEdit_pass->setObjectName(QString::fromUtf8("lineEdit_pass"));
    lineEdit_pass->setMaxLength(10);
    lineEdit_pass->setEchoMode(QLineEdit::Password);

    gridLayout1->addWidget(lineEdit_pass, 1, 1, 1, 1);


    gridLayout->addWidget(groupBox_login, 0, 0, 1, 4);

    groupBox_reg = new QGroupBox(Login);
    groupBox_reg->setObjectName(QString::fromUtf8("groupBox_reg"));
    gridLayout2 = new QGridLayout(groupBox_reg);
    gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
    label_regname = new QLabel(groupBox_reg);
    label_regname->setObjectName(QString::fromUtf8("label_regname"));

    gridLayout2->addWidget(label_regname, 0, 0, 1, 1);

    lineEdit_regname = new QLineEdit(groupBox_reg);
    lineEdit_regname->setObjectName(QString::fromUtf8("lineEdit_regname"));
    lineEdit_regname->setMaxLength(10);

    gridLayout2->addWidget(lineEdit_regname, 0, 1, 1, 1);

    label_regpass = new QLabel(groupBox_reg);
    label_regpass->setObjectName(QString::fromUtf8("label_regpass"));

    gridLayout2->addWidget(label_regpass, 1, 0, 1, 1);

    lineEdit_regpass = new QLineEdit(groupBox_reg);
    lineEdit_regpass->setObjectName(QString::fromUtf8("lineEdit_regpass"));
    lineEdit_regpass->setMaxLength(10);
    lineEdit_regpass->setEchoMode(QLineEdit::Password);

    gridLayout2->addWidget(lineEdit_regpass, 1, 1, 1, 1);

    label_regpass2 = new QLabel(groupBox_reg);
    label_regpass2->setObjectName(QString::fromUtf8("label_regpass2"));

    gridLayout2->addWidget(label_regpass2, 2, 0, 1, 1);

    lineEdit_regpass2 = new QLineEdit(groupBox_reg);
    lineEdit_regpass2->setObjectName(QString::fromUtf8("lineEdit_regpass2"));
    lineEdit_regpass2->setMaxLength(10);
    lineEdit_regpass2->setEchoMode(QLineEdit::Password);

    gridLayout2->addWidget(lineEdit_regpass2, 2, 1, 1, 1);


    gridLayout->addWidget(groupBox_reg, 1, 0, 1, 4);

    label_ip = new QLabel(Login);
    label_ip->setObjectName(QString::fromUtf8("label_ip"));

    gridLayout->addWidget(label_ip, 2, 0, 1, 1);

    lineEdit_ip = new QLineEdit(Login);
    lineEdit_ip->setObjectName(QString::fromUtf8("lineEdit_ip"));
    lineEdit_ip->setMaxLength(15);

    gridLayout->addWidget(lineEdit_ip, 2, 1, 1, 1);

    pushButton_login = new QPushButton(Login);
    pushButton_login->setObjectName(QString::fromUtf8("pushButton_login"));

    gridLayout->addWidget(pushButton_login, 2, 2, 1, 1);

    pushButton_reg = new QPushButton(Login);
    pushButton_reg->setObjectName(QString::fromUtf8("pushButton_reg"));
    pushButton_reg->setCheckable(true);

    gridLayout->addWidget(pushButton_reg, 2, 3, 1, 1);


    retranslateUi(Login);

    QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
    Login->setWindowTitle(QApplication::translate("Login", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
    groupBox_login->setTitle(QApplication::translate("Login", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
    label_name->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
    lineEdit_name->setText(QString());
    label_pass->setText(QApplication::translate("Login", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
    lineEdit_pass->setText(QString());
    groupBox_reg->setTitle(QApplication::translate("Login", "\346\263\250\345\206\214\345\271\266\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
    label_regname->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
    label_regpass->setText(QApplication::translate("Login", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
    label_regpass2->setText(QApplication::translate("Login", "\345\206\215\350\276\223\344\270\200\351\201\215\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
    label_ip->setText(QApplication::translate("Login", "\346\234\215\345\212\241\345\231\250IP", 0, QApplication::UnicodeUTF8));
    lineEdit_ip->setText(QString());
    pushButton_login->setText(QApplication::translate("Login", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
    pushButton_reg->setText(QApplication::translate("Login", "\346\263\250\345\206\214", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Login);
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
