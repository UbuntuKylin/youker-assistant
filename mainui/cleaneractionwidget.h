#ifndef CLEANERACTIONWIDGET_H
#define CLEANERACTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"
#include "../component/systembutton.h"
#include "../component/loadinglabel.h"
#include <QStackedWidget>

//class MainWindow;
class SessionDispatcher;
class SystemDispatcher;
//class CacheActionWidget;

class CleanerActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CleanerActionWidget(QWidget *parent = 0);
    ~CleanerActionWidget();
//    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setSessionDbusProxy(SessionDispatcher* dispatcher) { sessionProxy = dispatcher;}
    void setSystemDbusProxy(SystemDispatcher* dispatcher) { systemProxy = dispatcher;}
    void initConnect();
    void setLanguage();

public slots:
    void onStartButtonClicked();
    void onCleanButtonClicked();
    void onBackButtonClicked();
    void showReciveStatus(const QString &status);

signals:
    void showDetailData();
    void showMainData();

private:
//    QStackedWidget *statked_widget;
//    CacheActionWidget *cache_page;
    bool is_move;
    LoadingLabel *loading_label;
    QLabel *suggest_label;
//    QLabel *result_label;
    QLabel *doing_label;
    QPushButton *scan_button;
    QPushButton *clean_button;
    QPushButton *back_button;

//    MainWindow *p_mainwindow;
    SystemDispatcher *systemProxy;
    SessionDispatcher *sessionProxy;
};

#endif // CLEANERACTIONWIDGET_H
