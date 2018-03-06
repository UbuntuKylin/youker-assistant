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
import platform
from gi.repository import Gio as gio

class System():

    desktop = None
    touchpad_remove = False

    def __init__(self, sysdaemon):
        self.sysdaemon = sysdaemon
        self.desktop = os.getenv('XDG_CURRENT_DESKTOP')
        if self.desktop is None:
             self.desktop = os.getenv('XDG_SESSION_DESKTOP')
        release_info = platform.platform()
        # 20160119
        if "org.gnome.settings-daemon.peripherals.touchpad" in gio.Settings.list_schemas():
            self.touchpad_remove = False
        else:
            self.touchpad_remove = True
#        if "15.10-wily" in release_info:
#            self.touchpad_remove = True

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
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.peripherals-touchpad',
                None,
                'touchpad-enabled',
                'boolean', flag)
        else:
            # kobe1510
            if self.touchpad_remove:
                return False
            else:
                return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
                    None,
                    'touchpad-enabled',
                    'boolean', flag)

    # get is touchpad enable
    def get_touchpad_enable(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.peripherals-touchpad',
                None, 'touchpad-enabled', 'boolean')
        else:
            # kobe1510
            if self.touchpad_remove:
                return False
            else:
                return gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
                    None, 'touchpad-enabled', 'boolean')

    def set_touchscrolling_mode_disabled(self):
        # kobe1510
        if self.touchpad_remove:
            return gsettings.set('org.gnome.desktop.peripherals.touchpad',
                None,
                'scroll-method',
                'string', 'disabled')
        else:
            return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
                None,
                'scroll-method',
                'string', 'disabled')

    # set touch scrolling mode edge
    def set_touchscrolling_mode_edge(self):
        # kobe1510
        if self.touchpad_remove:
            return gsettings.set('org.gnome.desktop.peripherals.touchpad',
                None,
                'scroll-method',
                'string', 'edge-scrolling')
        else:
            return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
                None,
                'scroll-method',
                'string', 'edge-scrolling')

    # set touch scrolling mode two-finger
    def set_touchscrolling_mode_twofinger(self):
        # kobe1510
        if self.touchpad_remove:
            return gsettings.set('org.gnome.desktop.peripherals.touchpad',
                None,
                'scroll-method',
                'string', 'two-finger-scrolling')
        else:
            return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
                None,
                'scroll-method',
                'string', 'two-finger-scrolling')

    # get touchpad scrolling mode
    def get_touchscrolling_mode(self):
        # kobe1510
        if self.touchpad_remove:
            return gsettings.get('org.gnome.desktop.peripherals.touchpad',
                None, 'scroll-method', 'string')
        else:
            return gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
                None, 'scroll-method', 'string')

    #----------------------------mate--------------------------
    #选择触摸板滚动模式。支持的值有：0 - 禁止，1 - 边界滚动，2 - 双指滚动
    def set_mate_touchscrolling_mode(self, value):
        return gsettings.set('org.mate.peripherals-touchpad',
            None,
            'scroll-method',
            'int', value)

    def get_mate_touchscrolling_mode(self):
        return gsettings.get('org.mate.peripherals-touchpad',
            None, 'scroll-method', 'int')

    # set touch scrolling use horizontal True/False
    def set_touchscrolling_use_horizontal(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.peripherals-touchpad',
                None,
                'horiz-scroll-enabled',
                'boolean', flag)
        else:
            # kobe1510
            if self.touchpad_remove:
                return False
            else:
                return gsettings.set('org.gnome.settings-daemon.peripherals.touchpad',
                    None,
                    'horiz-scroll-enabled',
                    'boolean', flag)

    # get is touch scrolling use horizontal
    def get_touchscrolling_use_horizontal(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.peripherals-touchpad',
                None, 'horiz-scroll-enabled', 'boolean')
        else:
            # kobe1510
            if self.touchpad_remove:
                return False
            else:
                return gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
                    None, 'horiz-scroll-enabled', 'boolean')

    # ---------------window---------------

    # set window button alignment left
    def set_window_button_align_left(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            value = gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'button-layout', 'string')
            if "menu" in value:
                gsettings.set('org.gnome.desktop.wm.preferences',
                    None,
                    'button-layout',
                    'string', 'close,maximize,minimize:menu')
            else:
                gsettings.set('org.gnome.desktop.wm.preferences',
                    None,
                    'button-layout',
                    'string', 'close,maximize,minimize')
        else:
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
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            value = gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'button-layout', 'string')
            if "menu" in value:
                gsettings.set('org.gnome.desktop.wm.preferences',
                    None,
                    'button-layout',
                    'string', 'menu:minimize,maximize,close')
            else:
                gsettings.set('org.gnome.desktop.wm.preferences',
                    None,
                    'button-layout',
                    'string', ':minimize,maximize,close')
        else:
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
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            value = gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'button-layout', 'string')
            if value == 'close,maximize,minimize:menu' or value == 'close,minimize,maximize:menu' or value == 'close,minimize,maximize:' or value == 'close,maximize,minimize:':
                return 'left'
            elif value == 'menu:minimize,maximize,close' or value == 'menu:maximize,minimize,close' or value == ':minimize,maximize,close' or value == ':maximize,minimize,close':
                return 'right'
        else:
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
#    “toggle-shade”卷起/展开窗口，“toggle-maximize”最大化/还原窗口，
#“toggle-maximize-horizontally”及“toggle-maximize-vertically”横向及纵向最大化/还原窗口，
#“minimize”最小化窗口，“shade”卷起窗口，
#“menu”显示窗口菜单，“lower”将窗口降低到所有窗口之下，还有“none”什么也不做。
    # get titlebar double
    def get_titlebar_options(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return ['none', 'toggle_maximize', 'toggle_maximize_horizontally', 'toggle_maximize_vertically', 'minimize',  'toggle_shade', 'lower', 'menu', 'last']
        else:
            return ['none', 'toggle-maximize', 'toggle-maximize-horizontally', 'toggle-maximize-vertically', 'minimize', 'toggle-shade', 'lower', 'menu', 'last']

    # get current titlebar double
    def get_current_titlebar_double(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'action-double-click-titlebar', 'string')
        else:
            return gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'action-double-click-titlebar', 'string')

    # set titlebar double
    def set_titlebar_double(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.gnome.desktop.wm.preferences',
                None,
                'action-double-click-titlebar',
                'string', value)
        else:
            return gsettings.set('org.gnome.desktop.wm.preferences',
                None,
                'action-double-click-titlebar',
                'string', value)

    #-------------------------标题栏中键动作-------------------------
    # get titlebar middle
    def get_titlebar_middle(self):
        return ['none', 'toggle-maximize', 'toggle-maximize-horizontally', 'toggle-maximize-vertically', 'minimize', 'toggle-shade', 'lower', 'menu', 'last']

    # get current titlebar middle
    def get_current_titlebar_middle(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'action-middle-click-titlebar', 'string')
        else:
            return gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'action-middle-click-titlebar', 'string')

    # set titlebar middle
    def set_titlebar_middle(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.gnome.desktop.wm.preferences',
                None,
                'action-middle-click-titlebar',
                'string', value)
        else:
            return gsettings.set('org.gnome.desktop.wm.preferences',
                None,
                'action-middle-click-titlebar',
                'string', value)

    #-------------------------标题栏右键动作-------------------------
    # get titlebar right
    def get_titlebar_right(self):
        return ['none', 'toggle-maximize', 'toggle-maximize-horizontally', 'toggle-maximize-vertically', 'minimize', 'toggle-shade', 'lower', 'menu', 'last']

    # get current titlebar right
    def get_current_titlebar_right(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'action-right-click-titlebar', 'string')
        else:
            return gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'action-right-click-titlebar', 'string')

    # set titlebar right
    def set_titlebar_right(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.gnome.desktop.wm.preferences',
                None,
                'action-right-click-titlebar',
                'string', value)
        else:
            return gsettings.set('org.gnome.desktop.wm.preferences',
                None,
                'action-right-click-titlebar',
                'string', value)

    def get_current_idle_delay(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.session',
                None, 'idle-delay', 'int')
        else:
            return gsettings.get('org.gnome.desktop.session',
                None, 'idle-delay', 'uint')

    def set_current_idle_delay(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gsettings.set('org.mate.session',
                None,
                'idle-delay',
                'int', value)
        else:
            gsettings.set('org.gnome.desktop.session',
                None,
                'idle-delay',
                'uint', value)

    def get_lock_enabled(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.screensaver',
                None, 'lock-enabled', 'boolean')
        else:
            return gsettings.get('org.gnome.desktop.screensaver',
                None, 'lock-enabled', 'boolean')

    def set_lock_enabled(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gsettings.set('org.mate.screensaver',
                None,
                'lock-enabled',
                'boolean', value)
        else:
            gsettings.set('org.gnome.desktop.screensaver',
                None,
                'lock-enabled',
                'boolean', value)

    def get_current_lock_delay(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.screensaver',
                None, 'lock-delay', 'int')
        else:
            return gsettings.get('org.gnome.desktop.screensaver',
                None, 'lock-delay', 'uint')

    def set_current_lock_delay(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gsettings.set('org.mate.screensaver',
                None,
                'lock-delay',
                'int', value)
        else:
            gsettings.set('org.gnome.desktop.screensaver',
                None,
                'lock-delay',
                'uint', value)

    def get_current_critical_low(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.power-manager',
                None, 'action-critical-battery', 'string')
        else:
            return gsettings.get('org.gnome.settings-daemon.plugins.power',
                None, 'critical-battery-action', 'string')

    def set_current_critical_low(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gsettings.set('org.mate.power-manager',
                None,
                'action-critical-battery',
                'string', value)
        else:
            gsettings.set('org.gnome.settings-daemon.plugins.power',
                None,
                'critical-battery-action',
                'string', value)

    def get_current_lid_battery(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.power-manager',
                None, 'button-lid-battery', 'string')
        else:
            return gsettings.get('org.gnome.settings-daemon.plugins.power',
                None, 'lid-close-battery-action', 'string')

    def set_current_lid_battery(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gsettings.set('org.mate.power-manager',
                None,
                'button-lid-battery',
                'string', value)
        else:
            gsettings.set('org.gnome.settings-daemon.plugins.power',
                None,
                'lid-close-battery-action',
                'string', value)

    def get_current_lid_ac(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.power-manager',
                None, 'button-lid-ac', 'string')
        else:
            return gsettings.get('org.gnome.settings-daemon.plugins.power',
                None, 'lid-close-ac-action', 'string')

    def set_current_lid_ac(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gsettings.set('org.mate.power-manager',
                None,
                'button-lid-ac',
                'string', value)
        else:
            gsettings.set('org.gnome.settings-daemon.plugins.power',
                None,
                'lid-close-ac-action',
                'string', value)

    #----------------------------------------------------------------------
    def get_current_sleep_timeout_display_battery(self):
        return gsettings.get('org.mate.power-manager',
            None, 'sleep-display-battery', 'int')

    def set_current_sleep_timeout_display_battery(self, value):
        gsettings.set('org.mate.power-manager',
            None,
            'sleep-display-battery',
            'int', value)

    def get_current_sleep_timeout_display_ac(self):
        return gsettings.get('org.mate.power-manager',
            None, 'sleep-display-ac', 'int')

    def set_current_sleep_timeout_display_ac(self, value):
        gsettings.set('org.mate.power-manager',
            None,
            'sleep-display-ac',
            'int', value)
    #----------------------------------------------------------------------

    def get_current_sleep_timeout_battery(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.power-manager',
                None, 'sleep-computer-battery', 'int')
        else:
            return gsettings.get('org.gnome.settings-daemon.plugins.power',
                None, 'sleep-inactive-battery-timeout', 'int')

    def set_current_sleep_timeout_battery(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gsettings.set('org.mate.power-manager',
                None,
                'sleep-computer-battery',
                'int', value)
        else:
            gsettings.set('org.gnome.settings-daemon.plugins.power',
                None,
                'sleep-inactive-battery-timeout',
                'int', value)

    def get_current_sleep_timeout_ac(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.power-manager',
                None, 'sleep-computer-ac', 'int')
        else:
            return gsettings.get('org.gnome.settings-daemon.plugins.power',
                None, 'sleep-inactive-ac-timeout', 'int')

    def set_current_sleep_timeout_ac(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gsettings.set('org.mate.power-manager',
                None,
                'sleep-computer-ac',
                'int', value)
        else:
            gsettings.set('org.gnome.settings-daemon.plugins.power',
                None,
                'sleep-inactive-ac-timeout',
                'int', value)

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
