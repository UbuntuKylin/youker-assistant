#ifndef TOOLKITS_H
#define TOOLKITS_H

#include <QObject>
#include <QtGui>
#include <QDebug>
#include "alertdialog.h"

class Toolkits : public QObject
{
    Q_OBJECT
public:
    explicit Toolkits(QObject *parent = 0);
    //启动alert提示
    Q_INVOKABLE void alertMSG(const QString &alertText, int parent_x, int parent_y);
private:
    int mainwindow_width;
    int mainwindow_height;
    int alert_width;
    int alert_height;
    //本次alert的x坐标
    int alert_x;
    //保额次alert的y坐标
    int alert_y;

    //alert message提示框
    AlertDialog *alertBG;
    //alert提示框timer
    QTimer *alertTimer;
    //alert提示框隐藏timer
    QTimer *alertDelayTimer;
    //alert提示框GOE
    QGraphicsOpacityEffect *alertGOE;
    //alert提示框透明度
    float ao;
    //alert提示框y坐标
    int ay;
private slots:
    //alert提示步处理
    void updateAlert();
    //隐藏alert提示框
    void hideAlert();
};

#endif // TOOLKITS_H
