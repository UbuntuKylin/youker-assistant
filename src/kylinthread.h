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

#ifndef KYLINTHREAD_H
#define KYLINTHREAD_H

#include <QThread>
class CleanerWidget;

class KylinThread : public QThread
{
    Q_OBJECT
public:
    KylinThread();
    ~KylinThread();
    virtual void run();
    void setCleanerWidget(CleanerWidget* widget) { parent_widget = widget; }

private:
    CleanerWidget *parent_widget;
};

#endif // KYLINTHREAD_H
