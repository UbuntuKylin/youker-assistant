#ifndef GENERALDIALOG_H
#define GENERALDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QStyleOption>

#include "systembutton.h"

class SystemButton;

class GeneralDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GeneralDialog(QWidget *parent = 0, QString text = "", bool warn = false, bool showCancel = false );
    ~GeneralDialog();

    void paintEvent(QPaintEvent *event);
public slots:

    void onclickCloseBtn();
    void onclickOkBtn();

private:
    QLabel *contentLabel;

    QPushButton *cancelBtn;
    QPushButton *okBtn;
};

#endif // GENERALDIALOG_H
