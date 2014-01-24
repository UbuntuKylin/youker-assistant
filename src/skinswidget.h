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

#ifndef SKINSWIDGET_H
#define SKINSWIDGET_H

#include <QWidget>
#include <QtGui>
#include "skingrid.h"
class QSettings;
class SkinsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SkinsWidget(QSettings *mSettings = 0, QWidget *parent = 0);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
//    void resizeEvent(QResizeEvent *event);

signals:
    void skinSignalToQML(QString skinName);

private slots:
    void showSkin(QString page_count);
    void verifyToUseSkin(QString skinName);

private:
    void initTitleBar();//标题栏
    void initSkinsCenter();//皮肤列表区域
    void initBottomBar();//上一页下一页按钮区域
    QSettings *pSettings;
    QString skinName;
    bool is_change;
    QStringList skin_list;
    QStringList tip_list;

    QHBoxLayout *titleLayout;
    QGridLayout *centerLayout;
    QHBoxLayout *bottomLayout;

    QPoint move_point;
    bool mouse_press;
    QLabel *title_label;
    QLabel *title_icon_label;
    QLabel *close_button;
    int page_count;
    int page_count_point;
    int current_page;

//    SkinGrid *change_skin_widget_0;
//    SkinGrid *change_skin_widget_1;
//    SkinGrid *change_skin_widget_2;
//    SkinGrid *change_skin_widget_3;
//    SkinGrid *change_skin_widget_4;
//    SkinGrid *change_skin_widget_5;
//    SkinGrid *change_skin_widget_6;
//    SkinGrid *change_skin_widget_7;

    QPushButton *first_page_button;
    QPushButton *previous_page_button;
    QPushButton *next_page_button;
    QPushButton *last_page_button;
    QList<SkinGrid *> change_skin_list;

//    QImage wheel;
    
};

#endif // SKINSWIDGET_H
