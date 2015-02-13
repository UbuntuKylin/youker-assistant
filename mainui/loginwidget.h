#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"
#include "../component/systembutton.h"

class SessionDispatcher;
//class MainWindow;

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
//    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setSessionDbusProxy(SessionDispatcher* dispatcher) { sessionProxy = dispatcher;}
    void setLauguage();
    void initConnect();

signals:

public slots:
    void onLoginButtonClicked();

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;
    QPushButton *login_button;
    QPushButton *logo_label;
    SessionDispatcher *sessionProxy;

//    MainWindow *p_mainwindow;
};

#endif // LOGINWIDGET_H
