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

import sys
import os
import glob
import fcntl
import shutil
import logging
import tempfile
import subprocess
import re
from subprocess import PIPE
import apt
import apt_pkg
import dbus
import dbus.service
import dbus.mainloop.glib
import time
import threading
import platform
import cleaner
from autostartmanage import autostartmanage
#import pywapi
import urllib.request, urllib.error, urllib.parse, urllib.request, urllib.parse, urllib.error
from urllib.parse import urlencode
from xml.dom.minidom import parseString
import re
import json
import locale
import aptsources.sourceslist

import datetime
HOME = os.path.expandvars('$HOME')

#import mechanize
#import cookielib
#import random
#from BeautifulSoup import BeautifulSoup


from beautify.desktop import Desktop
from beautify.unity import Unity
from beautify.theme import Theme
from beautify.system import System
from beautify.sound import Sound
from beautify.filemanager import FileManager
#from beautify.cloudconfig import CloudConfig
from sysinfo import Sysinfo
#from camera.capture import Capture
#from weather.weatherinfo import WeatherInfo
#from weather.yahoo import YahooWeather
from .common import *
#from unzip import unzip_resource
#from piston_mini_client import APIError
import httplib2
#from weather.piston import WeatherPistonAPI
#MySever = ("http://service.ubuntukylin.com:8001/weather/api/1.0/")
#WeatherPistonAPI.default_service_root = MySever

from .piston_remoter import PingBackPistonAPI
#PingBackSever = ("http://servicPingBackPistonAPIe.ubuntukylin.com:8001/youker-assistant/")
#PingBackPistonAPI.default_service_root = PingBackSever
PINGBACK_SERVER = "http://service.ubuntukylin.com:8001/youker-assistant/"

#from piston_remoter import ServerPingBackAPI
#WEATHER_SERVER = "http://service.ubuntukylin.com:8001/weather/"

#from appcollections.monitorball.monitor_ball import MonitorBall

#from sso.ubuntusso import get_ubuntu_sso_backend

log = logging.getLogger('SessionDaemon')
#from slider.wizard import Wizard

INTERFACE = "com.kylin.assistant.sessiondaemon"
UKPATH = "/com/kylin/assistant/sessiondaemon"
POWER_PATH = "/sys/class/power_supply"
BATTERY_PATH = "/sys/class/power_supply/BAT0"
BAT_FILE = "/sys/class/power_supply/BAT0/uevent"

from gi.repository import Gio as gio
from .common import (BOOL_TYPE, INT_TYPE, DOUBLE_TYPE, STRING_TYPE)

#Depends:gir1.2-gconf-2.0
#from gi.repository import GConf
#import gconf
#TOPKEY = "/org/mate/panel/toplevels/top/size"
#BOTTOMKEY = "/org/mate/panel/toplevels/bottom/size"

class SessionDaemon(dbus.service.Object):
    def __init__ (self, mainloop):
        #self.wizardconf = Wizard()
#        self.ip_addr = None
        self.distrowatch = []
        self.ubuntukylin_dict = dict()
#        self.cloudconf = CloudConfig(self)
        self.sysconf = Sysinfo()
        self.desktopconf = Desktop()
        self.unityconf = Unity()
        self.themeconf = Theme()
        self.systemconf = System(self)
        self.soundconf = Sound()
#        self.ballconf = MonitorBall()
        self.fileconf = FileManager()
#        self.yahooconf = YahooWeather(self)
#        self.server = WeatherPistonAPI(service_root=MySever)
        self.premoter = PingBackPistonAPI(service_root=PINGBACK_SERVER)
#        self.weatherping = ServerPingBackAPI(service_root=WEATHER_SERVER)
#        self.daemonsame = cleaner.SearchTheSame()
#        self.daemonlarge = cleaner.ManageTheLarge()
#        self.daemonunneed = cleaner.CleanTheUnneed()
#        self.daemonoldkernel = cleaner.CleanTheOldkernel()
#        self.daemoncache = cleaner.CleanTheCache()
#        self.init_mechanize()
#        # sso - Robert
#        self.sso = get_ubuntu_sso_backend()
#        self.sso.connect("whoami", self.slot_whoami_done)
#        self.sso.connect("logout", self.slot_logout_successful)
#        self.sso.connect("fail",self.slot_login_fail)
        self.token = ""
        self.user = ""
        self.display_name = ""
        self.preferred_email = ""

        self.desktop = os.getenv('XDG_CURRENT_DESKTOP')
        if self.desktop is None:
             self.desktop = os.getenv('XDG_SESSION_DESKTOP')

        # gtk theme
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.interface_settings = gio.Settings.new("org.mate.interface")
        else:
            self.interface_settings = gio.Settings.new("org.gnome.desktop.interface")
        self.interface_settings.connect("changed::gtk-theme", self.gio_settings_monitor, STRING_TYPE)

        # icon
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
#            self.interface_settings = gio.Settings.new("org.mate.interface")
            self.interface_settings.connect("changed::icon-theme", self.gio_settings_monitor, STRING_TYPE)
            self.background_settings = gio.Settings.new("org.mate.background")
            self.background_settings.connect("changed::show-desktop-icons", self.gio_settings_monitor, BOOL_TYPE)
            self.desktop_settings = gio.Settings.new("org.mate.caja.desktop")
            for key in ("computer-icon-visible", "home-icon-visible", "network-icon-visible", "trash-icon-visible", "volumes-visible"):
                self.desktop_settings.connect("changed::%s" % key, self.gio_settings_monitor, BOOL_TYPE)
        else:
#            self.interface_settings = gio.Settings.new("org.gnome.desktop.interface")
            self.interface_settings.connect("changed::icon-theme", self.gio_settings_monitor, STRING_TYPE)
            self.background_settings = gio.Settings.new("org.gnome.desktop.background")
            self.background_settings.connect("changed::show-desktop-icons", self.gio_settings_monitor, BOOL_TYPE)
            self.desktop_settings = gio.Settings.new("org.gnome.nautilus.desktop")
            for key in ("home-icon-visible", "network-icon-visible", "trash-icon-visible", "volumes-visible"):
                self.desktop_settings.connect("changed::%s" % key, self.gio_settings_monitor, BOOL_TYPE)

        # mouse
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.mouse_settings = gio.Settings.new("org.mate.peripherals-mouse")
            self.mouse_settings.connect("changed::cursor-theme", self.gio_settings_monitor, STRING_TYPE)
            self.mouse_settings.connect("changed::cursor-size", self.gio_settings_monitor, INT_TYPE)
        else:
            self.interface_settings.connect("changed::cursor-theme", self.gio_settings_monitor, STRING_TYPE)
            self.interface_settings.connect("changed::cursor-size", self.gio_settings_monitor, INT_TYPE)

        # voice
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.sound_settings = gio.Settings.new("org.mate.sound")
        else:
            self.sound_settings = gio.Settings.new("org.gnome.desktop.sound")
        self.sound_settings.connect("changed::theme-name", self.gio_settings_monitor, STRING_TYPE)
        self.sound_settings.connect("changed::event-sounds", self.gio_settings_monitor, BOOL_TYPE)
        self.sound_settings.connect("changed::input-feedback-sounds", self.gio_settings_monitor, BOOL_TYPE)

        if self.desktop == "Unity":
            #unity launcher position
            self.unity_launcher_position = gio.Settings.new("com.canonical.Unity.Launcher")
            self.unity_launcher_position.connect("changed::launcher-position", self.gio_settings_monitor, STRING_TYPE)
            #unity launcher
            self.unity_settings = gio.Settings("org.compiz.unityshell", "/org/compiz/profiles/unity/plugins/unityshell/")
            self.unity_settings.connect("changed::icon-size", self.gio_settings_monitor, INT_TYPE)
            self.unity_settings.connect("changed::launcher-hide-mode", self.gio_settings_monitor, INT_TYPE)
            self.unity_settings.connect("changed::launcher-opacity", self.gio_settings_monitor, DOUBLE_TYPE)
            self.unity_settings.connect("changed::backlight-mode", self.gio_settings_monitor, INT_TYPE)
            #panel
            self.datetime_settings = gio.Settings.new("com.canonical.indicator.datetime")
            self.datetime_settings.connect("changed::show-seconds", self.gio_settings_monitor, BOOL_TYPE)
            self.datetime_settings.connect("changed::show-day", self.gio_settings_monitor, BOOL_TYPE)
            self.datetime_settings.connect("changed::show-date", self.gio_settings_monitor, BOOL_TYPE)
            #power
            self.power_settings = gio.Settings.new("com.canonical.indicator.power")
            self.power_settings.connect("changed::icon-policy", self.gio_settings_monitor, STRING_TYPE)
            self.power_settings.connect("changed::show-time", self.gio_settings_monitor, BOOL_TYPE)
            self.power_settings.connect("changed::show-percentage", self.gio_settings_monitor, BOOL_TYPE)

        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.toplevels_settings = gio.Settings("org.mate.panel.toplevel", "/org/mate/panel/toplevels/top/")
            self.toplevels_settings.connect("changed::size", self.gio_settings_monitor_diff, INT_TYPE, "top")
            self.toplevels_settings.connect("changed::auto-hide", self.gio_settings_monitor_diff, BOOL_TYPE, "top")
            self.bottomlevels_settings = gio.Settings("org.mate.panel.toplevel", "/org/mate/panel/toplevels/bottom/")
            self.bottomlevels_settings.connect("changed::size", self.gio_settings_monitor_diff, INT_TYPE, "bottom")
            self.bottomlevels_settings.connect("changed::auto-hide", self.gio_settings_monitor_diff, BOOL_TYPE, "bottom")

        # kobe: test GConf notify
