/********************************************************************************
** Form generated from reading UI file 'alertdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALERTDIALOG_H
#define UI_ALERTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AlertDialog
{
public:
    QPushButton *alertBG;

    void setupUi(QWidget *AlertDialog)
    {
        if (AlertDialog->objectName().isEmpty())
            AlertDialog->setObjectName(QString::fromUtf8("AlertDialog"));
        AlertDialog->resize(200, 75);
        alertBG = new QPushButton(AlertDialog);
        alertBG->setObjectName(QString::fromUtf8("alertBG"));
        alertBG->setGeometry(QRect(0, 0, 200, 75));

        retranslateUi(AlertDialog);

        QMetaObject::connectSlotsByName(AlertDialog);
    } // setupUi

    void retranslateUi(QWidget *AlertDialog)
    {
        AlertDialog->setWindowTitle(QApplication::translate("AlertDialog", "Form", 0, QApplication::UnicodeUTF8));
        alertBG->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AlertDialog: public Ui_AlertDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALERTDIALOG_H
