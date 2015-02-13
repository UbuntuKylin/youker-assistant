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

#include "filelist.h"
#include <stdio.h>
void filelist_init(GPtrArray **filelist)
{
	*filelist = g_ptr_array_new_full(100,  free);
	(*filelist)->len = 0;
}

int filelist_append(GPtrArray *filelist, char * value)
{
	g_ptr_array_add(filelist, (void*)value);
	return 0;
}

int filelist_length(GPtrArray *filelist)
{
	if( !filelist ){
		printf("it's NULL\n");
		return 0;
	}
	if(filelist->pdata == NULL)
		return 0;
	return filelist->len;
}

char * filelist_index(GPtrArray *filelist, int index)
{
	return (char*)g_ptr_array_index(filelist, index);
}

void filelist_destroy(GPtrArray *filelist)
{

	g_ptr_array_free(filelist, TRUE);
} 
