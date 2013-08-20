/********************************************************************************
** Form generated from reading UI file 'modaldialog.ui'
**
** Created: Tue Aug 20 11:29:27 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODALDIALOG_H
#define UI_MODALDIALOG_H

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

class Ui_ModalDialog
{
public:
    QPushButton *closeButton;
    QPushButton *okButton;
    QLabel *btn_close;
    QLabel *btn_min;
    QLabel *displaylabel;
    QLabel *label;
    QFrame *frame;

    void setupUi(QDialog *ModalDialog)
    {
        if (ModalDialog->objectName().isEmpty())
            ModalDialog->setObjectName(QString::fromUtf8("ModalDialog"));
        ModalDialog->resize(329, 195);
        closeButton = new QPushButton(ModalDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(230, 156, 94, 29));
        closeButton->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/quit.png);"));
        okButton = new QPushButton(ModalDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(120, 156, 94, 29));
        okButton->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/ok.png);"));
        btn_close = new QLabel(ModalDialog);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(10, 6, 26, 20));
        btn_min = new QLabel(ModalDialog);
        btn_min->setObjectName(QString::fromUtf8("btn_min"));
        btn_min->setGeometry(QRect(33, 6, 26, 20));
        displaylabel = new QLabel(ModalDialog);
        displaylabel->setObjectName(QString::fromUtf8("displaylabel"));
        displaylabel->setGeometry(QRect(8, 85, 311, 51));
        displaylabel->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/message.png);"));
        displaylabel->setPixmap(QPixmap(QString::fromUtf8(":/pixmap/image/message.png")));
        label = new QLabel(ModalDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(14, 51, 291, 16));
        frame = new QFrame(ModalDialog);
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
        displaylabel->raise();
        label->raise();
        QWidget::setTabOrder(okButton, closeButton);

        retranslateUi(ModalDialog);

        QMetaObject::connectSlotsByName(ModalDialog);
    } // setupUi

    void retranslateUi(QDialog *ModalDialog)
    {
        ModalDialog->setWindowTitle(QApplication::translate("ModalDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QString());
        okButton->setText(QString());
        btn_close->setText(QString());
        btn_min->setText(QString());
        displaylabel->setText(QApplication::translate("ModalDialog", "\347\202\271\345\207\273\347\241\256\345\256\232\346\214\211\351\222\256\345\274\200\345\247\213\346\243\200\346\265\213 \357\274\214\346\243\200\346\265\213\350\277\207\347\250\213\344\270\255\347\202\271\345\207\273\351\274\240\346\240\207\345\267\246\351\224\256\346\233\264\346\215\242\351\242\234\350\211\262\357\274\214\347\202\271\345\207\273\345\217\263\351\224\256\351\200\200\345\207\272\343\200\202", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ModalDialog", "\345\261\217\345\271\225\345\235\217\347\202\271\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ModalDialog: public Ui_ModalDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODALDIALOG_H
