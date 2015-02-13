#ifndef DESKTOPWIDGET_H
#define DESKTOPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>
class SessionDispatcher;

class DesktopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DesktopWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    void initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
    ComputerPage *page;
    QMap<QString, QVariant> desktop_info_map;
    SessionDispatcher *sessionProxy;
};

#endif // DESKTOPWIDGET_H
