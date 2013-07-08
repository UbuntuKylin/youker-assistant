#ifndef MODELESSDIALOG_H
#define MODELESSDIALOG_H
#include <QDeclarativeView>
#include <QStackedWidget>
#include <QUrl>
#include <QBoxLayout>
#include "QPalette"
#include "QPoint"
#include <QMouseEvent>
#include <QDebug>
#include <qdebug.h>
#include <QDialog>

class ModelessDialog : public QDialog//public QStackedWidget
{
    Q_OBJECT
public:
    explicit ModelessDialog(QWidget *parent = 0);
    ~ModelessDialog();
//    void mouseMoveEvent(QMouseEvent*event);
//    void mousePressEvent(QMouseEvent*event);


private:
    QDeclarativeView *view;
    QPoint dragPosition;
};

#endif // MODELESSDIALOG_H
