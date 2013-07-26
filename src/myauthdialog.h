#ifndef MYAUTHDIALOG_H
#define MYAUTHDIALOG_H

#include <QDialog>

namespace Ui {
class MyauthDialog;
}

class MyauthDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MyauthDialog(QWidget *parent = 0);
    ~MyauthDialog();
    
private:
    Ui::MyauthDialog *ui;
    void setView();
    QPoint dragPos;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MYAUTHDIALOG_H
