#ifndef HDWIDGET_H
#define HDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SystemDispatcher;

class HDWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HDWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    int initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
//    ComputerPage *page;
    QMap<QString, QVariant> hd_info_map;
    QMap<QString, QVariant> tmp_info_map;
    SystemDispatcher *systemproxy;
    int diskNum;
};

#endif // HDWIDGET_H
