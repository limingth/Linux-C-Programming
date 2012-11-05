/********************************************************************************
** Form generated from reading ui file 'privchat.ui'
**
** Created: Sun May 25 11:18:13 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PRIVCHAT_H
#define UI_PRIVCHAT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_PrivChat
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *PrivChat)
    {
    if (PrivChat->objectName().isEmpty())
        PrivChat->setObjectName(QString::fromUtf8("PrivChat"));
    PrivChat->resize(400, 300);
    gridLayout = new QGridLayout(PrivChat);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    textBrowser = new QTextBrowser(PrivChat);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

    gridLayout->addWidget(textBrowser, 0, 0, 1, 2);

    lineEdit = new QLineEdit(PrivChat);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

    pushButton = new QPushButton(PrivChat);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    gridLayout->addWidget(pushButton, 1, 1, 1, 1);


    retranslateUi(PrivChat);

    QMetaObject::connectSlotsByName(PrivChat);
    } // setupUi

    void retranslateUi(QDialog *PrivChat)
    {
    PrivChat->setWindowTitle(QApplication::translate("PrivChat", "\347\247\201\350\201\212", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("PrivChat", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(PrivChat);
    } // retranslateUi

};

namespace Ui {
    class PrivChat: public Ui_PrivChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRIVCHAT_H
