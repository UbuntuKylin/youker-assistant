#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>
#include "quibo.h"
namespace Ui {
class ModalDialog;
}

class ModalDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModalDialog(QWidget *parent = 0);
    ~ModalDialog();
    void monitor_check();
    
private:
    Ui::ModalDialog *ui;
    QPoint dragPos;
    QUIBO *qtui;

private slots:
    void on_closeButton_clicked();
    void on_okButton_clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MODALDIALOG_H
