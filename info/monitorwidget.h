#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SystemDispatcher;

class MonitorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    int initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
//    ComputerPage *page;
    QMap<QString, QVariant> monitor_info_map;
    QMap<QString, QVariant> tmp_info_map;
    SystemDispatcher *systemproxy;
    int vgaNum;
};

#endif // MONITORWIDGET_H
