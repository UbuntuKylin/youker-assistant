/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
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

#ifndef STARTUPTITLEWIDGET_H
#define STARTUPTITLEWIDGET_H

#include <QFrame>
#include <QTimer>

class QHBoxLayout;

class StartupTitleWidget : public QFrame
{
    Q_OBJECT
public:
    StartupTitleWidget(QWidget *parent);
    ~StartupTitleWidget();
    void initLeftContent();
    void initRightContent();
    void initWidgets();

public slots:
    void onMinBtnClicked();
    void onCloseBtnClicked();

//protected:
//    void paintEvent(QPaintEvent *e) override;

private:
//    QColor m_topBorderColor;
    QHBoxLayout *m_layout;
    QHBoxLayout *m_lLayout;
    QHBoxLayout *m_rLayout;
};

#endif // STARTUPTITLEWIDGET_H
