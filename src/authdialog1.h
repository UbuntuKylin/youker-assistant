#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>
#include <QPoint>
#include <QStackedWidget>
//#include <QDeclarativeView>
//#include <QApplication>
//#include <QMouseEvent>
//#include <QBoxLayout>

#include <QDeclarativeView>
#include <QApplication>
#include <QMouseEvent>
#include "QPoint"
#include <QBoxLayout>
#include <QStackedWidget>

//namespace Ui {
//class AuthDialog;
//}

class AuthDialog : public QDialog
//class AuthDialog : public QStackedWidget
{
    Q_OBJECT
    
public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();
//    QString passwd;
//    void mousePressEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
    QDeclarativeView *view;
    
private:
//    Ui::AuthDialog *ui;
    QPoint dragPosition;

    QBoxLayout *layout;

private slots:
    void on_quitBtn_clicked();
    void on_okBtn_clicked();

};

#endif // AUTHDIALOG_H
