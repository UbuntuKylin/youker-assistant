#ifndef BATTERYWIDGET_H
#define BATTERYWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SessionDispatcher;

class BatteryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    void initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
    QMap<QString, QVariant> battery_info_map;
    SessionDispatcher *sessionproxy;
};

#endif // BATTERYWIDGET_H
