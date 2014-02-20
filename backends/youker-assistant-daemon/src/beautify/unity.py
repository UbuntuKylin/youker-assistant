#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE

# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
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

import gsettings
from compizsettings import CompizSetting

class Unity:
    '''if compiz: key is icon_size; else if gsettins: key is icon-size'''

    #def __init__(self, name, key):
    #    self.setting = CompizSetting("%s.%s" % (name, key))

    # ---------------launcher---------------
    # -----------------默认值-----------------
    # Get Default Value
    def get_default_schema_value(self, name, key):
        compizsetting = CompizSetting("%s.%s" % (name, key))
        return compizsetting.get_schema_value()

    # Set Default Value  min=32, max=64, step=16, key="unityshell.icon_size"
    #def set_default_schema_value(self, key, name, type, value):
    def set_default_schema_value(self, key, type, value):
        #default_value = self.get_default_schema_value(name, key)
        #if default_value is not None:
        return gsettings.set('org.compiz.unityshell',
                            '/org/compiz/profiles/unity/plugins/unityshell/',
                            key, type, value)
        #else:
        #    raise NotImplemented

    # launcher auto hide mode, True/False
    def set_launcher_autohide(self, flag):
        return gsettings.set('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'launcher-hide-mode',
            'int', flag)

    # get launcher auto hide mode
    def get_launcher_autohide(self):
        value = gsettings.get('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'launcher-hide-mode', 'int')
        if value == 0:
            return False
        elif value == 1:
            return True
        else:
            return None

    # launcher icon size 32-64
    def set_launcher_icon_size(self, size):
        return gsettings.set('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'icon-size',
            'int', size)

    # get launcher icon size
    def get_launcher_icon_size(self):
        return gsettings.get('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'icon-size', 'int')

    # launcher 'show desktop' icon True/False
    def set_launcher_have_showdesktopicon(self, flag):
        launcher = gsettings.get_schema('com.canonical.Unity.Launcher')
        icons = launcher.get_strv('favorites')
        desktop = 'unity://desktop-icon'
        if flag == True:
            if desktop not in icons:
                icons.append(desktop)
                launcher.set_strv('favorites', icons)
        else:
            if desktop in icons:
                icons.remove(desktop)
                launcher.set_strv('favorites', icons)

    # get is launcher have 'show desktop' icon
    def get_launcher_have_showdesktopicon(self):
        launcher = gsettings.get_schema('com.canonical.Unity.Launcher')
        icons = launcher.get_strv('favorites')
        desktop = 'unity://desktop-icon'
        if desktop in icons:
            return True
        else:
            return False

if __name__ == '__main__':
    uuu = Unity()
    bb = uuu.get_default_schema_value("unityshell", "icon_size")
    aa = uuu.get_default_schema_value("unityshell", "launcher_hide_mode")
    #aa = uuu.get_default_schema_value('org.gnome.desktop.media-handling', 'automount')
    #uuu = Unity("unityshell", "icon_size")
    #aa = uuu.get_launcher_icon_size_test()
    print "bb->"
    print bb
    print "aa->"
    print aa
    uuu.set_default_schema_value('icon-size', 'int', bb)

    #uuu.set_default_schema_value('launcher-hide-mode', 'int', aa)

    #bb = uuu.get_default_launcher_icon_size()
    #print "bb->"
    #print bb
    #print(type(bb))
    #uuu.reset_default_launcher_icon_size(bb)
    #uuu.set_launcher_icon_size(48)
    # print uuu.get_launcher_icon_size()
    # print uuu.get_launcher_have_showdesktopicon()
    # uuu.set_launcher_autohide(0)
    # print uuu.get_launcher_autohide()
    # uuu.set_launcher_have_showdesktopicon(True)
    # uuu.set_launcher_icon_size(48)
