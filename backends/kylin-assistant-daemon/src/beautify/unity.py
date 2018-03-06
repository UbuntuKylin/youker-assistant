#!/usr/bin/python3
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

import os
from . import gsettings
#from .compizsettings import CompizSetting

class Unity:
    '''if compiz: key is icon_size; else if gsettins: key is icon-size'''
    desktop = None

    def __init__(self):
        self.desktop = os.getenv('XDG_CURRENT_DESKTOP')
        if self.desktop is None:
             self.desktop = os.getenv('XDG_SESSION_DESKTOP')
    #    self.setting = CompizSetting("%s.%s" % (name, key))

    # ---------------launcher---------------
    # -----------------默认值-----------------
    # Get Default Value
    #def get_default_schema_value(self, name, key):
    #    compizsetting = CompizSetting("%s.%s" % (name, key))
    #    return compizsetting.get_schema_value()

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
        try:
            value = gsettings.get('org.compiz.unityshell',
                '/org/compiz/profiles/unity/plugins/unityshell/',
                'launcher-hide-mode', 'int')
            if value == 0:
                return False
            elif value == 1:
                return True
            else:
                return None
        except Exception as e:
            return False

    # launcher icon size 32-64
    def set_launcher_icon_size(self, size):
        return gsettings.set('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'icon-size',
            'int', size)

    # get launcher icon size
    def get_launcher_icon_size(self):
        try:
            return gsettings.get('org.compiz.unityshell',
                '/org/compiz/profiles/unity/plugins/unityshell/',
                'icon-size', 'int')
        except Exception as e:
            return 0

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

    def get_default_launcher_have_showdesktopicon(self):
        return self.get_launcher_have_showdesktopicon()

    def set_default_launcher_have_showdesktopicon(self):
        self.set_launcher_have_showdesktopicon(True)



    #add by kobe
    # 透明度
    def get_launcher_transparency(self):
        try:
            return gsettings.get('org.compiz.unityshell',
                '/org/compiz/profiles/unity/plugins/unityshell/',
                'launcher-opacity', 'double')
        except Exception as e:
            return 0.0

    # 'min'    : 0.2, # TODO : Check these min max. Most prolly wrong.
    # 'max'    : 1.0, # But fine since they are ignored anyway.
    # 'ticks'  : [(0.666, Gtk.PositionType.BOTTOM, None)]
    def set_launcher_transparency(self, opacity):
        return gsettings.set('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'launcher-opacity',
            'double', opacity)

    # 图标背景
    def get_all_launcher_icon_colourings(self):
#        return ['0:0', '1:1', '2:2', '3:3', '4:4']
        return ['all programs', 'only run app', 'no coloring', 'edge coloring', 'each workspace alternating coloring']

    def get_launcher_icon_colouring(self):
        try:
            return gsettings.get('org.compiz.unityshell',
                '/org/compiz/profiles/unity/plugins/unityshell/',
                'backlight-mode', 'int')
        except Exception as e:
            return 0

    # 'map'       : {0:0,1:1,2:2,3:3,4:4}  0:所有程序，1:仅打开的应用程序，2:不着色，3:边缘着色，4:每个工作区交替着色
    def set_launcher_icon_colouring(self, colouring):
        return gsettings.set('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'backlight-mode',
            'int', colouring)

    def get_all_launcher_position(self):
        return ['Left', 'Bottom']

    def get_current_launcher_position(self):
        return gsettings.get('com.canonical.Unity.Launcher',
            None,
            'launcher-position',
            'string')

    def set_launcher_position(self, position):
        return gsettings.set('com.canonical.Unity.Launcher',
            None,
            'launcher-position',
            'string', position)

    #Dash背景模糊类型
    def get_dash_blur_experimental(self):
        try:
            return gsettings.get('org.compiz.unityshell',
                '/org/compiz/profiles/unity/plugins/unityshell/',
                'dash-blur-experimental', 'int')
        except Exception as e:
            return 0

    # 活动模糊smart: 2   静态模糊static:1   非模糊0
    def set_dash_blur_experimental(self, blur):
        return gsettings.set('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'dash-blur-experimental',
            'int', blur)

    #面板菜单透明度
    def get_panel_transparency(self):
        try:
            return gsettings.get('org.compiz.unityshell',
                '/org/compiz/profiles/unity/plugins/unityshell/',
                'panel-opacity', 'double')
        except Exception as e:
            return 0.0

    # 'min'    : 0.2, # TODO : Check these min max. Most prolly wrong.
    # 'max'    : 8.0, # But fine since they are ignored anyway.
    # 'ticks'  : [(0.666, Gtk.PositionType.BOTTOM, None)]
    def set_panel_transparency(self, opacity):
        return gsettings.set('org.compiz.unityshell',
            '/org/compiz/profiles/unity/plugins/unityshell/',
            'panel-opacity',
            'double', opacity)

    #日期时间格式
    def get_all_time_format(self):
        return ['locale-default', '12-hour' , '24-hour', 'custom']

    def get_time_format(self):
#        if self.desktop == "mate":
#            return gsettings.get('org.mate.panel',
#                '/org/mate/panel/objects/clock/prefs/',
#                'format',
#                'string')
#        else:
        return gsettings.get('com.canonical.indicator.datetime',
            None,
            'time-format',
            'string')

    def set_time_format(self, format):
