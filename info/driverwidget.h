#ifndef DRIVERWIDGET_H
#define DRIVERWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
//class SystemDispatcher;

class DriverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DriverWidget(QWidget *parent = 0/*, SystemDispatcher *proxy = 0*/);
    void initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
    QMap<QString, QVariant> driver_info_map;
//    SystemDispatcher *systemproxy;
};

#endif // DRIVERWIDGET_H