##        kobekey = "/apps/metacity/general/titlebar_font"
##        aa = '/'.join(kobekey.split('/')[0: -1])#/apps/metacity/general
#        self.client = GConf.Client.get_default()
##        self.client.add_dir('/'.join(TOPKEY.split('/')[0: -1]), GConf.ClientPreloadType.PRELOAD_NONE)
#        self.client.add_dir("/org/mate/panel/toplevels/top", GConf.ClientPreloadType.PRELOAD_NONE)
#        self.client.notify_add(TOPKEY, self.gio_settings_monitor_diff)#, "top"
##        self.client = gconf.client_get_default()
##        self.client.add_dir('/'.join(TOPKEY.split('/')[0: -1]), gconf.CLIENT_PRELOAD_NONE)
##        self.client.notify_add(TOPKEY, self.gio_settings_monitor_diff, "top")

#        gc = GConf.Client.get_default()
#        print gc.get_int('/org/mate/panel/toplevels/top/size')
#        gc.set_int('/org/mate/panel/toplevels/top/size', 1)
#        print gc.get_int('/org/mate/panel/toplevels/top/size')

        # menubar
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.menubar_settings = gio.Settings.new("org.mate.panel.menubar")
            self.menubar_settings.connect("changed::show-applications", self.gio_settings_monitor, BOOL_TYPE)
            self.menubar_settings.connect("changed::show-desktop", self.gio_settings_monitor, BOOL_TYPE)
            self.menubar_settings.connect("changed::show-icon", self.gio_settings_monitor, BOOL_TYPE)
            self.menubar_settings.connect("changed::show-places", self.gio_settings_monitor, BOOL_TYPE)

        # window
        self.interface_settings.connect("changed::menus-have-icons", self.gio_settings_monitor, BOOL_TYPE)
        if self.desktop == "Unity":
            self.gwd_settings = gio.Settings.new("org.compiz.gwd")
            self.gwd_settings.connect("changed::mouse-wheel-action", self.gio_settings_monitor, STRING_TYPE)
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.titlebar_settings = gio.Settings.new("org.gnome.desktop.wm.preferences")
        else:
            self.titlebar_settings = gio.Settings.new("org.gnome.desktop.wm.preferences")
        self.titlebar_settings.connect("changed::button-layout", self.gio_settings_monitor, STRING_TYPE)
        self.titlebar_settings.connect("changed::action-double-click-titlebar", self.gio_settings_monitor, STRING_TYPE)
        self.titlebar_settings.connect("changed::action-middle-click-titlebar", self.gio_settings_monitor, STRING_TYPE)
        self.titlebar_settings.connect("changed::action-right-click-titlebar", self.gio_settings_monitor, STRING_TYPE)

        #font
        self.interface_settings.connect("changed::font-name", self.gio_settings_monitor, STRING_TYPE)
        self.desktop_settings.connect("changed::font", self.gio_settings_monitor, STRING_TYPE)
        self.interface_settings.connect("changed::monospace-font-name", self.gio_settings_monitor, STRING_TYPE)
        self.interface_settings.connect("changed::document-font-name", self.gio_settings_monitor, STRING_TYPE)
        self.titlebar_settings.connect("changed::titlebar-font", self.gio_settings_monitor, STRING_TYPE)
        self.interface_settings.connect("changed::text-scaling-factor", self.gio_settings_monitor, DOUBLE_TYPE)
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.font_settings = gio.Settings.new("org.mate.font-rendering")
        else:
            self.font_settings = gio.Settings.new("org.gnome.settings-daemon.plugins.xsettings")
        self.font_settings.connect("changed::hinting", self.gio_settings_monitor, STRING_TYPE)
        self.font_settings.connect("changed::antialiasing", self.gio_settings_monitor, STRING_TYPE)

        # touchpad
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.touchpad_settings = gio.Settings.new("org.mate.peripherals-touchpad")
            self.touchpad_settings.connect("changed::scroll-method", self.gio_settings_monitor, INT_TYPE)
            self.touchpad_settings.connect("changed::touchpad-enabled", self.gio_settings_monitor, BOOL_TYPE)
            self.touchpad_settings.connect("changed::horiz-scroll-enabled", self.gio_settings_monitor, BOOL_TYPE)
        else:
            # 20160119
            if "org.gnome.settings-daemon.peripherals.touchpad" in gio.Settings.list_schemas():
                self.touchpad_settings = gio.Settings.new("org.gnome.settings-daemon.peripherals.touchpad")
                self.touchpad_settings.connect("changed::scroll-method", self.gio_settings_monitor, STRING_TYPE)
                self.touchpad_settings.connect("changed::touchpad-enabled", self.gio_settings_monitor, BOOL_TYPE)
                self.touchpad_settings.connect("changed::horiz-scroll-enabled", self.gio_settings_monitor, BOOL_TYPE)
#            release_info = platform.platform()
#            if "15.10-wily" not in release_info:
#                self.touchpad_settings = gio.Settings.new("org.gnome.settings-daemon.peripherals.touchpad")
#                self.touchpad_settings.connect("changed::scroll-method", self.gio_settings_monitor, STRING_TYPE)
#                self.touchpad_settings.connect("changed::touchpad-enabled", self.gio_settings_monitor, BOOL_TYPE)
#                self.touchpad_settings.connect("changed::horiz-scroll-enabled", self.gio_settings_monitor, BOOL_TYPE)
        if self.desktop == "Unity":
            self.canonical_interface_settings = gio.Settings.new("com.canonical.desktop.interface")
            self.canonical_interface_settings.connect("changed::scrollbar-mode", self.gio_settings_monitor, STRING_TYPE)

        #file manager
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.filemanager_settings = gio.Settings.new("org.mate.caja.preferences")
        else:
            self.filemanager_settings = gio.Settings.new("org.gnome.nautilus.preferences")
        self.filemanager_settings.connect("changed::always-use-location-entry", self.gio_settings_monitor, BOOL_TYPE)

        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.mediahanding_settings = gio.Settings.new("org.mate.media-handling")
        else:
            self.mediahanding_settings = gio.Settings.new("org.gnome.desktop.media-handling")
        self.mediahanding_settings.connect("changed::automount", self.gio_settings_monitor, BOOL_TYPE)
        self.mediahanding_settings.connect("changed::automount-open", self.gio_settings_monitor, BOOL_TYPE)
        self.mediahanding_settings.connect("changed::autorun-never", self.gio_settings_monitor, BOOL_TYPE)
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.iconview_settings = gio.Settings.new("org.mate.caja.icon-view")
        else:
            self.iconview_settings = gio.Settings.new("org.gnome.nautilus.icon-view")
        self.iconview_settings.connect("changed::thumbnail-size", self.gio_settings_monitor, INT_TYPE)
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            self.thumbnail_settings = gio.Settings.new("org.mate.thumbnail-cache")
        else:
            self.thumbnail_settings = gio.Settings.new("org.gnome.desktop.thumbnail-cache")
        self.thumbnail_settings.connect("changed::maximum-age", self.gio_settings_monitor, INT_TYPE)
        self.thumbnail_settings.connect("changed::maximum-size", self.gio_settings_monitor, INT_TYPE)

        bus_name = dbus.service.BusName(INTERFACE, bus=dbus.SessionBus())
        dbus.service.Object.__init__(self, bus_name, UKPATH)
        self.mainloop = mainloop

#    def gio_settings_monitor_diff(self, client, cnxn_id, entry, params):
#        pass
    def gio_settings_monitor_diff(self, settings, key, type, diff):
        if diff == "top":
            if type == BOOL_TYPE and key == "auto-hide":
                value = settings.get_boolean(key)
                self.notify_boolean("auto-hide-top", value)
            elif type == INT_TYPE and key == "size":
                value = settings.get_int(key)
                self.notify_int("size-top", value)
        elif diff == "bottom":
            if type == BOOL_TYPE and key == "auto-hide":
                value = settings.get_boolean(key)
                self.notify_boolean("auto-hide-bottom", value)
            elif type == INT_TYPE and key == "size":
                value = settings.get_int(key)
                self.notify_int("size-bottom", value)

    def gio_settings_monitor(self, settings, key, type):
#        value = settings.get_boolean("home-icon-visible")#get_int get_string get_string
        if type == BOOL_TYPE:
            value = settings.get_boolean(key)
            self.notify_boolean(key, value)
        elif type == INT_TYPE:
            value = settings.get_int(key)
            self.notify_int(key, value)
        elif type == DOUBLE_TYPE:
            value = settings.get_double(key)
            self.notify_double(key, value)
        elif type == STRING_TYPE:
            value = settings.get_string(key)
            self.notify_string(key, value)

    @dbus.service.signal(INTERFACE, signature='sb')
    def notify_boolean(self, key, value):
        pass

    @dbus.service.signal(INTERFACE, signature='si')
    def notify_int(self, key, value):
        pass

    @dbus.service.signal(INTERFACE, signature='sd')
    def notify_double(self, key, value):
        pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def notify_string(self, key, value):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_os_release(self):
        return platform.platform()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def currently_installed_version(self):
        apt_list = []
        cache = apt.Cache()
        try:
            pkg = cache['kylin-assistant']
        except KeyError as e:
            return [""]
        installed_version = pkg.installed.version
