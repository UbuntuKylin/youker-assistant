#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

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

class MainWindow;

class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
    ~TitleWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void initConnect();

signals:
    void closeApp();

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;
    SystemButton *min_button;
    SystemButton *close_button;
    SystemButton *skin_button;
    SystemButton *main_menu_button;

    MainWindow *p_mainwindow;
};

#endif // TITLEWIDGET_H
