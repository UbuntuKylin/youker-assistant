#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"

class MainWindow;

class ToolWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ToolWidget(QWidget *parent = 0);
    ~ToolWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void initConnect();

signals:
    void turnCurrentPage(int index);

public slots:
    void switchPageIndex(QString index);
    void showBoxTool();

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;
    QList<KylinToolButton *> button_list;

    MainWindow *p_mainwindow;
};

#endif // TOOLWIDGET_H
