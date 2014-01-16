/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LOCATIONDIALOG_H
#define LOCATIONDIALOG_H

#include <QDialog>
#include <QMap>
#include "sessiondispatcher.h"

namespace Ui {
class LocationDialog;
}

class LocationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LocationDialog(QWidget *parent = 0);
    ~LocationDialog();
    QStringList list_city_names(QString inputText);
    
private slots:
    void on_searchBtn_clicked();
    void on_quitBtn_clicked();
    void on_okBtn_clicked();
    void changeSelectCity(QString currentName);

private:
    Ui::LocationDialog *ui;
    QMap<QString, QVariant> cityInfo;
    QPoint dragPos;
    //判断是否根据用户输入内容点击了查找按钮
    bool flag;
    //保存用户选中的城市名，方便没有点击确定按钮，重新输入城市名字后判断flag
    QString selectCity;
    SessionDispatcher *sedispather;
//    QStringList geonameidList;
    QMap<QString, QVariant> yahooInfo;
    QMap<QString, QVariant> latInfo;
    QMap<QString, QVariant> lonInfo;
    bool yahoo;

signals:
    void sendCityInfo(QString cityName, QString cityId, QString lat, QString lon);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // LOCATIONDIALOG_H
