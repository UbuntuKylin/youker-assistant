#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>

class SystemDispatcher;

class MemoryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MemoryWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    int initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
//    ComputerPage *page;
    QMap<QString, QVariant> memory_info_map;
    QMap<QString, QVariant> tmp_info_map;
    SystemDispatcher *systemproxy;
    int memoryNum;
};

#endif // MEMORYWIDGET_H
