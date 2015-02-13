#ifndef CACHEACTIONWIDGET_H
#define CACHEACTIONWIDGET_H

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

class MainWindow;
class CacheActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CacheActionWidget(QWidget *parent = 0);
    ~CacheActionWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage();

private:
    QLabel *img_label;
    QLabel *title_label;
    QLabel *description_label;

    MainWindow *p_mainwindow;
};

#endif // CACHEACTIONWIDGET_H




