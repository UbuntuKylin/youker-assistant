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

#ifndef __FILELIST_H__
#define __FILELIST_H__

#include <glib.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"{
#endif

void filelist_init(GPtrArray**);
int  filelist_append(GPtrArray*, char * value);
int  filelist_length(GPtrArray*);
char * filelist_index(GPtrArray *filelist, int index);
void filelist_destroy(GPtrArray *filelist);

#ifdef __cplusplus
}
#endif

#endif
