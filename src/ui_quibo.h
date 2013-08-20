/********************************************************************************
** Form generated from reading UI file 'quibo.ui'
**
** Created: Tue Aug 20 11:46:40 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIBO_H
#define UI_QUIBO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QUIBO
{
public:
    QLabel *bg;

    void setupUi(QWidget *QUIBO)
    {
        if (QUIBO->objectName().isEmpty())
            QUIBO->setObjectName(QString::fromUtf8("QUIBO"));
        QUIBO->resize(400, 300);
        bg = new QLabel(QUIBO);
        bg->setObjectName(QString::fromUtf8("bg"));
        bg->setGeometry(QRect(0, 0, 5000, 5000));

        retranslateUi(QUIBO);

        QMetaObject::connectSlotsByName(QUIBO);
    } // setupUi

    void retranslateUi(QWidget *QUIBO)
    {
        QUIBO->setWindowTitle(QApplication::translate("QUIBO", "Form", 0, QApplication::UnicodeUTF8));
        bg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QUIBO: public Ui_QUIBO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIBO_H