#        print installed_version
        if ":" in installed_version:
            info = installed_version.split(":")
            apt_list.append(info.at(1))
        else:
            apt_list.append(installed_version)
#        print pkg.installed.version#1:2.0.3-0~704~ubuntu15.04.1
        if len(pkg.versions) == 2:
#            print pkg.versions[0].version, pkg.versions[1].version
            if pkg.versions[0].version == pkg.versions[1].version:
                apt_list.append(pkg.versions[0].version)
                apt_list.append(pkg.versions[1].version)
                apt_list.append("0")
            else:
                tmp_installed = ''
                tmp_unstalled = ''
                if pkg.installed.version == pkg.versions[0].version:
                    if ":" in pkg.versions[0].version:
                        tmp_installed = pkg.versions[0].version.split(":").at(1)
                    else:
                        tmp_installed = pkg.versions[0].version
                    if ":" in pkg.versions[1].version:
                        tmp_unstalled = pkg.versions[1].version.split(":").at(1)
                    else:
                        tmp_unstalled = pkg.versions[1].version
                    if tmp_installed < tmp_unstalled:
                        apt_list.append(tmp_installed)
                        apt_list.append(tmp_unstalled)
                        apt_list.append("1")
                elif pkg.installed.version == pkg.versions[1].version:
                        if ":" in pkg.versions[1].version:
                            tmp_installed = pkg.versions[1].version.split(":").at(1)
                        else:
                            tmp_installed = pkg.versions[1].version
                        if ":" in pkg.versions[0].version:
                            tmp_unstalled = pkg.versions[0].version.split(":").at(1)
                        else:
                            tmp_unstalled = pkg.versions[0].version
                        if tmp_installed < tmp_unstalled:
                            apt_list.append(tmp_installed)
                            apt_list.append(tmp_unstalled)
                            apt_list.append("1")
        return apt_list

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def run_selected_app(self, pkgname):
        run_app(pkgname)

    #---------------------------------conserve energy------------------------------------
    @dbus.service.method(INTERFACE, in_signature='d', out_signature='')
    def adjust_screen_gamma(self, gamma):
        cmd = "xgamma -gamma " + str(gamma)
        print(cmd)
        os.system(cmd)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='d')
    def get_screen_gamma(self):
