/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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

#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>
#include <QMap>
#include "weatherdb.h"
class QSettings;

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QSettings *mSettings = 0, QWidget *parent = 0);
    ~SelectDialog();
    void init_combobox_items();
    void update_city_list();
    void update_county_list();
    void showCityDialog();

private slots:
    void hide_select_dialog();
    void save_city_conf();
    void slotProvince();
    void slotCity();

    void changeSelectCity(QString currentName);
    void on_searchBtn_clicked();
    void on_quitButton_clicked();
    void on_okButton_clicked();

private:
    Ui::SelectDialog *ui;
    QSettings *pSettings;
    QPoint dragPos;
    WeatherDB *weatherdispather;

    //判断是否根据用户输入内容点击了查找按钮
    bool flag;
    //保存用户选中的城市名，方便没有点击确定按钮，重新输入城市名字后判断flag
    QString selectCity;
    QMap<QString, QVariant> yahooInfo;
    QMap<QString, QVariant> latInfo;
    QMap<QString, QVariant> lonInfo;

signals:
    void readyToUpdateWeatherForWizard();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // SELECTDIALOG_H
