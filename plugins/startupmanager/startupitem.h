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

#ifndef STARTUPITEM_H
#define STARTUPITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidgetItem>

class MySwitcher;
class StartupData;

class StartupItem : public QWidget
{
    Q_OBJECT

public:
    StartupItem(StartupData info, QWidget *parent=0);

    QListWidgetItem* getItem();
    QString getAppName();
    void setAppName(const QString &name);

    void setItemHovered();
    void unsetItemHovered();
    void setSwitcherOn(const bool b);

signals:
    void changeStartup(const QString &exec, const bool active);
    void enter();

protected:
    void enterEvent(QEvent *event);
    void paintEvent(QPaintEvent *);

private:
    bool isEntered;
    QListWidgetItem *item = nullptr;
    QString m_appName;

    QLabel *m_appIcon = nullptr;
    QLabel *m_appNameLabel = nullptr;
    QLabel *m_appDescLabel = nullptr;
    MySwitcher *switcher = nullptr;
    QWidget *m_labelWidget = nullptr;

    QHBoxLayout *m_switchLayout = nullptr;
    QVBoxLayout *m_labelLayout = nullptr;
    QHBoxLayout *m_leftLayout = nullptr;
    QHBoxLayout *m_layout = nullptr;
};

#endif // STARTUPITEM_H