#        p = os.popen("xgamma")
        status, output = subprocess.getstatusoutput("xgamma")
        gamma_list = output.split(" ")
        gamma = gamma_list[len(gamma_list) - 1]
        return float(gamma)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_idle_delay_list(self):
        return ['60', '120', '180', '300', '600', '1800', '3600', '0']

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_current_idle_delay(self):
        return self.systemconf.get_current_idle_delay()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_current_idle_delay(self, value):
        self.systemconf.set_current_idle_delay(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_lock_enabled(self):
        return self.systemconf.get_lock_enabled()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='')
    def set_lock_enabled(self, value):
        self.systemconf.set_lock_enabled(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_lock_delay_list(self):
        return ['30', '60', '120', '180', '300', '600', '1800', '3600', '0']

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_current_lock_delay(self):
        return self.systemconf.get_current_lock_delay()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_current_lock_delay(self, value):
        self.systemconf.set_current_lock_delay(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_sleep_timeout_list(self):
        return ['300', '600', '1200', '1800', '3600', '7200', '0']

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_critical_low(self):
        return self.systemconf.get_current_critical_low()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_current_critical_low(self, value):
        self.systemconf.set_current_critical_low(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_lid_battery(self):
        return self.systemconf.get_current_lid_battery()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_current_lid_battery(self, value):
        self.systemconf.set_current_lid_battery(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_lid_ac(self):
        return self.systemconf.get_current_lid_ac()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_current_lid_ac(self, value):
        self.systemconf.set_current_lid_ac(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_current_sleep_timeout_display_battery(self):
        return self.systemconf.get_current_sleep_timeout_display_battery()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_current_sleep_timeout_display_battery(self, value):
        self.systemconf.set_current_sleep_timeout_display_battery(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_current_sleep_timeout_display_ac(self):
        return self.systemconf.get_current_sleep_timeout_display_ac()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_current_sleep_timeout_display_ac(self, value):
        self.systemconf.set_current_sleep_timeout_display_ac(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_current_sleep_timeout_battery(self):
        return self.systemconf.get_current_sleep_timeout_battery()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_current_sleep_timeout_battery(self, value):
        self.systemconf.set_current_sleep_timeout_battery(value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_current_sleep_timeout_ac(self):
        return self.systemconf.get_current_sleep_timeout_ac()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_current_sleep_timeout_ac(self, value):
        self.systemconf.set_current_sleep_timeout_ac(value)


#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def check_user(self):
#        try:
#            self.sso = get_ubuntu_sso_backend()
#            self.sso.connect("whoami", self.slot_whoami_done)
#            self.sso.connect("logout", self.slot_logout_successful)
#            self.sso.connect("fail",self.slot_login_fail)
#            # try backend login
#            self.sso.find_oauth_token()
#        except ImportError:
#            print('Initial ubuntu-kylin-sso-client failed, seem it is not installed.')
#        except Exception as e:
#            print('Check user failed.')
#            print(e)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def slot_do_login_account(self):
#        try:
#            self.sso.set_show_register(False)
#            self.sso.get_oauth_token()
#        except ImportError:
#            print('Initial ubuntu-kylin-sso-client failed, seem it is not installed.')
#        except Exception as e:
#            print('User login failed.')
#            print(e)

    # user register
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def slot_do_register(self):
#        try:
#            self.sso.set_show_register(True)
#            self.sso.get_oauth_token()

#        except ImportError:
#            print('Initial ubuntu-kylin-sso-client failed, seem it is not installed.')
#        except Exception as e:
#            print('User register failed.')
#            print(e)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def slot_do_logout(self):
#        try:
#            self.sso.clear_token()

#        except ImportError:
#            print('Initial ubuntu-kylin-sso-client failed, seem it is not installed.')
#        except Exception as e:
#            print('User logout failed.')
#            print(e)

    #update user login status
    def slot_whoami_done(self, sso, result):
        self.user = result["username"]
        self.display_name = result["displayname"]
        self.preferred_email = result["preferred_email"]
        print('Login success, username: %s' % self.display_name)
        self.youkerid_whoami_signal(self.display_name, self.preferred_email)

    def slot_logout_successful(self, sso):
        if self.token:
            print('User %s has been logout' % self.display_name)
            self.token = ''
            self.user = ''
            self.display_name = ''
            self.preferred_email = ''
        else:
            print('No user has been login')
        self.youkerid_logout_signal()

    def slot_login_fail(self, sso):
        print('Login or logout failed')
        self.youkerid_login_fail_signal()

    @dbus.service.signal(INTERFACE, signature='ss')
    def youkerid_whoami_signal(self, display_name, preferred_email):
        pass

    @dbus.service.signal(INTERFACE, signature='')
    def youkerid_logout_signal(self):
        pass

    @dbus.service.signal(INTERFACE, signature='')
    def youkerid_login_fail_signal(self):
        pass



    # a dbus method which open folder by kobe
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def open_folder(self, path):
        root_path = os.path.expanduser(path)
        #if not os.path.isdir(root_path):
        #    path = os.path.dirname(path)
        if os.path.isdir(root_path):
            os.system("xdg-open '%s' &" % root_path)

#    def real_get_ip_address(self):
#        self.ip_addr = get_ip()
#        if self.ip_addr not in (False, None, {}, '', '[]', "['']"):
#            self.access_weather('ip_addr', 'kobe')

#    @dbus.service.signal(INTERFACE, signature='b')
#    def unzip_signal(self, result):
#        pass

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
#    def unzip_resource_uk_real(self, path):
#        value = unzip_resource(path)
#        self.unzip_signal(value)

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
#    def unzip_resource_uk(self, path):
#        t = threading.Thread(target = self.unzip_resource_uk_real, args=(path,))
#        t.start()

    #-----------------------------distrowatch rank-----------------------------
    def copy_distrowatch_default_conf(self):
        distrowatch_path = HOME + '/.config/ubuntukylin/kylin-assistant/distrowatch.conf'
        distrowatch_path_uk = HOME + '/.config/ubuntukylin'
        distrowatch_path_youker = HOME + '/.config/ubuntukylin/kylin-assistant'
        if not os.path.isdir(distrowatch_path_uk):
            os.makedirs(distrowatch_path_uk)
        if not os.path.isdir(distrowatch_path_youker):
            os.makedirs(distrowatch_path_youker)
        if not os.path.exists(distrowatch_path):
            if not os.path.exists(distrowatch_path):
                os.mknod(distrowatch_path)
            srcFile = '/var/lib/kylin-assistant-daemon/distrowatch.conf'
            if not os.path.exists(srcFile):
                print("error with distrowatch file")
                return
            else:
                open(distrowatch_path, "wb").write(open(srcFile, "rb").read())

#    def init_mechanize(self):
#        #copy distrowatch default file
#        self.copy_distrowatch_default_conf()
#        # Browser
#        self.br = mechanize.Browser()
#        # Cookie Jar
#        cj = cookielib.LWPCookieJar()
#        self.br.set_cookiejar(cj)

#        # Browser options
#        self.br.set_handle_equiv(True)
##        self.br.set_handle_gzip(True)
#        #self.br.set_handle_gzip(False)
#        self.br.set_handle_redirect(True)
#        self.br.set_handle_referer(True)
#        self.br.set_handle_robots(False)
#        self.br.set_handle_refresh(mechanize._http.HTTPRefreshProcessor(), max_time=1)
#        index = random.randint(0, LEN_AGENT-1)
#        # br.addheaders = [('User-agent', 'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.1) Gecko/2008071615 Ubuntu/3.0.1-1.fc9 Firefox/3.0.1'), ('Accept-Language', 'zh-CN,zh;q=0.8,en;q=0.6')]
#        self.br.addheaders = [('User-agent', 'Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.1) Gecko/2008071615 Ubuntu/3.0.1-1.fc9 Firefox/3.0.1')]

#    @dbus.service.signal(INTERFACE, signature='b')
#    def distrowatch_ubuntukylin_signal(self, uk_flag):
#        pass

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
#    def real_get_ubuntukylin_distrowatch_info(self):
#        self.ubuntukylin_dict.clear()
#        try:
#            r = self.br.open(ubuntukylin_distrowatch)
#            html = r.read()
#            soup = BeautifulSoup(html)
#        except Exception as e:
#            self.distrowatch_ubuntukylin_signal(False)
#            return
#        contents = soup.findAll(name="td", attrs={"class":"TablesTitle"})
#        p = re.compile('<[^>]+>')
##        ubuntukylin_dict = dict()
#        try:
#            result = p.sub(" ", str(contents))
#            aa = result.split('\n')
#            # print len(aa)
#            for i in range(0, len(aa)):
#                if 'Last Update:' in aa[i]:
#                    start_pos = str(aa[i]).find("Last Update:")
#                    self.ubuntukylin_dict['lastupdate'] = str(aa[i])[(start_pos+13):].rstrip()
#                elif 'OS Type:' in aa[i] and 'Based on:' in aa[i] and 'Origin:' in aa[i]:
#                    pos1 = str(aa[i]).find("OS Type:")
#                    pos2 = str(aa[i]).find("Based on:")
#                    pos3 = str(aa[i]).find("Origin:")
#                    self.ubuntukylin_dict['ostype'] = str(aa[i])[(pos1+8):pos2].replace(' ', '')
#                    self.ubuntukylin_dict['basedon'] = str(aa[i])[(pos2+9):pos3].replace(' ', '')
#                    self.ubuntukylin_dict['origin'] = str(aa[i])[(pos3+7):].replace(' ', '')
#                elif 'Architecture:' in aa[i] and 'Desktop:' in aa[i] and 'Category:' in aa[i] and 'Status:' in aa[i] and 'Popularity:' in aa[i] and 'hits per day' in aa[i]:
#                    pos1 = str(aa[i]).find("Architecture:")
#                    pos2 = str(aa[i]).find("Desktop:")
#                    pos3 = str(aa[i]).find("Category:")
#                    pos4 = str(aa[i]).find("Status:")
#                    pos5 = str(aa[i]).find("Popularity:")
#                    pos6 = str(aa[i]).find("hits per day")
#                    self.ubuntukylin_dict['architecture'] = str(aa[i])[(pos1+13):pos2].replace(' ', '')
#                    self.ubuntukylin_dict['desktop'] = str(aa[i])[(pos2+8):pos3].replace(' ', '')
#                    self.ubuntukylin_dict['category'] = str(aa[i])[(pos3+9):pos4].replace(' ', '')
#                    self.ubuntukylin_dict['status'] = str(aa[i])[(pos4+7):pos5].replace(' ', '')
#                    self.ubuntukylin_dict['popularity'] = str(aa[i])[(pos5+11):pos6].replace(' ', '')
#                elif i==6:
#                    self.ubuntukylin_dict['description'] = aa[i]
#        except Exception, e:
#            print 'exception->', e
#        self.distrowatch_ubuntukylin_signal(True)
##        return ubuntukylin_dict

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
#    def show_ubuntukylin_distrowatch_info(self):
#        return self.ubuntukylin_dict

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def get_ubuntukylin_distrowatch_info(self):
#        t = threading.Thread(target = self.real_get_ubuntukylin_distrowatch_info)
#        t.start()

#    @dbus.service.signal(INTERFACE, signature='s')
#    def distrowatch_all_signal(self, update_rate):
#        pass

#    def real_get_distrowatch_url(self):
#        self.distrowatch = []
#        update_rate = 'Last 6 months'
#        rank_list = []
#        os_list = []
#        today_hit_list = []
#        img_list = []
#        yestoday_hit_list = []
#        try:
#            r = self.br.open(distrowatch)
#            html = r.read()
#            soup = BeautifulSoup(html)
#        except Exception as e:
#            self.distrowatch_all_signal("")
#            return
#        p = re.compile('<[^>]+>')
#        spiderContents = soup.findAll(name="option", attrs={"selected":"selected"})
#        if len(spiderContents) > 1:
#            try:
#                result = p.sub("", str(spiderContents[1]))
#                update_rate = result
#            except Exception, e:
#                pass
#        else:
#            try:
#                result = p.sub("", str(spiderContents[0]))
#                update_rate = result
#            except Exception, e:
#                pass
#        spiderContents_rank = soup.findAll(name="th", attrs={"class":"phr1"})
#        spiderContents_os = soup.findAll(name="td", attrs={"class":"phr2"})
#        spiderContents_hit = soup.findAll(name="td", attrs={"class":"phr3"})
#        for i in range(0, len(spiderContents_rank)):
#            # print spiderContents_rank[i]#<th class="phr1">96</th>
#            try:
#                result = p.sub("", str(spiderContents_rank[i]))
#                rank_list.append(result)
#                # bb = spiderContents[i].findAll('img', id = 'src')
#                # print pa.sub("", str(spiderContents[i]))
#                # print bb#[<img src="images/other/alevel.png" alt="=" title="Yesterday: 155" />]
#            except Exception, e:
#                rank_list.append('')
#            try:
#                result = p.sub("", str(spiderContents_os[i]))
#                os_list.append(result)
#            except Exception, e:
#                os_list[i].append('')
#            try:
#                result = p.sub("", str(spiderContents_hit[i]))
#                today_hit_list.append(result)
#            except Exception, e:
#                today_hit_list.append('')
#            #<td class="phr3" title="Yesterday: 156">156<img src="images/other/alevel.png" alt="=" title="Yesterday: 156" /></td>
#            start_pos = str(spiderContents_hit[i]).find("src=")
#            end_pos = str(spiderContents_hit[i]).find("alt=")
#            img_path = ''
#            img_path = str(spiderContents_hit[i])[start_pos+5:end_pos]
#            img_path = img_path.replace('\"', '').replace(' ', '')
#            yestoday_hit_last_pos = str(spiderContents_hit[i]).find('Yesterday:',start_pos)
#            yestoday_hit_str = str(spiderContents_hit[i])[yestoday_hit_last_pos+10:]
#            yestoday_hit_num = 0
#            yestoday_hit_num = int(filter(str.isdigit, yestoday_hit_str))
#            img_list.append(img_path)
#            yestoday_hit_list.append(str(yestoday_hit_num))
#        for i in range(0, len(rank_list)):
#            line = "%s+%s+%s+%s+%s+%s" % (rank_list[i], os_list[i], os_list[i].replace(' ', '').replace('-', '').lower(), today_hit_list[i], img_list[i], yestoday_hit_list[i])
#            self.distrowatch.append(line)
##        print self.distrowatch
#        self.distrowatch_all_signal(update_rate)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def get_distrowatch_url(self):
#        t = threading.Thread(target = self.real_get_distrowatch_url)
#        t.start()


#    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
#    def get_distrowatch_info(self):
#        return self.distrowatch

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def get_ip_address(self):
#        t = threading.Thread(target = self.real_get_ip_address)
#        t.start()

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
#    def show_ip_address(self):
#        return self.ip_addr

    # True: has camera, False: no camera
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
#    def judge_camera(self):
#        if not hasattr(self, 'capturemode'):
#            self.capturemode = Capture()
#        return self.capturemode.judge_camera()

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def call_camera(self):
#        self.capturemode.call_camera()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def judge_power_is_exists(self):
        if os.path.isdir(POWER_PATH):
            if len(os.listdir(POWER_PATH)) == 0:
                return False
            else:
                if os.path.isdir(BATTERY_PATH):
                    return True
                else:
                    return False
        else:
            return False

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def read_battery_info(self):
        bat_dict = {}
        if not os.path.exists(BAT_FILE):
            bat_dict['error'] = 'unknown'
        else:
            try:
                fp = open(BAT_FILE)
                allLines = fp.readlines()
                fp.close()
                for eachline in allLines:
                    eachline = eachline.strip('\n')
                    if '=' in eachline:
                        tmp_list = eachline.split('=')
                        bat_dict[tmp_list[0]] = tmp_list[1]
            except Exception as e:
                bat_dict['error'] = 'unknown'
            return bat_dict

    # a dbus method which download and use kuaipan cloud conf by kobe
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def download_kysoft_cloud_conf(self):
#        self.cloudconf.download_kysoft_cloud_conf()

    # a dbus method which upload conf to kuaipan cloud by kobe
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def upload_kysoft_cloud_conf(self):
#        self.cloudconf.upload_kysoft_cloud_conf()

    # a dbus signal which download and use kuaipan cloud conf by kobe
    @dbus.service.signal(INTERFACE, signature='s')
    def download_cloud_conf_signal(self, download):
        pass

    # a dbus signal which upload conf to kuaipan cloud by kobe
    @dbus.service.signal(INTERFACE, signature='s')
    def upload_cloud_conf_signal(self, upload):
        pass

    # a dbus signal which tell widget to change titlebar postion by kobe
    @dbus.service.signal(INTERFACE, signature='s')
    def change_titlebar_position(self, position):
        pass

    #@dbus.service.method(INTERFACE, in_signature='', out_signature='')
    #def display_slide_show(self):
    #    self.wizardconf.show_slider()

    @dbus.service.method(INTERFACE, in_signature='as', out_signature='')
    def onekey_scan_function(self, mode_list):
        onekeyfunc_obj = cleaner.OneKeyClean()
        # change by kobe
        t = threading.Thread(target = onekeyfunc_obj.get_onekey_crufts, args = (self, mode_list, ))
        t.start()
        #onekeyfunc_obj.get_onekey_crufts(self, mode_list)
        #self.scan_complete_msg('onekey')

#    @dbus.service.method(INTERFACE, in_signature='as', out_signature='')
#    def mainpage_scan_function(self):
#        mainfunc_obj = cleaner.MainPage()
#        t = threading.Thread(target = mainfunc_obj.get_cache, args=(self,))
#        target_tid = mainfunc_obj.get_threadid(t)
#        self.trans_thread_infor(target_tid)
#        t.join()
#        self.scan_complete_msg('onekey')

#    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
#    def cancel_mainpage_scan(self, target_tid):
#        mainfunc_obj = cleaner.MainPage()
#        mainfunc_obj.cancel_mainpage_function(target_tid, SystemExit)

#    @dbus.service.signal(INTERFACE, signature='as')
#    def get_largefile_list(self, filelist):
#        pass

#    def tell_widget_largefile_list(self, filelist):
#        self.get_largefile_list(filelist)

#    @dbus.service.signal(INTERFACE, signature='si')
#    def get_history_number(self, flag, num):
#        pass

#    def tell_widget_history_number(self, flag, num):
#        self.get_history_number(flag, num)

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='i')
#    def scan_history_records(self, flag):
#        historyfunc_obj = cleaner.CleanTheHistory()
#        crufts = historyfunc_obj.get_history_crufts(flag)
#        figure = None
#        if isinstance(crufts, list):
#            figure = sum([int(one.split('<2_2>')[-1]) for one in crufts])
#        elif crufts in 'True':
#            figure = -99
#        elif crufts in 'No':
#            figure = -1
#        #return figure
#        self.tell_widget_history_number(flag, figure)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
#    def scan_system_history(self):
#        daemonsystem = cleaner.CleanSystemHistory()
#        url = daemonsystem.get_scan_result()
#        #self.scan_complete_msg('system')
#        #return len(url)
#        self.tell_widget_history_number("system", len(url))

    #@dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    #def scan_dash_history(self):
    #    daemondash = cleaner.CleanDashHistory()
    #    num = daemondash.get_scan_result()
    #    return num

    # the function of search the same file below path
    ### input-'path'  output-['filea<2_2>filea','fileb<2_2>fileb'....]
    #@dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    #def scan_of_same(self, path):
    #    tmp_list = self.daemonsame.get_scan_result(path)
    #    self.scan_complete_msg('same')
    #    return tmp_list

    # the function of sort the hundred files below path betown big to small
    ### input-'path'  output-['size<2_2>biggestfile<2_2>filestyle', 'size...]
    #@dbus.service.method(INTERFACE, in_signature='is', out_signature='as')
    #def scan_of_large(self, size, path):
    #    tmp_list = self.daemonlarge.get_scan_result(size, path)
    #    self.scan_complete_msg('large')
    #    return tmp_list

#    def real_scan_large_files(self, size, path):
#        filelist = self.daemonlarge.get_scan_result(size, path)
#        # start to send the over signal to UI
#        self.get_largefile_list(filelist)

#    @dbus.service.method(INTERFACE, in_signature='is', out_signature='')
#    def scan_of_large(self, size, path):
#        t = threading.Thread(target = self.real_scan_large_files, args=(size, path))
#        t.start()

    # the function of clean the cookies records
#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
#    def cookies_scan_function(self, flag):
#        cookiesfunc_obj = cleaner.CleanTheCookies(self)
#        t = threading.Thread(target = cookiesfunc_obj.get_cookie_crufts, args = (flag, self))
#        t.start()
#        #cookiesfunc_obj.get_cookie_crufts(flag, self)

#    @dbus.service.method(INTERFACE, in_signature='as', out_signature='')
#    def package_scan_function(self, mode_list):
#        packagefunc_obj = cleaner.CleanTheSpare()
#        t = threading.Thread(target = packagefunc_obj.get_all_package_crufts, args = (mode_list, self))
#        t.start()

#    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='')
#    def cache_scan_function(self, mode_list, flag):
#        cachefunc_obj = cleaner.CleanTheCache()
#        t = threading.Thread(target = cachefunc_obj.get_all_cache_crufts, args = (mode_list, flag, self))
#        t.start()

    # a dbus signal which means access weather by kobe
#    @dbus.service.signal(INTERFACE, signature='ss')
#    def access_weather(self, key, msg):
#        pass

    # a dbus signal which means scan complete by kobe
    @dbus.service.signal(INTERFACE, signature='s')
    def scan_complete(self, msg):
        pass
    
    @dbus.service.signal(INTERFACE, signature='ssss')
    def data_transmit_by_cache(self, flag0, path, flag1, size):
        pass

    @dbus.service.signal(INTERFACE, signature='i')
    def trans_thread_infor(self, target_tid):
        pass

    @dbus.service.signal(INTERFACE, signature='ssss')
    def data_transmit_by_package(self, flag, name, summary, size):
        pass

    @dbus.service.signal(INTERFACE, signature='sss')
    def data_transmit_by_cookies(self, flag, domain, num):
        pass

    #@dbus.service.signal(INTERFACE, signature='i')
    #def data_transmit_by_history(self, num):
    #    pass

    #@dbus.service.signal(INTERFACE, signature='s')
    #def browser_status_by_history(self, status):
    #    pass

#    @dbus.service.signal(INTERFACE, signature='ss')
#    def data_transmit_by_large(self, size, filepath):
#        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def cache_transmit_complete(self, flag):
        pass

    @dbus.service.signal(INTERFACE, signature='')
    def package_transmit_complete(self):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def cookies_transmit_complete(self, msg):
        pass

    #@dbus.service.signal(INTERFACE, signature='s')
    #def history_transmit_complete(self, msg):
    #    pass

    @dbus.service.signal(INTERFACE, signature='')
    def large_transmit_complete(self):
        pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def total_data_transmit(self, flag, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def display_scan_process(self, msg):
        pass

    def scan_complete_msg(self, para):
        self.scan_complete(para)

    def trans_thread_infor_msg(self, para):
        self.trans_thread_infor(para)

    def display_scan_process_msg(self, para):
        self.display_scan_process(para)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def exit(self):
        self.mainloop.quit()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_session_daemon(self):
        return "SessionDaemon"

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_system_message(self):
        return self.sysconf.get_sys_msg()

    # -------------------------beautify start here-------------------------

    # -------------------------desktop-------------------------

#    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='b')
#    def get_default_desktop_bool(self, schema, key):
#        return self.desktopconf.get_default_schema_value(schema, key)

#    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='')
#    def set_default_desktop(self, schema, key, type):
#        self.desktopconf.set_default_schema_value(schema, key, type)

    #--------------unity--------------------
    # show desktop icons
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_desktop_icons(self, flag):
        return self.desktopconf.set_show_desktop_icons(flag)

    # get show desktop icons
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_desktop_icons(self):
        return self.desktopconf.get_show_desktop_icons()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_computer(self, flag):
        return self.desktopconf.set_show_computer(flag)

    # get show homefolder
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_computer(self):
        return self.desktopconf.get_show_computer()

    # show home folder
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_homefolder(self, flag):
        return self.desktopconf.set_show_homefolder(flag)

    # get show homefolder
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_homefolder(self):
        return self.desktopconf.get_show_homefolder()

    # show network
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_network(self, flag):
        return self.desktopconf.set_show_network(flag)

    # get show network
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_network(self):
        return self.desktopconf.get_show_network()

    # show trash
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_trash(self, flag):
        return self.desktopconf.set_show_trash(flag)

    # get show trash
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_trash(self):
        return self.desktopconf.get_show_trash()

    # show devices
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_devices(self, flag):
        return self.desktopconf.set_show_devices(flag)

    # get show devices
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_devices(self):
        return self.desktopconf.get_show_devices()

    #--------------cinnamon--------------------
    # show desktop icons
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_cinnamon_desktop_icons(self, flag):
        return self.desktopconf.set_show_cinnamon_desktop_icons(flag)

    # get show desktop icons
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_cinnamon_desktop_icons(self):
        return self.desktopconf.get_show_cinnamon_desktop_icons()

    # show computer
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_cinnamon_computer(self, flag):
        return self.desktopconf.set_show_cinnamon_computer(flag)

    # get show computer
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_cinnamon_computer(self):
        return self.desktopconf.get_show_cinnamon_computer()

    # show home folder
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_cinnamon_homefolder(self, flag):
        return self.desktopconf.set_show_cinnamon_homefolder(flag)

    # get show homefolder
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_cinnamon_homefolder(self):
        return self.desktopconf.get_show_cinnamon_homefolder()

    # show network
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_cinnamon_network(self, flag):
        return self.desktopconf.set_show_cinnamon_network(flag)

    # get show network
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_cinnamon_network(self):
        return self.desktopconf.get_show_cinnamon_network()

    # show trash
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_cinnamon_trash(self, flag):
        return self.desktopconf.set_show_cinnamon_trash(flag)

    # get show trash
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_cinnamon_trash(self):
        return self.desktopconf.get_show_cinnamon_trash()

    # show devices
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_cinnamon_devices(self, flag):
        return self.desktopconf.set_show_cinnamon_devices(flag)

    # get show devices
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_cinnamon_devices(self):
        return self.desktopconf.get_show_cinnamon_devices()

    # -------------------------unity-------------------------

#    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='i')
#    def get_default_unity(self, name, key):
#        return self.unityconf.get_default_schema_value(name, key)

#    @dbus.service.method(INTERFACE, in_signature='ssi', out_signature='')
#    def set_default_unity(self, key, type, value):
#        self.unityconf.set_default_schema_value(key, type, value)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def set_default_launcher_have_showdesktopicon(self):
        self.unityconf.set_default_launcher_have_showdesktopicon()

    # set launcher auto hide mode
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_launcher_autohide(self, flag):
        return self.unityconf.set_launcher_autohide(flag)

    # get launcher auto hide mode
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_launcher_autohide(self):
        return self.unityconf.get_launcher_autohide()

    # launcher icon size 32-64
    @dbus.service.method(INTERFACE, in_signature='i', out_signature='b')
    def set_launcher_icon_size(self, size):
        return self.unityconf.set_launcher_icon_size(size)

    # get launcher icon size
    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_launcher_icon_size(self):
        return self.unityconf.get_launcher_icon_size()

    # set launcher 'show desktop' icon
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_launcher_have_showdesktopicon(self, flag):
        return self.unityconf.set_launcher_have_showdesktopicon(flag)

    # get is launcher have 'show desktop' icon
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_launcher_have_showdesktopicon(self):
        return self.unityconf.get_launcher_have_showdesktopicon()




    #add by kobe for v1.1.0
    # 透明度
    @dbus.service.method(INTERFACE, in_signature='', out_signature='d')
    def get_launcher_transparency(self):
        return self.unityconf.get_launcher_transparency()

    @dbus.service.method(INTERFACE, in_signature='d', out_signature='b')
    def set_launcher_transparency(self, opacity):
        return self.unityconf.set_launcher_transparency(opacity)

    #图标背景
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_all_launcher_icon_colourings(self):
        return self.unityconf.get_all_launcher_icon_colourings()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_launcher_icon_colouring(self):
        return self.unityconf.get_launcher_icon_colouring()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='b')
    def set_launcher_icon_colouring(self, colouring):
        return self.unityconf.set_launcher_icon_colouring(colouring)



    #Launcher position
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_all_launcher_position(self):
        return self.unityconf.get_all_launcher_position()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_launcher_position(self):
        return self.unityconf.get_current_launcher_position()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_launcher_position(self, position):
        return self.unityconf.set_launcher_position(position)

    # Dash背景模糊类型
    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_dash_blur_experimental(self):
        return self.unityconf.get_dash_blur_experimental()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='b')
    def set_dash_blur_experimental(self, blur):
        return self.unityconf.set_dash_blur_experimental(blur)

    #面板菜单透明度
    @dbus.service.method(INTERFACE, in_signature='', out_signature='d')
    def get_panel_transparency(self):
        return self.unityconf.get_panel_transparency()

    @dbus.service.method(INTERFACE, in_signature='d', out_signature='b')
    def set_panel_transparency(self, opacity):
        return self.unityconf.set_panel_transparency(opacity)


    #日期时间格式
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_all_time_format(self):
        return self.unityconf.get_all_time_format()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_time_format(self):
        return self.unityconf.get_time_format()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_time_format(self, format):
        return self.unityconf.set_time_format(format)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_seconds(self):
        return self.unityconf.get_show_seconds()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_seconds(self, flag):
        return self.unityconf.set_show_seconds(flag)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_week(self):
        return self.unityconf.get_show_week()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_week(self, flag):
        return self.unityconf.set_show_week(flag)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_date(self):
        return self.unityconf.get_show_date()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_date(self, flag):
        return self.unityconf.set_show_date(flag)

    # 电源
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_all_power_icon_policy(self):
        return self.unityconf.get_all_power_icon_policy()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_power_icon_policy(self):
        return self.unityconf.get_power_icon_policy()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_power_icon_policy(self, flag):
        return self.unityconf.set_power_icon_policy(flag)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_power_time(self):
        return self.unityconf.get_show_power_time()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_power_time(self, flag):
        return self.unityconf.set_show_power_time(flag)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_power_percentage(self):
        return self.unityconf.get_show_power_percentage()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_power_percentage(self, flag):
        return self.unityconf.set_show_power_percentage(flag)

    #-------------------------mate-------------------------
    @dbus.service.method(INTERFACE, in_signature='sb', out_signature='b')
    def set_mate_panel_autohide(self, position, flag):
        return self.unityconf.set_mate_panel_autohide(position, flag)

    # get launcher auto hide mode
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def get_mate_panel_autohide(self, position):
        return self.unityconf.get_mate_panel_autohide(position)

    @dbus.service.method(INTERFACE, in_signature='si', out_signature='b')
    def set_mate_panel_icon_size(self, position, size):
        return self.unityconf.set_mate_panel_icon_size(position, size)

    # get launcher icon size
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='i')
    def get_mate_panel_icon_size(self, position):
        return self.unityconf.get_mate_panel_icon_size(position)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_apps(self):
        return self.unityconf.get_show_apps()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_apps(self, flag):
        return self.unityconf.set_show_apps(flag)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_desktop(self):
        return self.unityconf.get_show_desktop()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_desktop(self, flag):
        return self.unityconf.set_show_desktop(flag)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_icon(self):
        return self.unityconf.get_show_icon()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_icon(self, flag):
        return self.unityconf.set_show_icon(flag)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_places(self):
        return self.unityconf.get_show_places()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_places(self, flag):
        return self.unityconf.set_show_places(flag)

    # -------------------------theme-------------------------

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='s')
    def get_default_font_string(self, schema, key):
        return self.themeconf.get_default_schema_value(schema, key)

#    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='d')
#    def get_default_font_double(self, schema, key):
#        return self.themeconf.get_default_schema_value(schema, key)

    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='b')
    def set_default_font(self, schema, key, type):
        return self.themeconf.set_default_schema_value(schema, key, type)

    # get themes
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_themes(self):
        return self.themeconf.get_themes()

    # get current theme
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_theme(self):
        return self.themeconf.get_theme()

    # set GTK theme and window theme
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_theme(self, theme):
        self.themeconf.set_theme(theme)


#----------------------------------------------------------------------------------------------------------
    @dbus.service.method(INTERFACE, in_signature='sssss', out_signature='')
    def set_ubuntukylin_default_setting_str(self, schema, title, key, type,value):
        self.themeconf.set_ubuntukylin_default_setting(schema, title, key, type,value)

    @dbus.service.method(INTERFACE, in_signature='ssssd', out_signature='')
    def set_ubuntukylin_default_setting_double(self, schema, title, key, type,value):
        self.themeconf.set_ubuntukylin_default_setting(schema, title, key, type,value)

    @dbus.service.method(INTERFACE, in_signature='ssssi', out_signature='')
    def set_ubuntukylin_default_setting_int(self, schema, title, key, type,value):
        self.themeconf.set_ubuntukylin_default_setting(schema, title, key, type,value)

    @dbus.service.method(INTERFACE, in_signature='ssssb', out_signature='')
    def set_ubuntukylin_default_setting_bool(self, schema, title, key, type,value):
        self.themeconf.set_ubuntukylin_default_setting(schema, title, key, type,value)
#----------------------------------------------------------------------------------------------------------


    # ----------------window theme----------------
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_window_themes(self):
        return self.themeconf.get_window_themes()

    # get current window theme
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_window_theme(self):
        return self.themeconf.get_current_window_theme()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_window_theme(self, theme):
        self.themeconf.set_window_theme(theme)

    # get icon themes
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_icon_themes(self):
        return self.themeconf.get_icon_themes()

    # get current icon theme
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_icon_theme(self):
        return self.themeconf.get_icon_theme()

    # set icon theme
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_icon_theme(self, theme):
        self.themeconf.set_icon_theme(theme)

    # get cursor themes
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_cursor_themes(self):
        return self.themeconf.get_cursor_themes()

    # get current cursor theme
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_cursor_theme(self):
        return self.themeconf.get_cursor_theme()

    # set cursor theme
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_cursor_theme(self, theme):
        self.themeconf.set_cursor_theme(theme)

    # get cursor size
    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_cursor_size(self):
        return self.themeconf.get_cursor_size()

    # set cursor size
    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_cursor_size(self, size):
        self.themeconf.set_cursor_size(size)

    # -------------------------fonts-------------------------

    # get font
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_font(self):
        return self.themeconf.get_font()

    # set font
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_font(self, font):
        return self.themeconf.set_font(font)

    # get desktop font
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_desktop_font(self):
        return self.themeconf.get_desktop_font()

    # set desktop font
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_desktop_font(self, font):
        return self.themeconf.set_desktop_font(font)

    # get document font
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_document_font(self):
        return self.themeconf.get_document_font()

    # set document font
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_document_font(self, font):
        return self.themeconf.set_document_font(font)

    # get monospace font
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_monospace_font(self):
        return self.themeconf.get_monospace_font()

    # set monospace font (use this func to change document font in ubuntu)
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_monospace_font(self, font):
        return self.themeconf.set_monospace_font(font)

    # get window title font
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_window_title_font(self):
        return self.themeconf.get_window_title_font()

    # set window title font
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_window_title_font(self, font):
        return self.themeconf.set_window_title_font(font)

    # get font zoom
    @dbus.service.method(INTERFACE, in_signature='', out_signature='d')
    def get_font_zoom(self):
        return self.themeconf.get_font_zoom()

    # set font zoom
    @dbus.service.method(INTERFACE, in_signature='d', out_signature='b')
    def set_font_zoom(self, zoom):
        return self.themeconf.set_font_zoom(zoom)

    # get smooth style list
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_smooth_style_list(self):
        return self.themeconf.get_all_hinting()

    # get smooth style
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_smooth_style(self):
        return self.themeconf.get_hinting()

    # set smooth style
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_smooth_style(self, value):
        return self.themeconf.set_hinting(value)

    # get antialiasing style list
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_antialiasing_style_list(self):
        return self.themeconf.get_all_antialiasing()

    # get antialiasing style
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_antialiasing_style(self):
        return self.themeconf.get_antialiasing()

    # set antialiasing style
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_antialiasing_style(self, value):
        return self.themeconf.set_antialiasing(value)


    # -------------------------scrollbars-------------------------
#    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='s')
#    def get_default_system_sring(self, schema, key):
#        return self.systemconf.get_default_schema_value(schema, key)

#    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='b')
#    def get_default_system_bool(self, schema, key):
#        return self.systemconf.get_default_schema_value(schema, key)

#    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='')
#    def set_default_system(self, schema, key, type):
#        self.systemconf.set_default_schema_value(schema, key, type)

    # set scrollbars mode overlay
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def set_scrollbars_mode_overlay(self):
        return self.systemconf.set_scrollbars_mode_overlay()

    # set scrollbars mode legacy
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def set_scrollbars_mode_legacy(self):
        return self.systemconf.set_scrollbars_mode_legacy()

    # get scrollbars mode
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_scrollbars_mode(self):
        return self.systemconf.get_scrollbars_mode()

    # -------------------------touchpad-------------------------

    # enable/disable the touchpad
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_touchpad_enable(self, flag):
        return self.systemconf.set_touchpad_enable(flag)

    # get is touchpad enable
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_touchpad_enable(self):
        return self.systemconf.get_touchpad_enable()

    # set touch scrolling use horizontal
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_touchscrolling_use_horizontal(self, flag):
        return self.systemconf.set_touchscrolling_use_horizontal(flag)

    # get is touch scrolling use horizontal
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_touchscrolling_use_horizontal(self):
        return self.systemconf.get_touchscrolling_use_horizontal()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def set_touchscrolling_mode_disabled(self):
        return self.systemconf.set_touchscrolling_mode_disabled()

    # set touch scrolling mode edge
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def set_touchscrolling_mode_edge(self):
        return self.systemconf.set_touchscrolling_mode_edge()

    # set touch scrolling mode two-finger
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def set_touchscrolling_mode_twofinger(self):
        return self.systemconf.set_touchscrolling_mode_twofinger()

    # get touchpad scrolling mode
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_touchscrolling_mode(self):
        return self.systemconf.get_touchscrolling_mode()

    @dbus.service.method(INTERFACE, in_signature='i', out_signature='b')
    def set_mate_touchscrolling_mode(self, value):
        return self.systemconf.set_mate_touchscrolling_mode(value)

    # get is touch scrolling use horizontal
    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_mate_touchscrolling_mode(self):
        return self.systemconf.get_mate_touchscrolling_mode()

    # -------------------------window-------------------------

    # set window button alignment left
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def set_window_button_align_left(self):
        self.systemconf.set_window_button_align_left()

    # set window button alignment right
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def set_window_button_align_right(self):
        self.systemconf.set_window_button_align_right()

    # get window button alignment
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_window_button_align(self):
        return self.systemconf.get_window_button_align()

    # set right click menus have icons
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_menus_have_icons(self, flag):
        return self.systemconf.set_menus_have_icons(flag)

    # get is right click menus have icons
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_menus_have_icons(self):
        return self.systemconf.get_menus_have_icons()

    # get titlebar wheel action
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_titlebar_wheel(self):
        return self.systemconf.get_titlebar_wheel()

    # get current titlebar wheel
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_titlebar_wheel(self):
        return self.systemconf.get_current_titlebar_wheel()

    # set titlebar wheel
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_titlebar_wheel(self, value):
        self.systemconf.set_titlebar_wheel(value)

    # get titlebar double
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_titlebar_options(self):
        return self.systemconf.get_titlebar_options()

    # get current titlebar double
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_titlebar_double(self):
        return self.systemconf.get_current_titlebar_double()

    # set titlebar double
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_titlebar_double(self, value):
        self.systemconf.set_titlebar_double(value)

    # get titlebar middle
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_titlebar_middle(self):
        return self.systemconf.get_titlebar_middle()

    # get current titlebar middle
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_titlebar_middle(self):
        return self.systemconf.get_current_titlebar_middle()

    # set titlebar middle
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_titlebar_middle(self, value):
        self.systemconf.set_titlebar_middle(value)

    # get titlebar right
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_titlebar_right(self):
        return self.systemconf.get_titlebar_right()

    # get current titlebar right
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_titlebar_right(self):
        return self.systemconf.get_current_titlebar_right()

    # set titlebar right
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_titlebar_right(self, value):
        self.systemconf.set_titlebar_right(value)

    # -------------------------sound-------------------------

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='s')
    def get_default_sound_string(self, schema, key):
        return self.soundconf.get_default_schema_value(schema, key)

#    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='')
#    def set_default_sound(self, schema, key, type):
#        self.soundconf.set_default_schema_value(schema, key, type)

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='')
    def set_input_feedback_sounds_enable(self, flag):
        self.soundconf.set_input_feedback_sounds_enable(flag)

    # get enable the login music
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_input_feedback_sounds_enable(self):
        return self.soundconf.get_input_feedback_sounds_enable()

    @dbus.service.method(INTERFACE, in_signature='b', out_signature='')
    def set_sound_event_enable(self, flag):
        self.soundconf.set_sound_event_enable(flag)

    # get enable the login music
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_sound_event_enable(self):
        return self.soundconf.get_sound_event_enable()

    # set enable the login music
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='')
    def set_login_music_enable(self, flag):
        self.soundconf.set_login_music_enable(flag)

    # get enable the login music
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_login_music_enable(self):
        return self.soundconf.get_login_music_enable()

    # get current sound theme
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_sound_theme(self):
        return self.soundconf.get_sound_theme()

    # set sound theme
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_sound_theme(self, theme):
        self.soundconf.set_sound_theme(theme)


    # -------------------------filemanager-------------------------
    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='b')
    def get_default_filemanager_bool(self, schema, key):
        return self.fileconf.get_default_schema_value(schema, key)

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='i')
    def get_default_filemanager_int(self, schema, key):
        return self.fileconf.get_default_schema_value(schema, key)

