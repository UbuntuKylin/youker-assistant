#ifndef CLEANERWIDGET_H
#define CLEANERWIDGET_H

#include <QWidget>
#include "kylinthread.h"
#include "../cleaner/cleanermainwidget.h"
#include "../cleaner/cleanerdetailwidget.h"
#include <QStackedWidget>

class SessionDispatcher;
class SystemDispatcher;
class MainWindow;

class CleanerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CleanerWidget(QWidget *parent = 0);
    ~CleanerWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setSessionDbusProxy(SessionDispatcher* dispatcher) { sessionProxy = dispatcher;}
    void setSystemDbusProxy(SystemDispatcher* dispatcher) { systemProxy = dispatcher;}
    void initUI();

public slots:
    void displayDetailPage();
    void displayMainPage();

private:
    KylinThread kthread;
    QStackedWidget *statked_widget;
    CleanerMainWidget *main_widget;
    CleanerDetailWidget *detail_widget;
    MainWindow *p_mainwindow;
    SystemDispatcher *systemProxy;
    SessionDispatcher *sessionProxy;
};

#endif // CLEANERWIDGET_H
