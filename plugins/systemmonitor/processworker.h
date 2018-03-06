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


#ifndef PROCESSWORKER_H
#define PROCESSWORKER_H

#include <glib.h>
#include <iostream>
#include <map>
#include <QString>
#include <QPainter>

using std::string;

class ProcessWorker
{
    ProcessWorker& operator=(const ProcessWorker&);
    ProcessWorker(const ProcessWorker&);
    typedef std::map<guint, std::string> UserMap;
    static UserMap users;

  public:
    ProcessWorker(pid_t pid, gint cpus, guint64 cpu_time);
    ~ProcessWorker();
    typedef std::map<pid_t, ProcessWorker*> List;
    typedef List::iterator Iterator;
    static ProcessWorker* find(pid_t pid);
    static Iterator begin() { return ProcessWorker::all.begin(); }
    static Iterator end() { return ProcessWorker::all.end(); }
    static List all;
    void setProcData();
    void set_user(guint uid);
    std::string lookup_user(guint uid);


    std::string user;
    gulong mem;
    gulong start_time;
    guint64 cpu_time;
    guint status;
    guint pcpu;
    gint nice;
    gchar *tooltip;
    gchar *name;
    gchar *arguments;
    const pid_t pid;
    guint uid;
    static std::map<pid_t, guint64> cpu_times;
    gchar *unit;
    gchar *session;
    gchar *seat;
//    gchar *security_context;
//    gchar *cgroup_name;
    gint num_cpus;
    guint64 cpu_total_time;
    unsigned frequency;
};

#endif // PROCESSWORKER_H
