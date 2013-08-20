/********************************************************************************
** Form generated from reading UI file 'messagedialog.ui'
**
** Created: Tue Aug 20 11:46:41 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSAGEDIALOG_H
#define UI_MESSAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MessageDialog
{
public:
    QPushButton *okButton;
    QLabel *btn_close;
    QLabel *btn_min;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *frame;

    void setupUi(QDialog *MessageDialog)
    {
        if (MessageDialog->objectName().isEmpty())
            MessageDialog->setObjectName(QString::fromUtf8("MessageDialog"));
        MessageDialog->resize(329, 195);
        okButton = new QPushButton(MessageDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(120, 157, 94, 29));
        okButton->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/ok.png);"));
        btn_close = new QLabel(MessageDialog);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(10, 6, 26, 20));
        btn_min = new QLabel(MessageDialog);
        btn_min->setObjectName(QString::fromUtf8("btn_min"));
        btn_min->setGeometry(QRect(33, 6, 26, 20));
        label = new QLabel(MessageDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 50, 24, 24));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/feature1.png);"));
        label_2 = new QLabel(MessageDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 80, 24, 24));
        label_2->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/feature2.png);"));
        label_3 = new QLabel(MessageDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 110, 24, 24));
        label_3->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/feature3.png);"));
        label_4 = new QLabel(MessageDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 54, 221, 16));
        label_5 = new QLabel(MessageDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(60, 84, 201, 16));
        label_6 = new QLabel(MessageDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(60, 114, 221, 16));
        frame = new QFrame(MessageDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 329, 195));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/dialog-feature.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        okButton->raise();
        btn_close->raise();
        btn_min->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_6->raise();

        retranslateUi(MessageDialog);

        QMetaObject::connectSlotsByName(MessageDialog);
    } // setupUi

    void retranslateUi(QDialog *MessageDialog)
    {
        MessageDialog->setWindowTitle(QApplication::translate("MessageDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        okButton->setText(QString());
        btn_close->setText(QString());
        btn_min->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QApplication::translate("MessageDialog", "\346\224\257\346\214\201\344\270\200\351\224\256\346\270\205\347\220\206\345\222\214\351\200\211\346\213\251\346\200\247\347\263\273\347\273\237\346\270\205\347\220\206", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MessageDialog", "\346\224\257\346\214\201\345\270\270\350\247\201\347\232\204\345\220\204\347\247\215\347\263\273\347\273\237\347\276\216\345\214\226\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MessageDialog", "\344\270\272\347\224\250\346\210\267\345\261\225\347\244\272\345\275\223\345\211\215\346\234\272\345\231\250\345\222\214\347\263\273\347\273\237\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MessageDialog: public Ui_MessageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSAGEDIALOG_H
