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

#include <glib/gi18n.h>
#include <glib.h>
#include <glibtop/procstate.h>
#include "util.h"

const char* format_process_state(guint state)
{
    const char *status;

    switch (state)
    {
        case GLIBTOP_PROCESS_RUNNING:
            status = _("Running");
            break;

        case GLIBTOP_PROCESS_STOPPED:
            status = _("Stopped");
            break;

        case GLIBTOP_PROCESS_ZOMBIE:
            status = _("Zombie");
            break;

        case GLIBTOP_PROCESS_UNINTERRUPTIBLE:
            status = _("Uninterruptible");
            break;

        default:
            status = _("Sleeping");
            break;
    }

    return status;
}

const gchar* get_nice_level (gint nice)
{
    if (nice < -7)
        return _("Very High");
    else if (nice < -2)
        return _("High");
    else if (nice < 3)
        return _("Normal");
    else if (nice < 7)
        return _("Low");
    else
        return _("Very Low");
}
