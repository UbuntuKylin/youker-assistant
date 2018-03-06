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

#include "processworker.h"
#include "util.h"

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
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <systemd/sd-login.h>

using std::string;

ProcessWorker::UserMap ProcessWorker::users;
ProcessWorker::List ProcessWorker::all;
std::map<pid_t, guint64> ProcessWorker::cpu_times;

static bool init;
static bool is_running;


static size_t e_strftime(char *s, size_t max, const char *fmt, const struct tm *tm)
{
    char *c, *ffmt, *ff;
    size_t ret;

    ffmt = g_strdup(fmt);
    ff = ffmt;
    while ((c = strstr(ff, "%l")) != NULL) {
        c[1] = 'I';
        ff = c;
    }

    ff = ffmt;
    while ((c = strstr(ff, "%k")) != NULL) {
        c[1] = 'H';
        ff = c;
    }

    ret = strftime(s, max, ffmt, tm);
    g_free(ffmt);
    return ret;
}

static size_t e_strftime_fix_am_pm(char *s, size_t max, const char *fmt, const struct tm *tm)
{
    char buf[10];
    char *sp;
    char *ffmt;
    size_t ret;

    if (strstr(fmt, "%p")==NULL && strstr(fmt, "%P")==NULL) {
        /* No AM/PM involved - can use the fmt string directly */
        ret=e_strftime(s, max, fmt, tm);
    } else {
        /* Get the AM/PM symbol from the locale */
        e_strftime (buf, 10, "%p", tm);

        if (buf[0]) {
            /**
             * AM/PM have been defined in the locale
             * so we can use the fmt string directly
             **/
            ret=e_strftime(s, max, fmt, tm);
        } else {
            /**
             * No AM/PM defined by locale
             * must change to 24 hour clock
             **/
            ffmt=g_strdup(fmt);
            for (sp=ffmt; (sp=strstr(sp, "%l")); sp++) {
                /**
                 * Maybe this should be 'k', but I have never
                 * seen a 24 clock actually use that format
                 **/
                sp[1]='H';
            }
            for (sp=ffmt; (sp=strstr(sp, "%I")); sp++) {
                sp[1]='H';
            }
            ret=e_strftime(s, max, ffmt, tm);
            g_free(ffmt);
        }
    }
    return(ret);
}

static size_t e_utf8_strftime_fix_am_pm(char *s, size_t max, const char *fmt, const struct tm *tm)
{
    size_t sz, ret;
    char *locale_fmt, *buf;

    locale_fmt = g_locale_from_utf8(fmt, -1, NULL, &sz, NULL);
    if (!locale_fmt)
        return 0;

    ret = e_strftime_fix_am_pm(s, max, locale_fmt, tm);
    if (!ret) {
        g_free (locale_fmt);
        return 0;
    }

    buf = g_locale_to_utf8(s, ret, NULL, &sz, NULL);
    if (!buf) {
        g_free (locale_fmt);
        return 0;
    }

    if (sz >= max) {
        char *tmp = buf + max - 1;
        tmp = g_utf8_find_prev_char(buf, tmp);
        if (tmp)
            sz = tmp - buf;
        else
            sz = 0;
    }
    memcpy(s, buf, sz);
    s[sz] = '\0';
    g_free(locale_fmt);
    g_free(buf);
    return sz;
}

static char *format_start_datetime_for_display(time_t date)
{
    time_t nowdate = time(NULL);
    time_t yesdate;
    struct tm then, now, yesterday;
    char buf[26];
    gboolean done = FALSE;

    if (date == 0)
        return g_strdup ("?");

    localtime_r (&date, &then);
    localtime_r (&nowdate, &now);
    if (then.tm_mday == now.tm_mday &&
        then.tm_mon == now.tm_mon &&
        then.tm_year == now.tm_year) {
        e_utf8_strftime_fix_am_pm (buf, 26, _("Today %l:%M %p"), &then);
        done = TRUE;
    }
    if (!done) {
        yesdate = nowdate - 60 * 60 * 24;
        localtime_r (&yesdate, &yesterday);
        if (then.tm_mday == yesterday.tm_mday &&
            then.tm_mon == yesterday.tm_mon &&
            then.tm_year == yesterday.tm_year) {
            e_utf8_strftime_fix_am_pm (buf, 26, _("Yesterday %l:%M %p"), &then);
            done = TRUE;
        }
    }
    if (!done) {
        int i;
        for (i = 2; i < 7; i++) {
            yesdate = nowdate - 60 * 60 * 24 * i;
            localtime_r (&yesdate, &yesterday);
            if (then.tm_mday == yesterday.tm_mday &&
                then.tm_mon == yesterday.tm_mon &&
                then.tm_year == yesterday.tm_year) {
                e_utf8_strftime_fix_am_pm (buf, 26, _("%a %l:%M %p"), &then);
                done = TRUE;
                break;
            }
        }
    }
    if (!done) {
        if (then.tm_year == now.tm_year) {
            e_utf8_strftime_fix_am_pm (buf, 26, _("%b %d %l:%M %p"), &then);
        } else {
            e_utf8_strftime_fix_am_pm (buf, 26, _("%b %d %Y"), &then);
        }
    }

    return g_strdup (buf);
}

