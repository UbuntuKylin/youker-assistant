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

#include <QDebug>
#include <errno.h>
#include <sys/time.h>
#include "udevhotplugin.h"

UDevHotPlugin::UDevHotPlugin(QObject *parent)
    : QThread(parent)
{
    mIsStop = false;
    mpUdev = udev_new();
    if (mpUdev) {
        mpUdevMonitor = udev_monitor_new_from_netlink(mpUdev, "udev");
        if (!mpUdevMonitor) {
            qWarning()<<"udev_monitor_new_from_netlink udev failed!!";
        }
        else {
            //if (udev_monitor_filter_add_match_subsystem_devtype(mpUdevMonitor, "usb", "usb_device")) {
            //    qWarning()<<"add_match_subsystem_devtype failed!!";
            //}
            if (udev_monitor_enable_receiving(mpUdevMonitor)) {
                qWarning()<<"start udev monitor failed!!";
            }
        }
    }
    else {
        qWarning()<<"udev_new failed!!";
    }
}

UDevHotPlugin::~UDevHotPlugin()
{
    if (mpUdevMonitor) {
        udev_monitor_unref(mpUdevMonitor);
    }
    if (mpUdev) {
        udev_unref(mpUdev);
    }
}

#if 0
static void print_device(struct udev_device *device, const char *source, int env)
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
 
	qDebug()<<QString().sprintf("%-6s[%llu.%06u] %-8s %s (%s)\n",
	       source,
	       (unsigned long long) tv.tv_sec, (unsigned int) tv.tv_usec,
	       udev_device_get_action(device),
	       udev_device_get_devpath(device),
	       udev_device_get_subsystem(device));
 
	if (env) {
		struct udev_list_entry *list_entry;
		udev_list_entry_foreach(list_entry, udev_device_get_properties_list_entry(device))
		qDebug()<<QString().sprintf("%s=%s\n",
			       udev_list_entry_get_name(list_entry),
			       udev_list_entry_get_value(list_entry));
	} 
}
#endif

void UDevHotPlugin::run()
{
	fd_set readfds;
    int fdcount;
    while(!mIsStop) {
        FD_ZERO(&readfds);
        if (mpUdevMonitor) {
            timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = 200000;
            FD_SET(udev_monitor_get_fd(mpUdevMonitor), &readfds);
            fdcount = select(udev_monitor_get_fd(mpUdevMonitor)+1, &readfds, NULL, NULL, &timeout);
            if (fdcount < 0) {
                if (errno != EINTR)
                    qWarning()<<QString().sprintf("error receiving uevent message: %m\n");
                return;
            }
            if (FD_ISSET(udev_monitor_get_fd(mpUdevMonitor), &readfds)) {
                struct udev_device *device;
                device = udev_monitor_receive_device(mpUdevMonitor);
                if (!device)
                    return;
                //print_device(device, "UEVENT", 1);
                const char* udev_action = udev_device_get_action(device);
                const char* udev_type = udev_device_get_devtype(device);
                const char* udev_subsysname = udev_device_get_subsystem(device);
                if (strcmp(udev_action,"add") == 0) {
                    emit sendUdevAddNotify(QString(udev_subsysname), QString(udev_type));
                }
                else if (strcmp(udev_action,"remove") == 0) {
                    emit sendUdevRemoveNotify(QString(udev_subsysname), QString(udev_type));
                }
                udev_device_unref(device);
            }
        }
        else {
            msleep(200);
        }
    }    
}

void UDevHotPlugin::stopDevHotPlugin()
{
    mIsStop = true;
}