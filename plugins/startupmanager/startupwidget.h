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

#ifndef STARTUPWIDGET_H
#define STARTUPWIDGET_H


#include <QFrame>
#include <QStackedWidget>
#include <QLabel>

class QVBoxLayout;
class StartupListWidget;
class StartupTitleWidget;

class StartupWidget : public QFrame
{
    Q_OBJECT

public:
    StartupWidget(QWidget *parent = 0);
    ~StartupWidget();

    void moveCenter();

protected:
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    StartupTitleWidget *m_titleWidget = nullptr;
    StartupListWidget *m_startupView = nullptr;
    QVBoxLayout *m_layout = nullptr;
    QPoint dragPosition;
    bool mousePressed;
};

#endif // STARTUPWIDGET_H