#    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='')
#    def set_default_filemanager(self, schema, key, type):
#        self.fileconf.set_default_schema_value(schema, key, type)

    # Set: Use the location entry instead of the pathbar
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='')
    def set_location_replace_pathbar(self, flag):
        self.fileconf.set_location_replace_pathbar(flag)

    # Get: Use the location entry instead of the pathbar
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_location_replace_pathbar(self):
        return self.fileconf.get_location_replace_pathbar()

    # Set: Automatically mount media
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='')
    def set_auto_mount_media(self, flag):
        self.fileconf.set_auto_mount_media(flag)

    # Get: Automatically mount media
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_auto_mount_media(self):
        return self.fileconf.get_auto_mount_media()

    # Set: Automatically open a folder
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='')
    def set_auto_open_folder(self, flag):
        self.fileconf.set_auto_open_folder(flag)

    # Get: Automatically open a folder
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_auto_open_folder(self):
        return self.fileconf.get_auto_open_folder()

    # Set: Prompt or autorun/autostart programs
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='')
    def set_prompt_autorun_programs(self, flag):
        self.fileconf.set_prompt_autorun_programs(flag)

    # Get: Prompt or autorun/autostart programs
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_prompt_autorun_programs(self):
        return self.fileconf.get_prompt_autorun_programs()

    # Set: Thumbnail icon size (pixels)
    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_thumbnail_icon_size(self, size):
        self.fileconf.set_thumbnail_icon_size(size)

    # Get: Thumbnail icon size (pixels)
    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_thumbnail_icon_size(self):
        return self.fileconf.get_thumbnail_icon_size()

    # Set: Thumbnail cache time (days)
    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_thumbnail_cache_time(self, size):
        self.fileconf.set_thumbnail_cache_time(size)

    # Get: Thumbnail cache time (days)
    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_thumbnail_cache_time(self):
        return self.fileconf.get_thumbnail_cache_time()

    # Set: Maximum thumbnail cache size (MB)
    @dbus.service.method(INTERFACE, in_signature='i', out_signature='')
    def set_thumbnail_cache_size(self, size):
        self.fileconf.set_thumbnail_cache_size(size)

    # Get: Maximum thumbnail cache size (MB)
    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def get_thumbnail_cache_size(self):
        return self.fileconf.get_thumbnail_cache_size()

    # ---start---------------------autostartmanage-------------------
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def get_current_autostart_status(self):
        autostartmanage.interface_get_status(self)

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def get_current_single_autostart_status(self, path):
        return autostartmanage.interface_get_single_status(self, path)
        
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def change_autostart_status(self, filename):
        autostartmanage.interface_change_status(self, filename)
    
    @dbus.service.signal(INTERFACE, signature='as')
    def autostartmanage_data_signal(self, info):
        pass
    @dbus.service.signal(INTERFACE, signature='s')
    def autostartmanage_status_signal(self, status):
        pass
    @dbus.service.signal(INTERFACE, signature='s')
    def autostartmanage_error_signal(self, error):
        pass
    # ---end---------------------autostartmanage--------------------

    #----START-------------------New-Youker-------------------------
    @dbus.service.method(INTERFACE, in_signature='a{sv}', out_signature='')
    def get_scan_result(self, mode_dic):
        # change by kobe
        t = threading.Thread(target = cleaner.interface_get_subpage_session, args = (self, mode_dic, ))
        t.start()
        #cleaner.interface_get_subpage_session(self, mode_dic)

    @dbus.service.signal(INTERFACE, signature='as')
    def subpage_data_signal(self, info):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def subpage_status_signal(self, status):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def subpage_error_signal(self, error):
        pass
    #----END---------------------New-Youker-------------------------

    @dbus.service.signal(INTERFACE, signature='b')
    def check_source_list_signal(self, result):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def start_check_source_useable(self):
        source_urllist = []
        bad_source_urllist = []
        good_source_urllist = []
        source = aptsources.sourceslist.SourcesList()
        for item in source.list:
            if item.str()[0:4] == "deb " and item.str()[0:9] != "deb cdrom":
                #print type(item.str()[4:].split()),item.str()[4:].split()
                source_list = item.str()[4:].split()
                if source_list[0].endswith("/") is True:
                    str = source_list[0] + "dists"
                else:
                    str = source_list[0] + "/dists"
                source_list[0] = str
                if len(source_list)>3:
                    urlend = source_list[2:]
                    for item in urlend:
                        urlbegin = source_list[0:2]
                        urlbegin.append(item)
                        source_urllist.append(urlbegin)
                else:
                    source_urllist.append(source_list)
        for urllist in source_urllist:
            source_url = '/'.join(urllist)
            try:
                response = urllib.request.urlopen(source_url,timeout=5)
                good_source_urllist.append(source_url)
            except Exception as e:
                print(e)
                bad_source_urllist.append(source_url)
        if good_source_urllist == []:
            self.check_source_list_signal(False)
        else:
            self.check_source_list_signal(True)

    # -------------------------monitorball-------------------------
