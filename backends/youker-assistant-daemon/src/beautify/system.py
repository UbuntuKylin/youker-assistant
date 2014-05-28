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

class System():
    def __init__(self, sysdaemon):
        self.sysdaemon = sysdaemon

    # -----------------默认值-----------------
    # Get Default Value
    def get_default_schema_value(self, schema, key):
        return gsettings.get_schema_value(schema, key)

    # Set Default Value
    def set_default_schema_value(self, schema, key, type):
        #fp = open("/tmp/default.txt", "w")
        #print >> fp, "--------------"
        #fp.close()
        default_value = self.get_default_schema_value(schema, key)
        if default_value is not None:
            gsettings.set(schema, None, key, type, default_value)
            if schema == "org.gnome.desktop.wm.preferences" and key == "button-layout":
                if default_value == 'close,maximize,minimize:' or default_value == 'close,minimize,maximize:':
                    self.sysdaemon.change_titlebar_position('left')
                elif default_value == ':minimize,maximize,close':
                    self.sysdaemon.change_titlebar_position('right')
        else:
            raise NotImplemented

    # ---------------scrollbars---------------

    # set scrollbars mode overlay
    def set_scrollbars_mode_overlay(self):
        return gsettings.set('com.canonical.desktop.interface',
            None,
            'scrollbar-mode',
            'string', 'overlay-auto')

    # set scrollbars mode legacy
    def set_scrollbars_mode_legacy(self):
        return gsettings.set('com.canonical.desktop.interface',
            None,
            'scrollbar-mode',
            'string', 'normal')

    # get scrollbars mode
    def get_scrollbars_mode(self):
        return gsettings.get('com.canonical.desktop.interface',
            None, 'scrollbar-mode', 'string')

    # ---------------touchpad---------------

    # enable/disable the touchpad
    def set_touchpad_enable(self, flag):
        return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
            None,
            'touchpad-enabled',
            'boolean', flag)

    # get is touchpad enable
    def get_touchpad_enable(self):
        return gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
            None, 'touchpad-enabled', 'boolean')

    # set touch scrolling mode edge
    def set_touchscrolling_mode_edge(self):
        return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
            None,
            'scroll-method',
            'string', 'edge-scrolling')

    # set touch scrolling mode two-finger
    def set_touchscrolling_mode_twofinger(self):
        return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
            None,
            'scroll-method',
            'string', 'two-finger-scrolling')

    # get touchpad scrolling mode
    def get_touchscrolling_mode(self):
        return gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
            None, 'scroll-method', 'string')

    # set touch scrolling use horizontal True/False
    def set_touchscrolling_use_horizontal(self, flag):
        return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
            None,
            'horiz-scroll-enabled',
            'boolean', flag)

    # get is touch scrolling use horizontal
    def get_touchscrolling_use_horizontal(self):
        return gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
            None, 'horiz-scroll-enabled', 'boolean')

    # ---------------window---------------

    # set window button alignment left
    def set_window_button_align_left(self):
        gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'button-layout',
            'string', 'close,maximize,minimize:')
        self.sysdaemon.change_titlebar_position("left")
        #return gsettings.set('org.gnome.desktop.wm.preferences',
        #    None,
        #    'button-layout',
        #    'string', 'close,maximize,minimize:')#close,minimize,maximize:

    # set window button alignment right
    def set_window_button_align_right(self):
        gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'button-layout',
            'string', ':minimize,maximize,close')
        self.sysdaemon.change_titlebar_position("right")
        #return gsettings.set('org.gnome.desktop.wm.preferences',
        #    None,
        #    'button-layout',
        #    'string', ':minimize,maximize,close')

    # get window button alignment
    def get_window_button_align(self):
        value = gsettings.get('org.gnome.desktop.wm.preferences',
            None, 'button-layout', 'string')
        if value == 'close,maximize,minimize:' or value == 'close,minimize,maximize:':
            return 'left'
        elif value == ':minimize,maximize,close' or value == ':maximize,minimize,close':
            return 'right'
        #elif value == 'close,minimize,maximize:':
        #    return 'default'
        else:
            return 'custom'

    # set right click menus have icons 菜单带图标 是否可在菜单项旁显示图标。
    def set_menus_have_icons(self, flag):
        return gsettings.set('org.gnome.desktop.interface',
            None,
            'menus-have-icons',
            'boolean', flag)

    # get is right click menus have icons
    def get_menus_have_icons(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'menus-have-icons', 'boolean')

    #-----------------------窗口控制按钮位置----------------------
    # get window button
    #def get_window_button(self):
    #    return ['close,minimize,maximize:', ':minimize,maximize,close'] #左边/右边

    # get current window button
    #def get_current_window_button(self):
    #    return gsettings.get('org.gnome.desktop.wm.preferences',
    #        None, 'button-layout', 'string')

    # set window button
    #def set_window_button(self, value):
    #    return gsettings.set('org.gnome.desktop.wm.preferences',
    #        None,
    #        'button-layout',
    #        'string', value)

    #-----------------------标题栏鼠标滚轮动作---------------------
    # get titlebar wheel
    def get_titlebar_wheel(self):
        return ['none', 'shade']

    # get current titlebar wheel
    def get_current_titlebar_wheel(self):
        return gsettings.get('org.compiz.gwd',
            None, 'mouse-wheel-action', 'string')

    # set titlebar wheel
    def set_titlebar_wheel(self, value):
        return gsettings.set('org.compiz.gwd',
            None,
            'mouse-wheel-action',
            'string', value)

    #-------------------------标题栏双击动作-------------------------
    # get titlebar double
    def get_titlebar_double(self):
        return ['none', 'toggle-maximize', 'minimize', 'toggle-shade', 'lower', 'menu']

    # get current titlebar double
    def get_current_titlebar_double(self):
        return gsettings.get('org.gnome.desktop.wm.preferences',
            None, 'action-double-click-titlebar', 'string')

    # set titlebar double
    def set_titlebar_double(self, value):
        return gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'action-double-click-titlebar',
            'string', value)

    #-------------------------标题栏中键动作-------------------------
    # get titlebar middle
    def get_titlebar_middle(self):
        return ['none', 'toggle-maximize', 'minimize', 'toggle-shade', 'lower','menu']

    # get current titlebar middle
    def get_current_titlebar_middle(self):
        return gsettings.get('org.gnome.desktop.wm.preferences',
            None, 'action-middle-click-titlebar', 'string')

    # set titlebar middle
    def set_titlebar_middle(self, value):
        return gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'action-middle-click-titlebar',
            'string', value)

    #-------------------------标题栏右键动作-------------------------
    # get titlebar right
    def get_titlebar_right(self):
        return ['none', 'toggle-maximize', 'minimize', 'toggle-shade', 'lower','menu']

    # get current titlebar right
    def get_current_titlebar_right(self):
        return gsettings.get('org.gnome.desktop.wm.preferences',
            None, 'action-right-click-titlebar', 'string')

    # set titlebar right
    def set_titlebar_right(self, value):
        return gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'action-right-click-titlebar',
            'string', value)

