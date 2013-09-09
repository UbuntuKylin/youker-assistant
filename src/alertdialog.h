#ifndef ALERTDIALOG_H
#define ALERTDIALOG_H

#include <QWidget>
#include <QtGui>

namespace Ui {
class AlertDialog;
}

class AlertDialog : public QWidget
{
    Q_OBJECT
    
public:
    explicit AlertDialog(QWidget *parent = 0);
    ~AlertDialog();
    void paintEvent(QPaintEvent *);
    void setMSG(QString);
private:
    Ui::AlertDialog *ui;
};

#endif // ALERTDIALOG_H
