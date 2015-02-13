#ifndef AUTOSTART_H
#define AUTOSTART_H

#include <QDialog>

#include "../component/kylinlistwidget.h"
#include "../component/kylintitlebar.h"
#include "../component/autogroup.h"
//class KylinTitleBar;
//#include <QScrollArea>
//#include "../component/kylinscrollarea.h"

#include "../component/testscrollwidget.h"

class MainWindow;
class SessionDispatcher;
class AutoStart :public QDialog
{
  Q_OBJECT
public:
    AutoStart(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~AutoStart();
//    void setParentWindow(MainWindow *From) { mainwindow = From;}
    void setLanguage();
    void initConnect();
    void initData();

public slots:
    void onCloseButtonClicked();
    void onMinButtonClicked();
    void setCurrentItemAutoStatus(QString dekstopName);
    void readyReciveData(const QStringList &data);
    void readyShowUI();

private:
    void initTitleBar();

private:
    SessionDispatcher *sessionproxy;
//    MainWindow *mainwindow;
    KylinTitleBar *title_bar;
//    QWidget *bottom_widget;
//    KylinListWidget *list_widget;
//    QList<AutoGroup *> auto_list;
    QList<QStringList> data_list;
//    QScrollArea *scrollArea;
//    QWidget *panel;
//    KylinScrollArea  *scroll_widget;
    TestScrollWidget *scroll_widget;
};

#endif // AUTOSTART_H
