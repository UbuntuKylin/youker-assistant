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

#pragma once

#include <glib.h>
#include <iostream>
#include <map>
#include <QString>
#include <QObject>

using std::string;

#define KEY_FILE_DESKTOP_GROUP "Desktop Entry"
#define KEY_FILE_DESKTOP_KEY_HIDDEN "Hidden"
#define KEY_FILE_DESKTOP_KEY_NO_DISPLAY "NoDisplay"
#define KEY_FILE_DESKTOP_KEY_ONLY_SHOW_IN "OnlyShowIn"
#define KEY_FILE_DESKTOP_KEY_NOT_SHOW_IN "NotShowIn"
#define KEY_FILE_DESKTOP_KEY_AUTOSTART_ENABLED "X-GNOME-Autostart-enabled"
#define KEY_FILE_DESKTOP_KEY_NAME "Name"
#define KEY_FILE_DESKTOP_KEY_EXEC "Exec"
#define KEY_FILE_DESKTOP_KEY_TRY_EXEC "TryExec"
#define KEY_FILE_DESKTOP_KEY_COMMENT "Comment"
#define KEY_FILE_DESKTOP_KEY_ICON "Icon"
#define KEY_FILE_DESKTOP_KEY_TYPE "Type"
#define KEY_FILE_DESKTOP_TYPE_APPLICATION "Application"
#define KEY_FILE_DESKTOP_TYPE_LINK "Link"
#define KEY_FILE_DESKTOP_KEY_URL "URL"
#define KEY_FILE_DESKTOP_KEY_STARTUP_NOTIFY "StartupNotify"
#define KEY_FILE_DESKTOP_KEY_CATEGORIES "Categories"
#define KEY_FILE_DESKTOP_KEY_MIME_TYPE "MimeType"
#define KEY_FILE_DESKTOP_KEY_TERMINAL "Terminal"
#define KEY_FILE_DESKTOP_TYPE_DIRECTORY "Directory"

#define SAVE_MASK_HIDDEN     0x0001
#define SAVE_MASK_ENABLED    0x0002
#define SAVE_MASK_NAME       0x0004
#define SAVE_MASK_EXEC       0x0008
#define SAVE_MASK_COMMENT    0x0010
#define SAVE_MASK_NO_DISPLAY 0x0020
#define SAVE_MASK_ALL        0xffff

#define kylin_start_manager_key_file_get_string(key_file, key) \
    g_key_file_get_string(key_file, G_KEY_FILE_DESKTOP_GROUP, key, NULL)
#define kylin_start_manager_key_file_get_locale_string(key_file, key) \
    g_key_file_get_locale_string(key_file, G_KEY_FILE_DESKTOP_GROUP, key, NULL, NULL)
#define kylin_start_manager_key_file_set_boolean(key_file, key, value) \
    g_key_file_set_boolean(key_file, G_KEY_FILE_DESKTOP_GROUP, key, value)
#define kylin_start_manager_key_file_set_string(key_file, key, value) \
    g_key_file_set_string(key_file, G_KEY_FILE_DESKTOP_GROUP, key, value)

std::string make_string(char *c_str);
gboolean get_boolean_from_desktop_file(GKeyFile *keyfile, const gchar *key, gboolean default_value);
gboolean write_contents_into_desktop_file (GKeyFile *keyfile, const gchar *path, GError **error);
void write_default_error_info_to_desktop_file(GKeyFile *keyfile);
void set_locale_string_into_desktop_file(GKeyFile *keyfile, const gchar *key, const gchar *value);
gboolean get_shown_from_desktop_file(GKeyFile *keyfile, const char *current_desktop);
char *get_current_desktop_env();
gboolean is_str_equal(const char *a, const char *b);
