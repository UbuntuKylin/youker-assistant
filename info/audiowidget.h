#ifndef AUDIOWIDGET_H
#define AUDIOWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include "computerpage.h"
#include "../component/scrollwidget.h"
#include <QMap>
#include <QVariant>

class SystemDispatcher;

class AudioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AudioWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    int initData();

signals:

public slots:

private:
    ScrollWidget *scroll_widget;
//    ComputerPage *page;
    QMap<QString, QVariant> audio_info_map;
    QMap<QString, QVariant> tmp_info_map;
    SystemDispatcher *systemproxy;
    int mulNum;
};

#endif // AUDIOWIDGET_H
