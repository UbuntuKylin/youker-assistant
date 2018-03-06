#! /usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright (C) 2007-2011 Tualatrix Chou <tualatrix@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA

import logging

from . import ccm
import compizconfig

log = logging.getLogger('CompizSetting')

class CompizPlugin:
    context = compizconfig.Context()

    def __init__(self, name):
        self._plugin = self.context.Plugins[name]

    @classmethod
    def set_plugin_active(cls, name, active):
        try:
            plugin = cls.context.Plugins[name]
            plugin.Enabled = int(active)
            cls.context.Write()
        except:
            pass

    @classmethod
    def get_plugin_active(cls, name):
        try:
            plugin = cls.context.Plugins[name]
            return bool(plugin.Enabled)
        except:
            return False

    def set_enabled(self, bool):
        self._plugin.Enabled = int(bool)
        self.save()

    def get_enabled(self):
        return self._plugin.Enabled

    def save(self):
        self.context.Write()

    def resolve_conflict(self):
        conflicts = self.get_enabled() and self._plugin.DisableConflicts or \
                                           self._plugin.EnableConflicts
        conflict = ccm.PluginConflict(self._plugin, conflicts)
        return conflict.Resolve()

    @classmethod
    def is_available(cls, name, setting):
        return name in cls.context.Plugins and \
               setting in cls.context.Plugins[name].Screen

    def create_setting(self, key, target):
        settings = self._plugin.Screen

        if type(settings) == list:
            return settings[0][key]
        else:
            return settings[key]


class CompizSetting(object):
    def __init__(self, key, target=''):
        plugin_name, setting_name = key.split('.')
        self.key = key
        self._plugin = CompizPlugin(plugin_name)

        if not self._plugin.get_enabled():
            self._plugin.set_enabled(True)

        self._setting = self._plugin.create_setting(setting_name, target)

    def set_value(self, value):
        self._setting.Value = value
        self._plugin.save()

    def get_value(self):
        return self._setting.Value

    def is_default_and_enabled(self):
        return self._setting.Value == self._setting.DefaultValue and \
                self._plugin.get_enabled()

    def reset(self):
        self._setting.Reset()
        self._plugin.save()

    def resolve_conflict(self):
        return self._plugin.resolve_conflict()

    def get_schema_value(self):
        return self._setting.DefaultValue
