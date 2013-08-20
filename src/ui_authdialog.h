/********************************************************************************
** Form generated from reading UI file 'authdialog.ui'
**
** Created: Tue Aug 20 11:29:27 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHDIALOG_H
#define UI_AUTHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AuthDialog
{
public:
    QPushButton *closeButton;
    QPushButton *okButton;
    QLabel *btn_close;
    QLabel *btn_min;
    QLabel *msg_label;
    QLabel *label;
    QLineEdit *lineEdit;
    QFrame *frame;

    void setupUi(QDialog *AuthDialog)
    {
        if (AuthDialog->objectName().isEmpty())
            AuthDialog->setObjectName(QString::fromUtf8("AuthDialog"));
        AuthDialog->resize(329, 195);
        closeButton = new QPushButton(AuthDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(230, 156, 94, 29));
        closeButton->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/quit.png);"));
        okButton = new QPushButton(AuthDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(120, 156, 94, 29));
        okButton->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/ok.png);"));
        btn_close = new QLabel(AuthDialog);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(10, 6, 26, 20));
        btn_min = new QLabel(AuthDialog);
        btn_min->setObjectName(QString::fromUtf8("btn_min"));
        btn_min->setGeometry(QRect(33, 6, 26, 20));
        msg_label = new QLabel(AuthDialog);
        msg_label->setObjectName(QString::fromUtf8("msg_label"));
        msg_label->setGeometry(QRect(14, 85, 305, 51));
        msg_label->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/message.png);"));
        msg_label->setPixmap(QPixmap(QString::fromUtf8(":/pixmap/image/message.png")));
        label = new QLabel(AuthDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(14, 51, 58, 16));
        lineEdit = new QLineEdit(AuthDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(74, 44, 241, 31));
        frame = new QFrame(AuthDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 329, 195));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/dialog-bg.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        closeButton->raise();
        okButton->raise();
        btn_close->raise();
        btn_min->raise();
        msg_label->raise();
        label->raise();
        lineEdit->raise();
        QWidget::setTabOrder(okButton, closeButton);
        QWidget::setTabOrder(closeButton, lineEdit);

        retranslateUi(AuthDialog);

        QMetaObject::connectSlotsByName(AuthDialog);
    } // setupUi

    void retranslateUi(QDialog *AuthDialog)
    {
        AuthDialog->setWindowTitle(QApplication::translate("AuthDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QString());
        okButton->setText(QString());
        btn_close->setText(QString());
        btn_min->setText(QString());
        msg_label->setText(QString());
        label->setText(QApplication::translate("AuthDialog", "\347\224\250\346\210\267\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        lineEdit->setPlaceholderText(QApplication::translate("AuthDialog", "\350\276\223\345\205\245\345\275\223\345\211\215\347\224\250\346\210\267\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AuthDialog: public Ui_AuthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHDIALOG_H
