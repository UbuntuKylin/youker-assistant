/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef PROCAPP_H
#define PROCAPP_H

#include <glib.h>
#include <iostream>
#include <map>

using std::string;

class ProcApp {
public:
    GPtrArray * filelist;
    guint64 cpu_total_time;
    guint64 cpu_total_time_last;
    gint num_cpus;
};

#endif // PROCAPP_H