if __name__ == '__main__':
    gsettings.set('org.compiz.gwd',None,'mouse-wheel-action', 'string', 'shade')
#    sss = System(None)
#    print sss.set_titlebar_wheel('shade')

    #aa = sss.get_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'touchpad-enabled')
    #print aa#True
    #sss.set_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'touchpad-enabled', 'boolean')
    #bb = sss.get_default_schema_value('com.canonical.desktop.interface', 'scrollbar-mode')
    #print bb#overlay-auto
    #sss.set_default_schema_value('com.canonical.desktop.interface', 'scrollbar-mode', 'string')
    #cc = sss.get_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'scroll-method')
    #print cc#two-finger-scrolling
    #sss.set_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'scroll-method', 'string')
#    dd = sss.get_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'horiz-scroll-enabled')
#    print dd#True
    #sss.set_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'horiz-scroll-enabled', 'boolean')

    #print sss.get_scrollbars_mode()
    #print sss.get_touchpad_enable()
    #print sss.get_touchscrolling_mode()
    #print sss.get_touchscrolling_use_horizontal()
    #print sss.get_window_button_align()
    #print sss.get_menus_have_icons()
# 	sss.set_menus_have_icons(True)
# 	sss.set_touchpad_enable(True)
    #sss.set_scrollbars_mode_overlay()
    # sss.set_scrollbars_mode_legacy()
    # sss.set_touchscrolling_mode_edge()
    #sss.set_touchscrolling_mode_twofinger()
    #sss.set_touchscrolling_use_horizontal(True)
    # sss.set_window_button_align_left()
    # sss.set_window_button_align_right()
