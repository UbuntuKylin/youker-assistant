#ifndef NICWIDGET_H
#define NICWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SystemDispatcher;

class NicWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NicWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    void initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
    ComputerPage *page2;
    QMap<QString, QVariant> wire_info_map;
    QMap<QString, QVariant> wireless_info_map;
    SystemDispatcher *systemproxy;
};

#endif // NICWIDGET_H