#    # get cpu percent
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='d')
#    def get_cpu_percent(self):
#        return self.ballconf.get_cpu_percent()

#    # get total memory
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
#    def get_total_memory(self):
#        return self.ballconf.get_total_memory()

#    # get used memory
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
#    def get_used_memory(self):
#        return self.ballconf.get_used_memory()

#    # get free memory
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
#    def get_free_memory(self):
#        return self.ballconf.get_free_memory()

#    # get network flow total, return (up, down)
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
#    def get_network_flow_total(self):
#        return self.ballconf.get_network_flow_total()

    # -------------------------weather-------------------------
    # get weather information of six days
#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
#    def get_forecast_weahter(self, cityId):
#        self.weatherconf.getWeatherForecast(cityId)

    # get real forecast weather information of six days
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
#    def get_forecast_dict(self):
#        return self.weatherconf.get_forecast_dict()

    # is Unity or Cinnamon or others
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def access_current_desktop(self):
        '''env |grep XDG_CURRENT_DESKTOP'''
        desktop = None
        try:
            desktop = os.getenv('XDG_CURRENT_DESKTOP')
            if desktop is None:
                 desktop = os.getenv('XDG_SESSION_DESKTOP')
        except Exception as e:
            pass
        return desktop

    # is x86 or aarch64
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def access_current_machine(self):
        return platform.machine()

