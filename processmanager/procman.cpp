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

#include "procman.h"
#include "util.h"
#include "filelist.h"

#include <glibtop.h>
#include <glibtop/proclist.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gprintf.h>
#include <glibtop/procstate.h>
#include <glibtop/procmem.h>
#include <glibtop/procmap.h>
#include <glibtop/proctime.h>
#include <glibtop/procuid.h>
#include <glibtop/procargs.h>
#include <glibtop/prockernel.h>
#include <pwd.h>
#include <glibtop/mem.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

using std::string;

ProcessInfo::UserMap ProcessInfo::users;
ProcessInfo::List ProcessInfo::all;
std::map<pid_t, guint64> ProcessInfo::cpu_times;

ProcessInfo::ProcessInfo(pid_t pid)
    : tooltip(NULL),
      name(NULL),
      arguments(NULL),
      status(0),
      pid(pid),
      uid(-1)
{
    ProcessInfo * const info = this;
    glibtop_proc_state procstate;
    glibtop_proc_time proctime;
    glibtop_proc_args procargs;
    gchar** arguments;

    glibtop_get_proc_state (&procstate, pid);
    glibtop_get_proc_time (&proctime, pid);
    arguments = glibtop_get_proc_argv (&procargs, pid, 0);

    std::string tooltip = make_string(g_strjoinv(" ", arguments));
    if (tooltip.empty())
        tooltip = procstate.cmd;
    info->tooltip = g_markup_escape_text(tooltip.c_str(), -1);
    info->arguments = g_strescape(tooltip.c_str(), "\\\"");
    g_strfreev(arguments);

    guint64 cpu_time = proctime.rtime;
    std::map<pid_t, guint64>::iterator it(ProcessInfo::cpu_times.find(pid));
    if (it != ProcessInfo::cpu_times.end())
    {
        if (proctime.rtime >= it->second)
            cpu_time = it->second;
    }
    info->cpu_time = cpu_time;
    info->start_time = proctime.start_time;
}

ProcessInfo::~ProcessInfo()
{
    g_free(this->name);
    g_free(this->tooltip);
    g_free(this->arguments);
}

ProcessInfo* ProcessInfo::find(pid_t pid)
{
    Iterator it(ProcessInfo::all.find(pid));
    return (it == ProcessInfo::all.end() ? NULL : it->second);
}

std::string ProcessInfo::lookup_user(guint uid)
{
    typedef std::pair<ProcessInfo::UserMap::iterator, bool> Pair;
    ProcessInfo::UserMap::value_type hint(uid, "");
    Pair p(ProcessInfo::users.insert(hint));
    if (p.second) {
        struct passwd* pwd;
        pwd = getpwuid(uid);

        if (pwd && pwd->pw_name)
            p.first->second = pwd->pw_name;
        else {
            char username[16];
            g_sprintf(username, "%u", uid);
            p.first->second = username;
        }
    }
    return p.first->second;
}

void ProcessInfo::set_user(guint uid)
{
    if (G_LIKELY(this->uid == uid))
        return;
    this->uid = uid;
    this->user = lookup_user(uid);
}

