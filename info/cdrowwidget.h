#ifndef CDROWWIDGET_H
#define CDROWWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SystemDispatcher;

class CDRowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CDRowWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    void initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
    QMap<QString, QVariant> cdrom_info_map;
    SystemDispatcher *systemproxy;
};

#endif // CDROWWIDGET_H
