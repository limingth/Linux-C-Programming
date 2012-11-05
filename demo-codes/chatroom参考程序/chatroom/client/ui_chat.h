/********************************************************************************
** Form generated from reading ui file 'chat.ui'
**
** Created: Sun May 25 11:18:13 2008
**      by: Qt User Interface Compiler version 4.4.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListView>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Chat
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QTextBrowser *textBrowser;
    QListView *listView;
    QHBoxLayout *hboxLayout1;
    QLabel *label_to;
    QLabel *label_whom;
    QLabel *label_say;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *Chat)
    {
    if (Chat->objectName().isEmpty())
        Chat->setObjectName(QString::fromUtf8("Chat"));
    Chat->resize(566, 384);
    vboxLayout = new QVBoxLayout(Chat);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    textBrowser = new QTextBrowser(Chat);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
    textBrowser->setSizePolicy(sizePolicy);

    hboxLayout->addWidget(textBrowser);

    listView = new QListView(Chat);
    listView->setObjectName(QString::fromUtf8("listView"));
    listView->setMinimumSize(QSize(100, 0));
    listView->setMaximumSize(QSize(120, 16777215));

    hboxLayout->addWidget(listView);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label_to = new QLabel(Chat);
    label_to->setObjectName(QString::fromUtf8("label_to"));

    hboxLayout1->addWidget(label_to);

    label_whom = new QLabel(Chat);
    label_whom->setObjectName(QString::fromUtf8("label_whom"));
    label_whom->setMinimumSize(QSize(100, 0));
    label_whom->setMaximumSize(QSize(100, 16777215));

    hboxLayout1->addWidget(label_whom);

    label_say = new QLabel(Chat);
    label_say->setObjectName(QString::fromUtf8("label_say"));

    hboxLayout1->addWidget(label_say);

    lineEdit = new QLineEdit(Chat);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    hboxLayout1->addWidget(lineEdit);

    pushButton = new QPushButton(Chat);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    hboxLayout1->addWidget(pushButton);


    vboxLayout->addLayout(hboxLayout1);


    retranslateUi(Chat);

    QMetaObject::connectSlotsByName(Chat);
    } // setupUi

    void retranslateUi(QDialog *Chat)
    {
    Chat->setWindowTitle(QApplication::translate("Chat", "\350\201\212\345\244\251\345\256\244", 0, QApplication::UnicodeUTF8));
    label_to->setText(QApplication::translate("Chat", "\345\257\271", 0, QApplication::UnicodeUTF8));
    label_whom->setText(QApplication::translate("Chat", "\346\211\200\346\234\211\344\272\272", 0, QApplication::UnicodeUTF8));
    label_say->setText(QApplication::translate("Chat", "\350\257\264\357\274\232", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("Chat", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Chat);
    } // retranslateUi

};

namespace Ui {
    class Chat: public Ui_Chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