static void update_info (ProcApp *app, ProcessInfo *info)
{
    glibtop_proc_state procstate;
    glibtop_proc_uid procuid;
    glibtop_proc_time proctime;
    glibtop_proc_args procargs;
    gchar** arguments;
    float memrate;
    glibtop_mem memory;
    glibtop_proc_mem procmem;
    glibtop_get_mem(&memory);
    glibtop_get_proc_mem(&procmem,info->pid);
    memrate = 100*(procmem.resident) /((memory.total)*1.0);
    info->mem = memrate;

    glibtop_get_proc_state (&procstate, info->pid);
    info->status = procstate.state;

    glibtop_get_proc_uid (&procuid, info->pid);
    glibtop_get_proc_time (&proctime, info->pid);

    arguments = glibtop_get_proc_argv (&procargs, info->pid, 0);
    std::string tooltip = make_string(g_strjoinv(" ", arguments));
    if (tooltip.empty())
        tooltip = procstate.cmd;
    g_strfreev(arguments);
    info->name = procstate.cmd;
    info->set_user(procstate.uid);

    guint64 difference = proctime.rtime - info->cpu_time;
    if (difference > 0)
        info->status = GLIBTOP_PROCESS_RUNNING;
    info->pcpu = difference * 100 / app->cpu_total_time;
    info->pcpu = MIN(info->pcpu, 100);

    ProcessInfo::cpu_times[info->pid] = info->cpu_time = proctime.rtime;
    info->nice = procuid.nice;

    gchar* str_command = g_strdup_printf("%s", g_strdup_printf("%s", info->arguments));
    gchar* str_user =  g_strdup_printf("%s", info->user.c_str());
    gchar* str_pid = g_strdup_printf("%s", g_strdup_printf("%d", info->pid));
    gchar* str_priority = g_strdup_printf("%s", g_strdup_printf("%s", get_nice_level(info->nice)));
    gchar* str_status =  g_strdup_printf("%s", g_strdup(format_process_state(info->status)));
    gchar* str_mem =  g_strdup_printf("%s",g_strdup_printf("%0.1f%%", info->mem));
    gchar* str_pcpu =  g_strdup_printf("%s",g_strdup_printf("%d%%", info->pcpu));
    gchar* str_cputime =  g_strdup_printf("%s",g_strdup_printf(ngettext("%lld second", "%lld seconds", info->cpu_time/HZ), (unsigned long long)info->cpu_time/HZ));
    gchar* str_starttime =  g_strdup_printf("%s",g_strdup_printf("%s", ctime((const time_t*)(&info->start_time))));
    str_starttime[strlen(str_starttime)-1] = 0;
    int info_size = 1024;
//    int info_size = strlen(str_name) + strlen(str_user) + strlen(str_uid) + strlen(str_status) + strlen(str_mem) + strlen(str_pcpu) + strlen(str_cputime) + strlen(str_starttime) + strlen(str_nice) + strlen(str_priority)  + strlen(str_pid) + strlen(str_command)  + strlen(str_wchan) + 1;
    char *pro_info;
    pro_info = (char*)calloc( info_size, sizeof(char));
    memset( pro_info, 0, info_size );
    if(!pro_info){
        perror("calloc");
    }
    snprintf( pro_info, info_size, "%s;%s;%s;%s;%s;%s;%s;%s;%s",  str_command, str_user, str_pid, str_priority, str_status, str_mem, str_pcpu, str_cputime, str_starttime);
    filelist_append(app->filelist, pro_info);
}

static void refresh_whose_processes_list (ProcApp *app, const pid_t* pid_list, const guint n)
{
    guint i;
    for(i = 0; i < n; ++i) {
        ProcessInfo *info = ProcessInfo::find(pid_list[i]);
        if (!info) {
            info = new ProcessInfo(pid_list[i]);
            ProcessInfo::all[info->pid] = info;
        }
        update_info (app, info);
    }
}

void list_whose_proc_info(ProcApp *app) {
    glibtop_init();

    pid_t* pid_list;
    glibtop_proclist proclist;
    glibtop_cpu cpu;
    gint which, arg;
    gint i;
    gint  whose_process;
    whose_process = 1;

    filelist_init(&app->filelist);

    app->num_cpus = 0;
    i=0;
    while (i < GLIBTOP_NCPU && cpu.xcpu_total[i] != 0) {
        app->num_cpus ++;
        i++;
    }
    if (app->num_cpus == 0) {
        app->num_cpus = 1;
    }

    switch (whose_process) {
        case 0://all processes
            which = GLIBTOP_KERN_PROC_ALL;
            arg = 0;
            break;
        case 2://active processes
            which = GLIBTOP_KERN_PROC_ALL | GLIBTOP_EXCLUDE_IDLE;
            arg = 0;
            break;
        default:
            which = GLIBTOP_KERN_PROC_UID;
            arg = getuid ();
            break;
    }

    pid_list = glibtop_get_proclist (&proclist, which, arg);
    glibtop_get_cpu (&cpu);
    app->cpu_total_time = MAX(cpu.total - app->cpu_total_time_last, 1);
    app->cpu_total_time_last = cpu.total;
    refresh_whose_processes_list (app, pid_list, proclist.number);

    g_free (pid_list);
    glibtop_close();
}
