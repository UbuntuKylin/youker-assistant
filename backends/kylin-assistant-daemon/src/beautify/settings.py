#! /usr/bin/env python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
#
# Author:     Kobe Lee <xiangli@ubuntukylin.com>
# Maintainer: Ubuntu Kylin
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3, as published
# by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranties of
# MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
# PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.
### END LICENSE


from gi.repository import Gio as gio
import os, sys
import types
from .common import Schema

#http://lazka.github.io/pgi-docs/api/Gio_2.0/classes/Settings.html

class Settings:
    #db = None
    #BASE_KEY             = "org.gnome.gedit.preferences.encodings"
    def __init__(self, schema):
        self.db = gio.Settings.new(schema)

    #def open_settings_db(self):
    #    try:
    #        self.db = gio.Settings.new(self.BASE_KEY)
    #    except Exception as e:
    #        print e

    def get_value(self, key, type):
        try:
            setting_type = type
            get_func = {
                int:     self.db.get_int,
                bytes:  self.db.get_string,
                bool: self.db.get_boolean,
                list:    self.db.get_strv,
                dict:    self.db.get_string,
                type(None):    self.db.get_value,
            }[setting_type]
            return get_func(key)
        except Exception as e:
            print(e)
            return None

    def set_value(self, key, type, value):
        try:
            setting_type = type
            set_func = {
                int:     self.db.set_int,
                bytes:  self.db.set_string,
                bool: self.db.set_boolean,
                list:    self.db.set_strv,
                dict:    self.db.set_string,
                type(None):    self.db.set_value,
            }[setting_type]
            set_func(key, value)
        except Exception as e:
            print(e)

    def get_schema_value(self, schema, key):
        schema_default = Schema.load_schema(schema, key)
        if schema_default is not None:
            return schema_default
        else:
            raise NotImplemented

    # kobe: test notify func
#    def connect_notify(self):
#    #def connect_notify(self, func, data=None):
##        gs = gio.Settings("org.gnome.nautilus.desktop", None)
#        self.db.connect("changed::home-icon-visible", self.kobe_test)

#    def kobe_test(self, settings, key):
#        print "notify test success----------------------------"

if __name__ == '__main__':
    #list_on = ['GB18030', 'UTF-8', 'CURRENT', 'ISO-8859-15', 'UTF-16']
    #list_off = ['UTF-8', 'CURRENT', 'ISO-8859-15', 'UTF-16']
    settings = Settings("org.gnome.gedit.preferences.encodings")
    ##settings.open_settings_db()
    #value = settings.get_value("auto-detected", types.ListType)
    #print type(value)#<type 'list'>
    #print value
    #if value == list_off:
    #    settings.set_value("auto-detected", types.ListType, list_on)
    #else:
    #    settings.set_value("auto-detected", types.ListType, list_off)

    #settings = Settings("org.gnome.nautilus.preferences")
    #value = settings.get_value("always-use-location-entry", types.BooleanType)
    #settings = Settings("org.gnome.desktop.media-handling")
    #value = settings.get_value("automount", types.BooleanType)
    #print type(value)#<type 'list'>
    #print value

    default_value = settings.get_schema_value("org.gnome.gedit.preferences.encodings", "auto-detected")
    print("default_value->")
    print(default_value)



