#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SystemDispatcher;

class CpuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CpuWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    void initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
    QMap<QString, QVariant> cpu_info_map;
    SystemDispatcher *systemproxy;
};

#endif // CPUWIDGET_H
