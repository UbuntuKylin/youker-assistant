#ifndef BOXACTIONWIDGET_H
#define BOXACTIONWIDGET_H

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

class MainWindow;

class BoxActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoxActionWidget(QWidget *parent = 0);
    ~BoxActionWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage();

private:
    QLabel *img_label;
    QLabel *title_label;
    QPushButton *more_btn;
    MainWindow *p_mainwindow;
};

#endif // BOXACTIONWIDGET_H
