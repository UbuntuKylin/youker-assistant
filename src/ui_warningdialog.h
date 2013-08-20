/********************************************************************************
** Form generated from reading UI file 'warningdialog.ui'
**
** Created: Tue Aug 20 11:29:27 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WARNINGDIALOG_H
#define UI_WARNINGDIALOG_H

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

class Ui_WarningDialog
{
public:
    QPushButton *okButton;
    QLabel *btn_close;
    QLabel *btn_min;
    QLabel *displaylabel;
    QLabel *label;
    QFrame *frame;

    void setupUi(QDialog *WarningDialog)
    {
        if (WarningDialog->objectName().isEmpty())
            WarningDialog->setObjectName(QString::fromUtf8("WarningDialog"));
        WarningDialog->resize(329, 195);
        okButton = new QPushButton(WarningDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(224, 156, 94, 29));
        okButton->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/ok.png);"));
        btn_close = new QLabel(WarningDialog);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setGeometry(QRect(10, 6, 26, 20));
        btn_min = new QLabel(WarningDialog);
        btn_min->setObjectName(QString::fromUtf8("btn_min"));
        btn_min->setGeometry(QRect(33, 6, 26, 20));
        displaylabel = new QLabel(WarningDialog);
        displaylabel->setObjectName(QString::fromUtf8("displaylabel"));
        displaylabel->setGeometry(QRect(8, 85, 311, 51));
        displaylabel->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/message.png);"));
        displaylabel->setPixmap(QPixmap(QString::fromUtf8(":/pixmap/image/message.png")));
        label = new QLabel(WarningDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(14, 51, 291, 16));
        frame = new QFrame(WarningDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 329, 195));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/pixmap/image/dialog-bg.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        frame->raise();
        okButton->raise();
        btn_close->raise();
        btn_min->raise();
        displaylabel->raise();
        label->raise();

        retranslateUi(WarningDialog);

        QMetaObject::connectSlotsByName(WarningDialog);
    } // setupUi

    void retranslateUi(QDialog *WarningDialog)
    {
        WarningDialog->setWindowTitle(QApplication::translate("WarningDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        okButton->setText(QString());
        btn_close->setText(QString());
        btn_min->setText(QString());
        displaylabel->setText(QApplication::translate("WarningDialog", "\345\257\271\344\270\215\350\265\267\357\274\214\346\202\250\346\262\241\346\234\211\351\200\211\344\270\255\345\216\206\345\217\262\350\256\260\345\275\225\346\211\253\346\217\217\351\241\271\357\274\214\350\257\267\351\200\211\344\270\255\357\274\201", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WarningDialog", "\345\217\213\346\203\205\346\217\220\347\244\272\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WarningDialog: public Ui_WarningDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WARNINGDIALOG_H
