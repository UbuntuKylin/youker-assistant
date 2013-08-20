/********************************************************************************
** Form generated from reading UI file 'restartdialog.ui'
**
** Created: Tue Aug 20 11:29:27 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTARTDIALOG_H
#define UI_RESTARTDIALOG_H

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

class Ui_RestartDialog
{
public:
    QLabel *btn_close;
    QPushButton *okButton;
    QLabel *displaylabel;
    QLabel *label;
    QFrame *frame;

    void setupUi(QDialog *RestartDialog)
    {
        if (RestartDialog->objectName().isEmpty())
            RestartDialog->setObjectName(QString::fromUtf8("RestartDialog"));
        RestartDialog->resize(329, 195);
        btn_close = new QLabel(RestartDialog);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(7, 10, 26, 20));
        okButton = new QPushButton(RestartDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(122, 157, 94, 29));
        okButton->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/ok.png);"));
        displaylabel = new QLabel(RestartDialog);
        displaylabel->setObjectName(QString::fromUtf8("displaylabel"));
        displaylabel->setGeometry(QRect(5, 89, 311, 51));
        displaylabel->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/message.png);"));
        displaylabel->setPixmap(QPixmap(QString::fromUtf8(":/pixmap/image/message.png")));
        label = new QLabel(RestartDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 55, 291, 16));
        frame = new QFrame(RestartDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 329, 195));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/dialog-bg.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        btn_close->raise();
        okButton->raise();
        displaylabel->raise();
        label->raise();

        retranslateUi(RestartDialog);

        QMetaObject::connectSlotsByName(RestartDialog);
    } // setupUi

    void retranslateUi(QDialog *RestartDialog)
    {
        RestartDialog->setWindowTitle(QApplication::translate("RestartDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        btn_close->setText(QString());
        okButton->setText(QString());
        displaylabel->setText(QApplication::translate("RestartDialog", "<html><head/><body><p>\346\202\250\347\263\273\347\273\237\344\270\212\347\232\204\344\274\230\345\256\242\345\212\251\346\211\213\346\230\257\347\254\254\344\270\200\346\254\241\345\220\257\345\212\250\347\233\270\345\205\263\346\234\215\345\212\241\357\274\214\350\257\267\347\202\271\345\207\273\342\200\234\347\241\256\350\256\244\342\200\235\346\214\211\351\222\256\345\205\263\351\227\255\357\274\214\347\204\266\345\220\216\351\207\215\345\220\257\344\274\230\345\256\242\345\212\251\346\211\213\343\200\202</p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RestartDialog", "\346\234\215\345\212\241\346\217\220\351\206\222\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RestartDialog: public Ui_RestartDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTARTDIALOG_H