#        if self.desktop == "mate":
#            return gsettings.set('org.mate.panel',
#                '/org/mate/panel/objects/clock/prefs/',
#                'format',
#                'string', format)
#        else:
        return gsettings.set('com.canonical.indicator.datetime',
            None,
            'time-format',
            'string', format)
    # 秒
    def get_show_seconds(self):
        return gsettings.get('com.canonical.indicator.datetime',
            None,
            'show-seconds',
            'boolean')

    def set_show_seconds(self, flag):
        return gsettings.set('com.canonical.indicator.datetime',
            None,
            'show-seconds',
            'boolean', flag)

    #星期
    def get_show_week(self):
        return gsettings.get('com.canonical.indicator.datetime',
            None,
            'show-day',
            'boolean')

    def set_show_week(self, flag):
        return gsettings.set('com.canonical.indicator.datetime',
            None,
            'show-day',
            'boolean', flag)

    #日期
    def get_show_date(self):
        return gsettings.get('com.canonical.indicator.datetime',
            None,
            'show-date',
            'boolean')

    def set_show_date(self, flag):
        return gsettings.set('com.canonical.indicator.datetime',
            None,
            'show-date',
            'boolean', flag)

    # 电源
    # present:电源总是可见     charge:当机器充电/放电时可见         never:总是不可见
    def get_all_power_icon_policy(self):
        return ['present', 'charge', 'never']

    def get_power_icon_policy(self):
        return gsettings.get('com.canonical.indicator.power',
            None,
            'icon-policy',
            'string')

    def set_power_icon_policy(self, flag):
        return gsettings.set('com.canonical.indicator.power',
            None,
            'icon-policy',
            'string', flag)

    #电源时间
    def get_show_power_time(self):
        return gsettings.get('com.canonical.indicator.power',
            None,
            'show-time',
            'boolean')

    def set_show_power_time(self, flag):
        return gsettings.set('com.canonical.indicator.power',
            None,
            'show-time',
            'boolean', flag)

    #电源百分比
    def get_show_power_percentage(self):
        return gsettings.get('com.canonical.indicator.power',
            None,
            'show-percentage',
            'boolean')

    def set_show_power_percentage(self, flag):
        return gsettings.set('com.canonical.indicator.power',
            None,
            'show-percentage',
            'boolean', flag)

    #-----------------mate----------------------------
    def set_mate_panel_icon_size(self, position, size):
        if position == "top":
            return gsettings.set('org.mate.panel.toplevel',
                '/org/mate/panel/toplevels/top/',
                'size',
                'int', size)
        elif position == "bottom":
            return gsettings.set('org.mate.panel.toplevel',
                '/org/mate/panel/toplevels/bottom/',
                'size',
                'int', size)
        else:
            return False

    # get launcher icon size
    def get_mate_panel_icon_size(self, position):
        if position == "top":
            return gsettings.get('org.mate.panel.toplevel',
                '/org/mate/panel/toplevels/top/',
                'size', 'int')
        elif position == "bottom":
            return gsettings.get('org.mate.panel.toplevel',
                '/org/mate/panel/toplevels/bottom/',
                'size', 'int')
        else:
            return False

    def set_mate_panel_autohide(self, position, flag):
        if position == "top":
            return gsettings.set('org.mate.panel.toplevel',
                '/org/mate/panel/toplevels/top/',
                'auto-hide',
                'boolean', flag)
        elif position == "bottom":
            return gsettings.set('org.mate.panel.toplevel',
                '/org/mate/panel/toplevels/bottom/',
                'auto-hide',
                'boolean', flag)
        else:
            return False

    def get_mate_panel_autohide(self, position):
        if position == "top":
            return gsettings.get('org.mate.panel.toplevel',
                '/org/mate/panel/toplevels/top/',
                'auto-hide', 'boolean')
        elif position == "bottom":
            return gsettings.get('org.mate.panel.toplevel',
                '/org/mate/panel/toplevels/bottom/',
                'auto-hide', 'boolean')
        else:
            return False

    def get_show_apps(self):
        return gsettings.get('org.mate.panel.menubar',
            None,
            'show-applications',
            'boolean')

    def set_show_apps(self, flag):
        return gsettings.set('org.mate.panel.menubar',
            None,
            'show-applications',
            'boolean', flag)

    def get_show_desktop(self):
        return gsettings.get('org.mate.panel.menubar',
            None,
            'show-desktop',
            'boolean')

    def set_show_desktop(self, flag):
        return gsettings.set('org.mate.panel.menubar',
            None,
            'show-desktop',
            'boolean', flag)

    def get_show_icon(self):
        return gsettings.get('org.mate.panel.menubar',
            None,
            'show-icon',
            'boolean')

    def set_show_icon(self, flag):
        return gsettings.set('org.mate.panel.menubar',
            None,
            'show-icon',
            'boolean', flag)

    def get_show_places(self):
        return gsettings.get('org.mate.panel.menubar',
            None,
            'show-places',
            'boolean')

    def set_show_places(self, flag):
        return gsettings.set('org.mate.panel.menubar',
            None,
            'show-places',
            'boolean', flag)

if __name__ == '__main__':
    uuu = Unity()
#    print uuu.get_launcher_icon_colouring()
#    print uuu.set_launcher_icon_colouring(1)
    print(uuu.get_time_format())
#    bb = uuu.get_default_schema_value("unityshell", "icon_size")
#    aa = uuu.get_default_schema_value("unityshell", "launcher_hide_mode")
    #aa = uuu.get_default_schema_value('org.gnome.desktop.media-handling', 'automount')
    #uuu = Unity("unityshell", "icon_size")
    #aa = uuu.get_launcher_icon_size_test()
    #print "bb->"
    #print bb
    #print "aa->"
    #print aa
    #uuu.set_default_schema_value('icon-size', 'int', bb)
#    cc = uuu.get_default_launcher_have_showdesktopicon()
#    print cc

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