#    # is Unity or not
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
#    def judge_desktop_is_unity(self):
#        '''env |grep XDG_CURRENT_DESKTOP'''
#        desktop = ''
#        try:
#            desktop = os.getenv('XDG_CURRENT_DESKTOP')
#        except Exception as e:
#            pass
#        return desktop

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
#    def judge_desktop_is_cinnamon(self):
#        '''env |grep XDG_CURRENT_DESKTOP'''
#        desktop = ''#X-Cinnamon
#        try:
#            desktop = os.getenv('XDG_CURRENT_DESKTOP')
#        except Exception as e:
#            pass
#        return desktop


    # -------------------------pingback-------------------------
    def get_last_time(self):
        time_text = None
        usrPath = os.path.join(HOME, '.config/kylin/kylin-assistant/pingback.time')
        if os.path.exists(usrPath):
            fp = open(usrPath)
            try:
                time_text = fp.read( ).replace('\n', '')
            finally:
                fp.close()
        return time_text

    def set_last_time(self, time_text):
        abs_path = os.path.join(HOME, '.config/kylin/kylin-assistant')
        if not os.path.isdir(abs_path):
            os.makedirs(abs_path)
        usrPath = os.path.join(abs_path, 'pingback.time')
        fp = open(usrPath, 'w')
        fp.write(time_text)
        fp.close()

