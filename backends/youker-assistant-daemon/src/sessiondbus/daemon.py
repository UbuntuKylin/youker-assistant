#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
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
from gi.repository import GObject

import time

import cleaner

from beautify.desktop import Desktop
from beautify.unity import Unity
from beautify.theme import Theme
from beautify.system import System
from beautify.sound import Sound
from sysinfo import Sysinfo
from weather.weatherinfo import WeatherInfo
from appcollections.monitorball.monitor_ball import MonitorBall
log = logging.getLogger('SessionDaemon')

INTERFACE = "com.ubuntukylin.IhuSession"
UKPATH = "/"
UK_ACTION_YOUKER = 'com.ubuntukylin_tools.daemon.youker'
class SessionDaemon(dbus.service.Object):
    def __init__ (self, mainloop):
        self.sysconf = Sysinfo()
        self.desktopconf = Desktop()
        self.unityconf = Unity()
        self.themeconf = Theme()
        self.systemconf = System()
        self.soundconf = Sound()
        self.ballconf = MonitorBall()
        self.weatherconf = WeatherInfo(self)
        self.daemonsame = cleaner.SearchTheSame()
        self.daemonlarge = cleaner.ManageTheLarge()
        self.daemonunneed = cleaner.CleanTheUnneed()
        self.daemonoldkernel = cleaner.CleanTheOldkernel()
        self.daemoncache = cleaner.CleanTheCache()
        self.daemonclean = cleaner.FunctionOfClean(self)
        self.daemononekey = cleaner.OneKeyClean()

        bus_name = dbus.service.BusName(INTERFACE, bus=dbus.SessionBus())
        dbus.service.Object.__init__(self, bus_name, UKPATH)
        self.mainloop = mainloop

    @dbus.service.method(INTERFACE, in_signature='as', out_signature='')
    def onekey_scan_function(self, mode_list):
        daemononekey = cleaner.OneKeyClean()
        total_dic = daemononekey.get_onekey_crufts(self, mode_list)
        self.scan_complete_msg('onekey')

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='i')
    def history_scan_funciton(self, flag):
        daemonhistory = cleaner.CleanTheHistory(None)
        crufts_list = daemonhistory.get_history_crufts(flag)
        figure = None
        if crufts_list[0] in 'No':
            figure = -1
        elif crufts_list[0] in 'True':
            figure = -99
        else:
            figure = sum([int(one.split('<2_2>')[-1]) for one in crufts_list])
        return figure

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def scan_history_records(self):
        daemonhistory = cleaner.CleanTheHistory(None)
        tmp_list = daemonhistory.get_scan_result()
        self.scan_complete_msg('history')
        return sum([int(one.split('<2_2>')[-1]) for one in tmp_list])

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def scan_system_history(self):
        daemonsystem = cleaner.CleanSystemHistory()
        url = daemonsystem.get_scan_result()
        self.scan_complete_msg('system')
        return len(url)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def scan_dash_history(self):
        daemondash = cleaner.CleanDashHistory()
        num = daemondash.get_scan_result()
        return num

    # the function of search the same file below path
    ### input-'path'  output-['filea<2_2>filea','fileb<2_2>fileb'....]
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    def scan_of_same(self, path):
        tmp_list = self.daemonsame.get_scan_result(path)
        self.scan_complete_msg('same')
        return tmp_list

    # the function of sort the hundred files below path betown big to small
    ### input-'path'  output-['size<2_2>biggestfile<2_2>filestyle', 'size...]
    @dbus.service.method(INTERFACE, in_signature='is', out_signature='as')
    def scan_of_large(self, size, path):
        tmp_list = self.daemonlarge.get_scan_result(size, path)
        self.scan_complete_msg('large')
        return tmp_list
    # the function of clean the cookies records
    ### input-''   output-['domain<2_2>number', 'dom...]
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def scan_cookies_records(self):
        daemoncookies = cleaner.CleanTheCookies(self)
        tmp_list = daemoncookies.get_scan_result()
        self.scan_complete_msg('cookies')
        return tmp_list

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    def cookies_scan_function(self, flag):
        daemoncookies = cleaner.CleanTheCookies(self)
        crufts_list = daemoncookies.get_cookies_crufts(flag)
        return crufts_list
    # the function of scan the unneedpackages
    ### input-''   output-['pkgname<2_2>pkgsummary<2_2>installedsize', 'pkg...]
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def scan_unneed_packages(self):
        tmp_list = self.daemonunneed.get_scan_result()
        self.scan_complete_msg('unneed')
        return tmp_list
    # the function of scan the oldkernel
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def oldkernel_scan_function(self):
        crufts_list = self.daemonoldkernel.get_oldkernel_crufts()
        self.scan_complete_msg('oldkernel')
        return crufts_list
    # the function of scan the apt cache
    ### input-'' output-['filepath<2_2>size', 'filepath<2_2>size', 'file...]
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def scan_apt_cruft(self):
        #tmp_dic = self.daemoncache.get_scan_result()
        tmp_dic = self.daemoncache.get_cache_crufts()
        self.scan_complete_msg('apt')
        return tmp_dic['apt'].split('<1_1>')
    # the function of scan the softwarecenter cache
    ### input-'' output-['filepath<2_2>size', 'filepath<2_2>size', 'file...]
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def scan_softwarecenter_cruft(self):
        #tmp_dic = self.daemoncache.get_scan_result()
        tmp_dic = self.daemoncache.get_cache_crufts()
        self.scan_complete_msg('softwarecenter')
        return tmp_dic['softwarecenter'].split('<1_1>')

    # a dbus signal which means access weather by kobe
    @dbus.service.signal(INTERFACE, signature='ss')
    def access_weather(self, key, msg):
        pass

    #def access_weather_msg(self, para):
    #    self.access_weather(para)

    # a dbus signal which means scan complete by kobe
    @dbus.service.signal(INTERFACE, signature='s')
    def scan_complete(self, msg):
        pass
    
    @dbus.service.signal(INTERFACE, signature='s')
    def deb_exists_firefox(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def deb_exists_chromium(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def display_scan_process(self, msg):
        pass

    def scan_complete_msg(self, para):
        self.scan_complete(para)

    def deb_exists_firefox_msg(self, para):
        self.deb_exists_firefox(para)

    def deb_exists_chromium_msg(self, para):
        self.deb_exists_chromium(para)

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

    @dbus.service.signal(INTERFACE, signature='as')
    def get_speed(self, speed):
        pass

    def get_network_speed(self, speed):
        self.get_speed(speed)

    # -------------------------beautify start here-------------------------

    # -------------------------desktop-------------------------

    # show desktop icons
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_show_desktop_icons(self, flag):
        return self.desktopconf.set_show_desktop_icons(flag)

    # get show desktop icons
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_show_desktop_icons(self):
        return self.desktopconf.get_show_desktop_icons()

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

    # -------------------------unity-------------------------

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

    # -------------------------theme-------------------------

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

    # -------------------------scrollbars-------------------------

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

    # set touch scrolling use horizontal
    @dbus.service.method(INTERFACE, in_signature='b', out_signature='b')
    def set_touchscrolling_use_horizontal(self, flag):
        return self.systemconf.set_touchscrolling_use_horizontal(flag)

    # get is touch scrolling use horizontal
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def get_touchscrolling_use_horizontal(self):
        return self.systemconf.get_touchscrolling_use_horizontal()

    # -------------------------window-------------------------

    # set window button alignment left
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def set_window_button_align_left(self):
        return self.systemconf.set_window_button_align_left()

    # set window button alignment right
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def set_window_button_align_right(self):
        return self.systemconf.set_window_button_align_right()

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

    # -------------------------sound-------------------------

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

    # -------------------------beautify end here-------------------------

    # -------------------------monitorball-------------------------
    # get cpu percent
    @dbus.service.method(INTERFACE, in_signature='', out_signature='d')
    def get_cpu_percent(self):
        return self.ballconf.get_cpu_percent()

    # get total memory
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_total_memory(self):
        return self.ballconf.get_total_memory()

    # get used memory
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_used_memory(self):
        return self.ballconf.get_used_memory()

    # get free memory
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_free_memory(self):
        return self.ballconf.get_free_memory()

    # get network flow total, return (up, down)
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_network_flow_total(self):
        return self.ballconf.get_network_flow_total()

    # get network flow, return (up, down)
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def get_network_flow(self):
        speed_network = self.ballconf.get_network_flow()
        self.get_network_speed(speed_network)

    # -------------------------weather-------------------------
    # get weather information of six days
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def get_forecast_weahter(self, cityId):
        self.weatherconf.getWeatherForecast(cityId)

    # get real forecast weather information of six days
    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_forecast_dict(self):
        return self.weatherconf.get_forecast_dict()

    #@dbus.service.method(INTERFACE, in_signature='s', out_signature='a{sv}')
    #def get_forecast_weahter(self, cityId):
        #return self.weatherconf.getWeatherForecast(cityId)

    # get current day's weather
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def get_current_weather(self, cityId):
        self.weatherconf.getCurrentWeather(cityId)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_current_weather_dict(self):
        return self.weatherconf.get_current_weather_dict()

    # get current day's weather
    #@dbus.service.method(INTERFACE, in_signature='s', out_signature='a{sv}')
    #def get_current_weather(self, cityId):
    #    return self.weatherconf.getCurrentWeather(cityId)

    # get current PM2.5
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def get_current_pm25(self, cityId):
        self.weatherconf.getPM25Info(cityId)
        #return self.weatherconf.(cityId)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_pm25_str(self):
        return self.weatherconf.get_pm25_str()

    # update weather data
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def update_weather_data(self, cityId):
        return self.weatherconf.updateCurrentWeather(cityId)

    # get cityid from citynamegetPM25Info
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='s')
    def get_city_id(self, cityName):
        return self.weatherconf.getCityId(cityName)

    # change city name
    #@dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    #def change_select_city_name(self, cityName):
    #    self.weatherconf.change_city(cityName)

    # read conf data
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    #def read_conf_data(self):
    #    return self.weatherconf.read_conf_data()

    # write conf data
    #@dbus.service.method(INTERFACE, in_signature='ss', out_signature='')
    #def write_conf_data(self, key, value):
    #    self.weatherconf.write_conf_data(key, value)
