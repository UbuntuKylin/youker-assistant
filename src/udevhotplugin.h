/*
 * Copyright (C) 2013 ~ 2021 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Min Yang    yangmin@kylinos.cn
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

#pragma once

#include <QThread>
#include <libudev.h>
#include <sys/select.h>
#include <linux/types.h>
#include <linux/netlink.h>

class UDevHotPlugin : public QThread
{
    Q_OBJECT
public:
    explicit UDevHotPlugin(QObject * parent = nullptr);
    ~UDevHotPlugin(); 
    void stopDevHotPlugin();

signals:
    void sendUdevAddNotify(QString strUdevSubName, QString strUdevType);
    void sendUdevRemoveNotify(QString strUdevSubName, QString strUdevType);

protected:
    virtual void run() override;

private:
    struct udev* mpUdev;
    struct udev_monitor* mpUdevMonitor;
    bool mIsStop;
};