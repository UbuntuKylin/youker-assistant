/*
 *
 * Copyright (C) 2008, 2009 Novell, Inc.
 * Copyright (C) 1999 Free Software Foundation, Inc.
 * Copyright (C) 2007, 2009 Vincent Untz.
 * Copyright (C) 2008 Lucas Rocha.
 * Copyright (C) 2008 William Jon McCann <jmccann@redhat.com>
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Authors:
 *  Vincent Untz <vuntz@gnome.org>
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 */

#include "util.h"

#include <QApplication>

#include <fstream>
#include <sstream>

std::string make_string(char *c_str)
{
    if (!c_str) {
        return string();
    }
    string s(c_str);
    g_free(c_str);
    return s;
}

gboolean get_boolean_from_desktop_file(GKeyFile *keyfile, const gchar *key, gboolean default_value)
{
    GError   *error;
    gboolean  retval;

    error = NULL;
    retval = g_key_file_get_boolean(keyfile, G_KEY_FILE_DESKTOP_GROUP, key, &error);
    if (error != NULL) {
        retval = default_value;
        g_error_free(error);
    }

    return retval;
}

gboolean write_contents_into_desktop_file(GKeyFile *keyfile, const gchar *path, GError **error)
{
    GError  *write_error;
    gchar   *data;
    gsize    length;
    gboolean res;

    g_return_val_if_fail(keyfile != NULL, FALSE);
    g_return_val_if_fail(path != NULL, FALSE);

    write_error = NULL;
    data = g_key_file_to_data(keyfile, &length, &write_error);

    if (write_error) {
        g_propagate_error(error, write_error);
        return FALSE;
    }

    res = g_file_set_contents(path, data, length, &write_error);
    g_free(data);

    if (write_error) {
        g_propagate_error (error, write_error);
        return FALSE;
    }

    return res;
}

void write_default_error_info_to_desktop_file(GKeyFile *keyfile)
{
    kylin_start_manager_key_file_set_string(keyfile, G_KEY_FILE_DESKTOP_KEY_TYPE, "Application");
    kylin_start_manager_key_file_set_string(keyfile, G_KEY_FILE_DESKTOP_KEY_EXEC, "/bin/false");
}

void set_locale_string_into_desktop_file(GKeyFile *keyfile, const gchar *key, const gchar *value)
{
    const char         *locale;
    const char * const *langs_pointer;
    int                 i;

    if (value == NULL) {
        value = "";
    }

    locale = NULL;
    langs_pointer = g_get_language_names ();
    for (i = 0; langs_pointer[i] != NULL; i++) {
        /* find first without encoding  */
        if (strchr (langs_pointer[i], '.') == NULL) {
            locale = langs_pointer[i];
            break;
        }
    }

    if (locale != NULL) {
        g_key_file_set_locale_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, key, locale, value);
    }
    else {
        g_key_file_set_string(keyfile, G_KEY_FILE_DESKTOP_GROUP, key, value);
    }
}

gboolean get_shown_from_desktop_file(GKeyFile *keyfile, const char *current_desktop)
{
    char     **only_show_in, **not_show_in;
    gboolean   found;
    int        i;

    if (!current_desktop)
        return TRUE;

    only_show_in = g_key_file_get_string_list(keyfile, G_KEY_FILE_DESKTOP_GROUP,
                                               G_KEY_FILE_DESKTOP_KEY_ONLY_SHOW_IN, NULL, NULL);

    if (only_show_in) {
        found = FALSE;
        for (i = 0; only_show_in[i] != NULL; i++) {
            if (g_strcmp0 (current_desktop, only_show_in[i]) == 0) {
                found = TRUE;
                break;
            }
        }

        g_strfreev (only_show_in);

        if (!found)
            return FALSE;
    }

    not_show_in = g_key_file_get_string_list(keyfile, G_KEY_FILE_DESKTOP_GROUP,
                                              G_KEY_FILE_DESKTOP_KEY_NOT_SHOW_IN, NULL, NULL);
    if (not_show_in) {
        found = FALSE;
        for (i = 0; not_show_in[i] != NULL; i++) {
            if (g_strcmp0 (current_desktop, not_show_in[i]) == 0) {
                found = TRUE;
                break;
            }
        }

        g_strfreev (not_show_in);

        if (found)
            return FALSE;
    }

    return TRUE;
}

char *get_current_desktop_env()
{
    static char *current_desktop = NULL;

    /* Support XDG_CURRENT_DESKTOP environment variable; this can be used
     * to abuse gnome-session in non-GNOME desktops. */
    if (!current_desktop) {
        const char *desktop;
        desktop = g_getenv("XDG_CURRENT_DESKTOP");

        /* Note: if XDG_CURRENT_DESKTOP is set but empty, do as if it
         * was not set */
        if (!desktop || desktop[0] == '\0')
            current_desktop = g_strdup ("GNOME");
        else
            current_desktop = g_strdup (desktop);
    }

    /* Using "*" means skipping desktop-related checks */
    if (g_strcmp0(current_desktop, "*") == 0)
        return NULL;

    return current_desktop;
}

gboolean is_str_equal(const char *a, const char *b)
{
    if (g_strcmp0 (a, b) == 0) {
        return TRUE;
    }

    if (a && !b && a[0] == '\0') {
        return TRUE;
    }

    if (b && !a && b[0] == '\0') {
        return TRUE;
    }

    return FALSE;
}
