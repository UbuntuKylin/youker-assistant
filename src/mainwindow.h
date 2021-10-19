/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>
#include <QMenu>
#include <QGSettings>
#include <QList>
#include <QMap>
#include <QDir>

#include "kleftwidget.h"
#include "krightwidget.h"

class MainWindow : public QFrame
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUI();
    void initOpacityGSettings();
    void initConnections();

    void initLeftSideBar();
    void initRightPanel();

public slots:
    void handleMessage(const QString &);
    void onSwitchPage(int nIndex);
    void onMinimizeWindow();
    void onMaximizeWindow();
    void switchPage(int nIndex);

protected:
    void loadPlugins();
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    int panelIndex2ListIndex(int nPanelIndex);

private:
    KLeftWidget *m_leftWidget = nullptr;
    KRightWidget *m_rightWidget = nullptr;
    QPoint dragPosition;
    bool mousePressed = false;

    // layout
    QHBoxLayout *m_mainLayout = nullptr;

    // QGSettings
    QGSettings *m_gsTransOpacity = nullptr;
    qreal m_curTransOpacity = 1;

    // plugins
    QDir m_pluginsDir;
    QList<QObject *> m_pluginsList;
};
#endif // MAINWINDOW_H