static void get_process_name (ProcessWorker *info, const gchar *cmd, const GStrv args)
{
    if (args) {
        // look for /usr/bin/very_long_name
        // and also /usr/bin/interpreter /usr/.../very_long_name
        // which may have use prctl to alter 'cmd' name
        for (int i = 0; i != 2 && args[i]; ++i) {
            char* basename;
            basename = g_path_get_basename(args[i]);

            if (g_str_has_prefix(basename, cmd)) {
                info->name = basename;
                return;
            }

            g_free(basename);
        }
    }

    info->name = g_strdup(cmd);
}

static void get_process_systemd_info(ProcessWorker *info)
{
//    uid_t uid;
    if (!init) {
        if (access("/run/systemd/seats/", F_OK) >= 0) {
            is_running = true;
        }
        init = true;
    }

    if (is_running) {
        free(info->unit);
        info->unit = NULL;
        sd_pid_get_unit(info->pid, &info->unit);

        free(info->session);
        info->session = NULL;
        sd_pid_get_session(info->pid, &info->session);

        free(info->seat);
        info->seat = NULL;

        if (info->session != NULL)
            sd_session_get_seat(info->session, &info->seat);

    //    if (sd_pid_get_owner_uid(info->pid, &uid) >= 0)
    //        info->owner = info->lookup_user(uid);
    //    else
    //        info->owner = "";
    }
}

ProcessWorker::ProcessWorker(pid_t pid, gint cpus, guint64 cpu_time)
    : tooltip(NULL),
      name(NULL),
      arguments(NULL),
//      security_context(NULL),
//      cgroup_name(NULL),
      unit(NULL),
      session(NULL),
      seat(NULL),
      pid(pid),
      uid(-1),
      mem(0UL),
      status(0U),
      pcpu(0U),
      nice(0),
      num_cpus(cpus),
      cpu_total_time(cpu_time),
      frequency(0U)
{
    this->setProcData();
}

ProcessWorker::~ProcessWorker()
{
    g_free(this->name);
    g_free(this->tooltip);
    g_free(this->arguments);
//    g_free(this->security_context);
//    g_free(this->cgroup_name);
    g_free(this->unit);
    g_free(this->session);
    g_free(this->seat);
}

void ProcessWorker::setProcData()
{
    //init
    ProcessWorker * const info = this;

    glibtop_proc_state procstate;
    glibtop_proc_time proctime;
    glibtop_proc_args procargs;
    gchar** args;

    glibtop_get_proc_state(&procstate, pid);
    glibtop_get_proc_time(&proctime, pid);
    args = glibtop_get_proc_argv(&procargs, pid, 0);

    get_process_name(info, procstate.cmd, static_cast<const GStrv>(args));

    std::string tooltip = make_string(g_strjoinv(" ", args));
    if (tooltip.empty())
        tooltip = procstate.cmd;
    info->tooltip = g_markup_escape_text(tooltip.c_str(), -1);
    info->arguments = g_strescape(tooltip.c_str(), "\\\"");
    g_strfreev(args);

    guint64 cpu_time = proctime.rtime;
    std::map<pid_t, guint64>::iterator it(ProcessWorker::cpu_times.find(pid));
    if (it != ProcessWorker::cpu_times.end())
    {
        if (proctime.rtime >= it->second)
            cpu_time = it->second;
    }
    info->cpu_time = cpu_time;
    info->start_time = proctime.start_time;

//    get_process_selinux_context (info);
//    info->cgroup_name = NULL;
//    get_process_cgroup_info(info);

    info->unit = info->session = info->seat = NULL;
    get_process_systemd_info(info);
}


ProcessWorker* ProcessWorker::find(pid_t pid)
{
    Iterator it(ProcessWorker::all.find(pid));
    return (it == ProcessWorker::all.end() ? NULL : it->second);
}

std::string ProcessWorker::lookup_user(guint uid)
{
    typedef std::pair<ProcessWorker::UserMap::iterator, bool> Pair;
    ProcessWorker::UserMap::value_type hint(uid, "");
    Pair p(ProcessWorker::users.insert(hint));
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

void ProcessWorker::set_user(guint uid)
{
    if (G_LIKELY(this->uid == uid))
        return;
    this->uid = uid;
    this->user = lookup_user(uid);
}
