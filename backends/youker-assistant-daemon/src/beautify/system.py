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

class System:

    # -----------------默认值-----------------
    # Get Default Value
    def get_default_schema_value(self, schema, key):
        return gsettings.get_schema_value(schema, key)

    # Set Default Value
    def set_default_schema_value(self, schema, key, type):
        default_value = self.get_default_schema_value(schema, key)
        if default_value is not None:
            return gsettings.set(schema, None, key, type, default_value)
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
        return gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'button-layout',
            'string', 'close,maximize,minimize:')

    # set window button alignment right
    def set_window_button_align_right(self):
        return gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'button-layout',
            'string', ':minimize,maximize,close')

    # get window button alignment
    def get_window_button_align(self):
        value = gsettings.get('org.gnome.desktop.wm.preferences',
            None, 'button-layout', 'string')
        if value == 'close,maximize,minimize:':
            return 'left'
        elif value == ':minimize,maximize,close':
            return 'right'
        elif value == 'close,minimize,maximize:':
            return 'default'
        else:
            return 'custom'

    # set right click menus have icons
    def set_menus_have_icons(self, flag):
        return gsettings.set('org.gnome.desktop.interface',
            None,
            'menus-have-icons',
            'boolean', flag)

    # get is right click menus have icons
    def get_menus_have_icons(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'menus-have-icons', 'boolean')

if __name__ == '__main__':
    sss = System()

    #aa = sss.get_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'touchpad-enabled')
    #print aa#True
    #sss.set_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'touchpad-enabled', 'boolean')
    #bb = sss.get_default_schema_value('com.canonical.desktop.interface', 'scrollbar-mode')
    #print bb#overlay-auto
    #sss.set_default_schema_value('com.canonical.desktop.interface', 'scrollbar-mode', 'string')
    #cc = sss.get_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'scroll-method')
    #print cc#two-finger-scrolling
    #sss.set_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'scroll-method', 'string')
    dd = sss.get_default_schema_value('org.gnome.settings-daemon.peripherals.touchpad', 'horiz-scroll-enabled')
    print dd#True
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
