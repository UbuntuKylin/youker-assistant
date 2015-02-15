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

#include <glib.h>
#include <iostream>
#include <map>

using std::string;

inline string make_string(char *c_str)
{
    if (!c_str) {
        return string();
    }
    string s(c_str);
    g_free(c_str);
    return s;
}

const char* format_process_state(guint state);
const gchar* get_nice_level (gint nice);

class ProcessInfo
{
    ProcessInfo& operator=(const ProcessInfo&);
    ProcessInfo(const ProcessInfo&);
    typedef std::map<guint, std::string> UserMap;
    static UserMap users;

  public:
    ProcessInfo(pid_t pid);
    ~ProcessInfo();
    typedef std::map<pid_t, ProcessInfo*> List;
    typedef List::iterator Iterator;
    static ProcessInfo* find(pid_t pid);
    static Iterator begin() { return ProcessInfo::all.begin(); }
    static Iterator end() { return ProcessInfo::all.end(); }
    static List all;

    void set_user(guint uid);
    std::string lookup_user(guint uid);
    std::string user;
    float mem;
    gulong start_time;
    guint64 cpu_time;
    guint status;
    guint pcpu;
    gint nice;
    gchar *tooltip;
    gchar *name;
    gchar *arguments;
    const guint pid;
    guint uid;
    static std::map<pid_t, guint64> cpu_times;
};
