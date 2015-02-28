/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef BOXWIDGET_H
#define BOXWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListView>
#include "../component/kylinlistmodel.h"

class SessionDispatcher;

class BoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoxWidget(QWidget *parent = 0, QString path = "");
    ~BoxWidget();
    void loadPlugins();
    void initPluginWidget();
    void setSessionDbusProxy(SessionDispatcher *dispatcher) { sessionProxy = dispatcher;}

signals:

public slots:
  void OnClickListView(const QModelIndex & index);
  void displayBoxHomePage();
  void displayBoxSubPage(QString plugin_id);

private:
    QListView *list_view;
    KylinListModel m_feture_Model;
    QString plugin_path;
    SessionDispatcher *sessionProxy;
};

#endif // BOXWIDGET_H
