#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>
//#include <QLabel>
//#include <QPushButton>
//#include <QMouseEvent>
//#include <QHBoxLayout>
//#include <QSignalMapper>
//#include <QVBoxLayout>
//#include "../component/kylinbutton.h"
//#include "../component/kylintoolbutton.h"
//#include "../component/systembutton.h"
//#include "../component/loadinglabel.h"

//class MainWindow;

class ActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActionWidget(QWidget *parent = 0);
    ~ActionWidget();
//    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
//    void initConnect();
//    void setLanguage();

public slots:
//    void onStartButtonClicked();
//    void onEndButtonClicked();

private:
//    QPoint press_point;//鼠标按下去的点
//    bool is_move;
//    LoadingLabel *loading_label;
//    QLabel *suggest_label;
//    QLabel *result_label;
//    QPushButton *scan_button;
//    QPushButton *back_button;

//    MainWindow *p_mainwindow;
};

#endif // ACTIONWIDGET_H
