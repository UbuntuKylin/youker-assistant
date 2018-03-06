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

import os
from .settings import Settings
import types

class GeditManager:
    def __init__(self):
        self.default = None
        self.settings = Settings("org.gnome.gedit.preferences.encodings")

    # -----------------默认值-----------------
    # Get Default Value
    def get_default_schema_value(self, schema, key):
        return self.settings.get_schema_value(schema, key)

    # Set Default Value
    def set_default_schema_value(self, schema, key, type):
        default_value = self.get_default_schema_value(schema, key)
        if default_value is not None:
            return self.settings.set_value(key, type, default_value)
        else:
            raise NotImplemented

    # 在Gedit中自动检测简体中文编码
    # on=['GB18030', 'UTF-8', 'CURRENT', 'ISO-8859-15', 'UTF-16']
    # off=['UTF-8', 'CURRENT', 'ISO-8859-15', 'UTF-16']
    # default = off
    # Get: Auto detect text encoding for Simplified Chinese in Gedit
    def get_detect_chinese_encoding(self):
        return self.settings.get_value("auto-detected", list)

    # Set: Auto detect text encoding for Simplified Chinese in Gedit
    def set_detect_chinese_encoding(self, flag):
        list_on = ['GB18030', 'UTF-8', 'CURRENT', 'ISO-8859-15', 'UTF-16']
        list_off = ['UTF-8', 'CURRENT', 'ISO-8859-15', 'UTF-16']
        if(flag):
            self.settings.set_value("auto-detected", list, list_off)
        else:
            self.settings.set_value("auto-detected", list, list_on)


    # Get Default Value: Auto detect text encoding for Simplified Chinese in Gedit
    #def get_default_detect_chinese_encoding(self):
    #    self.default = self.settings.get_schema_value("auto-detected")

    # Set Default Value: Auto detect text encoding for Simplified Chinese in Gedit
    #def set_default_detect_chinese_encoding(self):
    #    if self.default is not None:
    #        self.settings.set_value("auto-detected", types.ListType, self.default)


if __name__ == '__main__':
    gm = GeditManager()
    #aa = gm.get_detect_chinese_encoding()
    #print aa
    #list_on = ['GB18030', 'UTF-8', 'CURRENT', 'ISO-8859-15', 'UTF-16']
    #list_off = ['UTF-8', 'CURRENT', 'ISO-8859-15', 'UTF-16']
    #if aa == list_off:
    #    gm.set_detect_chinese_encoding(False)
    #else:
    #    gm.set_detect_chinese_encoding(True)


    #gm.get_default_detect_chinese_encoding()
    #print "default->"
    #print gm.default
    #gm.set_default_detect_chinese_encoding()

    #aa = gm.get_default_schema_value("org.gnome.gedit.preferences.encodings", "auto-detected")
    #print aa
    gm.set_default_schema_value("org.gnome.gedit.preferences.encodings", "auto-detected", list)
