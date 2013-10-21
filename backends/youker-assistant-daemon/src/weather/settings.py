#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2010 Sebastian MacDonald Sebas310@gmail.com
# Copyright (C) 2010 Mehdi Rejraji mehd36@gmail.com
# Copyright (C) 2011 Vadim Rutkovsky roignac@gmail.com
# Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd
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

try:
    from gi.repository import Gio
except ImportError:
    pass
import os, sys
import types

INFO_TYPE            = 'type'
INFO_SETTING         = 'setting'
class Settings:
    db = None
    BASE_KEY             = 'apps.indicators.chinaweather'
    REFRESH_RATE         = 'refresh_rate'
    CITY_KEY             = 'city_id'
    TEMPERATURE_KEY      = 'show_temperature'
    PLACES               = 'places'
    PLACECHOSEN          = 'placechosen'

    INFO = {
        REFRESH_RATE : {
            INFO_TYPE : types.IntType,
            INFO_SETTING : 'refresh-rate'
        },
        CITY_KEY : {
            INFO_TYPE : types.StringType,
            INFO_SETTING : 'city-id'
        },
        TEMPERATURE_KEY : {
            INFO_TYPE : types.BooleanType,
            INFO_SETTING : 'show-temperature'
        },
        PLACES : {
            INFO_TYPE : types.ListType,
            INFO_SETTING: 'places'
        },
        PLACECHOSEN : {
            INFO_TYPE : types.IntType,
            INFO_SETTING: 'placechosen'
        },
    }

    # Open the DB
    def prepare_settings_store(self):
        print "Settings: preparing settings store"
        try:
            self.db = Gio.Settings.new(self.BASE_KEY)
        except Exception as e:
            print "Settings: exception occurred while opening settings:\n %s" % str(e)

    def get_value(self, setting, return_id = False):
        setting_name = Settings.INFO[setting][INFO_SETTING]
        try:
            setting_type = Settings.INFO[setting][INFO_TYPE]
            get_func = {
                types.IntType:     self.db.get_int,
                types.StringType:  self.db.get_string,
                types.BooleanType: self.db.get_boolean,
                types.ListType:    self.db.get_string,
                types.DictType:    self.db.get_string,
                types.NoneType:    self.db.get_value,
            }[setting_type]
            return get_func(setting_name)
        except:
            print "Settings: can't find value for %s" % setting
            return None

    def set_value(self, setting, value):
        value = '' if value is None else value
        value = str(value) if type(value) is types.ListType else value
        #print "Settings: setting '%s'='%s'" % (setting, value)
        setting_name = Settings.INFO[setting][INFO_SETTING]
        try:
            setting_type = Settings.INFO[setting][INFO_TYPE]
            set_func = {
                types.IntType:     self.db.set_int,
                types.StringType:  self.db.set_string,
                types.BooleanType: self.db.set_boolean,
                types.ListType:    self.db.set_string,
                types.DictType:    self.db.set_string,
                types.NoneType:    self.db.set_value,
            }[setting_type]
            set_func(setting_name, value)
        except:
            print "Settings: schema for '%s' not found, aborting" % setting
