#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

//class CommonToolButton;
#include <QToolButton>
class MainWindow;
class SessionDispatcher;
#include "autostartwidget.h"
#include "cameramanager.h"

class HomePage : public QWidget
{
    Q_OBJECT
public:
    explicit HomePage(QWidget *parent = 0);
    ~HomePage();
    void setLanguage();
    void initBoxTool();
    void initConnect();
    void setSessionDbusProxy(SessionDispatcher *dispatcher) { sessionProxy = dispatcher;}
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void initUI();

public slots:
    void switchPageIndex(QString index);

private:
    QLabel *version_logo;
    QLabel *version_title;
    QLabel *version_tip;
    QPushButton *check_btn;
    QLabel *box_logo;
    QLabel *box_title;
    QLabel *box_tip;
//    QList<CommonToolButton *> button_list;
    QList<QToolButton *> button_list;
    QPushButton *more_text_btn;
    QPushButton *more_btn;
    SessionDispatcher *sessionProxy;
//    CommonToolButton *software_btn;
//    CommonToolButton *boot_btn;
//    CommonToolButton *camera_btn;
    MainWindow *p_mainwindow;
    AutoStartWidget *auto_start;
    CameraManager *camera_manager;
};

#endif // HOMEPAGE_H