#    @dbus.service.signal(INTERFACE, signature='b')
#    def weather_server_pingback_signal(self, result):
#        pass

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
#    def access_server_pingback_real(self):
#            pingback = self.weatherping.access_server_pingback()
#            self.weather_server_pingback_signal(pingback)
##            return pingback

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def access_server_pingback(self):
#        t = threading.Thread(target = self.access_server_pingback_real)
#        t.start()

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
#    def submit_uk_pingback(self, cityname):
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def submit_uk_pingback(self, appVersion):
        last_time = self.get_last_time()
        now_time = datetime.datetime.now()
        if last_time in (None, ''):
#            version_youker_assistant = get_uk_version()
            distro, version_os  = get_distro_info()
            try:
                pingback = self.premoter.submit_pingback_main(distro, version_os, appVersion, '')
#                pingback = self.premoter.submit_pingback_main(distro, version_os, version_youker_assistant, cityname)
            except Exception as e:
                print('pingback failed...')
                print(e)
            if pingback:
                self. set_last_time(now_time.strftime('%Y-%m-%d'))#'%Y-%m-%d %H:%M:%S'
            return pingback
        else:
            last_time = datetime.datetime.strptime(last_time, '%Y-%m-%d')
            now_time = now_time.strftime('%Y-%m-%d')
            now_time = datetime.datetime.strptime(now_time, '%Y-%m-%d')
#            myseconds = (now_time - last_time).seconds
            delta = now_time - last_time#两个日期相隔的天数
            if (delta.days > 0):
#                version_youker_assistant = get_uk_version()
                distro, version_os  = get_distro_info()
                try:
                    pingback = self.premoter.submit_pingback_main(distro, version_os, appVersion, '')
#                    pingback = self.premoter.submit_pingback_main(distro, version_os, version_youker_assistant, cityname)
                except Exception as e:
                    print('pingback failed...')
                    print(e)
                if pingback:
                    self. set_last_time(now_time.strftime('%Y-%m-%d'))
                return pingback
            else:
                return False

#    def real_get_current_weather(self, cityId):
#        self.weather_data = self.server.get_cma_observe_weather(cityId)
#        if self.weather_data not in (False, None, {}, '', '[]', "['']"):
#            self.access_weather('weather', 'kobe')

    # get current day's weather
#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
#    def get_current_weather(self, cityId):
#        t = threading.Thread(target = self.real_get_current_weather, args = (cityId,))
#        t.setDaemon(True)
#        t.start()
#        self.weatherconf.getCurrentWeather(cityId)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
#    def get_current_weather_dict(self):
#        return self.weather_data
#        return self.weatherconf.get_current_weather_dict()

    # get current day's weather from yahoo 0.3.3
#    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='')
#    def get_current_yahoo_weather(self, latlon, cityId):
#        self.yahooconf.getYahooCurrentWeather(latlon, cityId)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
#    def get_current_yahoo_weather_dict(self):
#        return self.yahooconf.get_current_yahoo_weather_dict()

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
#    def get_yahoo_forecast_dict(self):
#        return self.yahooconf.get_yahoo_forecast_dict()
