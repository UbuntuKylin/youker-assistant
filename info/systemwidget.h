#ifndef SYSTEMWIDGET_H
#define SYSTEMWIDGET_H

#include <QWidget>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SystemDispatcher;

class SystemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SystemWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    void initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
//    ComputerPage *page2;
    QMap<QString, QVariant> sys_info_map;
    SystemDispatcher *systemproxy;
};

#endif // SYSTEMWIDGET_H
