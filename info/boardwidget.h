#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SystemDispatcher;

class BoardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoardWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    void initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
    QMap<QString, QVariant> board_info_map;
    SystemDispatcher *systemproxy;
};

#endif // BOARDWIDGET_H
