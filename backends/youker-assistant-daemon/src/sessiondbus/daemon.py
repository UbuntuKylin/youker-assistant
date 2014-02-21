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

import cleaner
import pywapi
import urllib2, urllib
from urllib import urlencode
from xml.dom.minidom import parseString
import re
import json
import locale


from beautify.desktop import Desktop
from beautify.unity import Unity
from beautify.theme import Theme
from beautify.system import System
from beautify.sound import Sound
from beautify.filemanager import FileManager
from sysinfo import Sysinfo
from weather.weatherinfo import WeatherInfo
from weather.yahoo import YahooWeather#0.3.3
from account.userinfo import UserInfo
from appcollections.monitorball.monitor_ball import MonitorBall
log = logging.getLogger('SessionDaemon')
#from slider.wizard import Wizard

INTERFACE = "com.ubuntukylin.session"
UKPATH = "/"

class SessionDaemon(dbus.service.Object):
    def __init__ (self, mainloop):
        #self.wizardconf = Wizard()
        self.userconf = UserInfo()
        self.sysconf = Sysinfo()
        self.desktopconf = Desktop()
        self.unityconf = Unity()
        self.themeconf = Theme()
        self.systemconf = System()
        self.soundconf = Sound()
        self.ballconf = MonitorBall()
        self.fileconf = FileManager()
        self.weatherconf = WeatherInfo(self)
        self.yahooconf = YahooWeather(self)
        self.daemonsame = cleaner.SearchTheSame()
        self.daemonlarge = cleaner.ManageTheLarge()
        self.daemonunneed = cleaner.CleanTheUnneed()
        self.daemonoldkernel = cleaner.CleanTheOldkernel()
        self.daemoncache = cleaner.CleanTheCache()
        self.__cities = []
        self.__idList = []
        self.__latList = []
        self.__lonList = []
        bus_name = dbus.service.BusName(INTERFACE, bus=dbus.SessionBus())
        dbus.service.Object.__init__(self, bus_name, UKPATH)
        self.mainloop = mainloop

    #@dbus.service.method(INTERFACE, in_signature='', out_signature='')
    #def display_slide_show(self):
    #    self.wizardconf.show_slider()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_currrent_date(self):
        #return "0000-00-00"
        return self.userconf.get_currrent_date()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_time(self):
        #return "0000-00-00 00:00:00"
        return self.userconf.get_current_time()

    # Get score when login current day, if first, it's 5, and it not, it's 0
    @dbus.service.method(INTERFACE, in_signature='bs', out_signature='i')
    def login_in_forum_account(self, flag, date):
        #return 0
        return self.userconf.login_in_forum(flag, date)

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='s')
    def get_yahoo_city_id(self, geonameId):
        """ Get Yahoo id from geonameid """
        #print geonameId#1816670
        yahoo_id = ''
        baseurl = 'http://api.geonames.org/getJSON'
        params = {'geonameId': geonameId,
                  'username': 'kobe'}
        url = '?'.join((baseurl, urlencode(params)))
        try:
            handler = urllib2.urlopen(url)
        except urllib2.URLError:
            print "error"
        content_type = handler.info().dict['content-type']
        try:
            charset = re.search('charset\=(.*)',content_type).group(1)
        except AttributeError:
            charset = 'utf-8'
        if charset.lower() != 'utf-8':
            json_response = handler.read().decode(charset).encode('utf-8')
        else:
            json_response = handler.read()
        city = json.loads(json_response)
        handler.close()
        if 'adminName1' in city:
            displayed_city_name = u', '.join((city['name'],
                                              city['adminName1'],
                                              city['countryName']))
        elif 'name' in city:
            displayed_city_name = u', '.join((city['name'],
                                              city['countryName']))
        else:
            return
        #print displayed_city_name#Beijing, Beijing, China
        woeid_result = pywapi.get_woeid_from_yahoo(displayed_city_name)
        #print woeid_result#{'count': 1, 0: (u'2151330', u'Beijing, Beijing, China')}
        if 'error' in woeid_result:
            return
        else:
        # only look at the the first woeid result
            woeid = woeid_result[0][0]
            location_code = woeid
            #print location_code#2151330
        # Get old Yahoo id by woeid
        url = 'http://weather.yahooapis.com/forecastrss?w=%s' % woeid#http://weather.yahooapis.com/forecastrss?w=2151330
        try:
            handler = urllib2.urlopen(url)
        except urllib2.URLError:
            return
        content_type = handler.info().dict['content-type']
        try:
            charset = re.search('charset\=(.*)',content_type).group(1)
        except AttributeError:
            charset = 'utf-8'
        if charset.lower() != 'utf-8':
            xml_response = handler.read().decode(charset).encode('utf-8')
        else:
            xml_response = handler.read()
        dom = parseString(xml_response)
        handler.close()
        try:
            guid_value = dom.getElementsByTagName('guid')[0].firstChild.nodeValue
        except (AttributeError, IndexError):
            dom.unlink()
            return
        p = re.compile('([^_]*)_')
        m = p.match(guid_value)
        try:
            yahoo_id =  m.group(1)
        except AttributeError:
            print "No yahoo id via woeid. "
        dom.unlink()
        return yahoo_id

    # geonameid
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_geonameid_list(self):
        return self.__idList

    # 经度
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_longitude_list(self):
        return self.__lonList

    # 纬度
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_latitude_list(self):
        return self.__latList

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    def search_city_names(self, search_string):
        try:
            (localeName, encode) = locale.getdefaultlocale()
            if localeName is not None:
                locale_name = localeName.split('_')[0]
            else:
                locale_name = "en"
            baseurl = 'http://api.geonames.org/searchJSON'
            params = {'q': search_string, 'featureClass': 'P', 'maxRows': '10',
                        'lang': locale_name, 'username': 'kobe'}
            url = '?'.join((baseurl, urlencode(params)))
            #print url#http://api.geonames.org/searchJSON?q=beijing&lang=zh&username=kobe&maxRows=10&featureClass=P
            handler = urllib2.urlopen(url)
            content_type = handler.info().dict['content-type']
            try:
                charset = re.search('charset\=(.*)', content_type).group(1)
            except AttributeError:
                charset = 'utf-8'
            if charset.lower() != 'utf-8':
                json_response = handler.read().decode(charset).encode('utf-8')
            else:
                json_response = handler.read()
            cities = json.loads(json_response)
            handler.close()
            #print type(cities)
            self.__cities = []
            self.__idList = []
            self.__latList = []
            self.__lonList = []
            for city in cities['geonames']:
                if 'adminName2' in city:
                    displayed_city_name = u', '.join(
                        (city['name'], city['adminName1'],
                        city['adminName1'], city['countryName'])
                        )
                elif 'adminName1' in city:
                    displayed_city_name = u', '.join(
                        (city['name'], city['adminName1'], city['countryName'])
                        )
                else:
                    displayed_city_name = u', '.join((city['name'],
                                                    city['countryName']))
                self.__cities.append(displayed_city_name.encode('utf-8'))
                self.__idList.append(unicode(city['geonameId']))
                self.__latList.append(unicode(city['lat']))
                self.__lonList.append(unicode(city['lng']))
        except urllib2.URLError:
            print "error"
        return self.__cities


    @dbus.service.method(INTERFACE, in_signature='as', out_signature='')
    def onekey_scan_function(self, mode_list):
        onekeyfunc_obj = cleaner.OneKeyClean()
        onekeyfunc_obj.get_onekey_crufts(self, mode_list)
        self.scan_complete_msg('onekey')

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='i')
    def scan_history_records(self, flag):
        historyfunc_obj = cleaner.CleanTheHistory()
        crufts = historyfunc_obj.get_history_crufts(flag)
        figure = None
        if isinstance(crufts, list):
            figure = sum([int(one.split('<2_2>')[-1]) for one in crufts])
        elif crufts in 'True':
            figure = -99
        elif crufts in 'No':
            figure = -1
        return figure

    #@dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    #def history_scan_function(self, flag):
    #    historyfunc_obj = cleaner.CleanTheHistory()
    #    historyfunc_obj.new_get_history_crufts(flag, self)

    #@dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    #def scan_history_records(self):
    #    daemonhistory = cleaner.CleanTheHistory(None)
    #    tmp_list = daemonhistory.get_scan_result()
    #    self.scan_complete_msg('history')
    #    return sum([int(one.split('<2_2>')[-1]) for one in tmp_list])

    @dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    def scan_system_history(self):
        daemonsystem = cleaner.CleanSystemHistory()
        url = daemonsystem.get_scan_result()
        self.scan_complete_msg('system')
        return len(url)

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
    @dbus.service.method(INTERFACE, in_signature='is', out_signature='as')
    def scan_of_large(self, size, path):
        tmp_list = self.daemonlarge.get_scan_result(size, path)
        self.scan_complete_msg('large')
        return tmp_list

    @dbus.service.method(INTERFACE, in_signature='is', out_signature='')
    def large_scan_function(self, size, path):
        largefunc_obj = cleaner.ManageTheLarge()
        largefunc_obj.get_large_files(size, path, self)

    # the function of clean the cookies records

    #@dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    #def cookies_scan_function(self, flag):
    #    cookiesfunc_obj = cleaner.CleanTheCookies(self)
    #    crufts_list = cookiesfunc_obj.get_cookies_crufts(flag)
    #    return crufts_list

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def cookies_scan_function(self, flag):
        cookiesfunc_obj = cleaner.CleanTheCookies(self)
        cookiesfunc_obj.get_cookie_crufts(flag, self)

    # the function of scan the unneedpackages
    ### input-''   output-['pkgname<2_2>pkgsummary<2_2>installedsize', 'pkg...]
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def scan_unneed_packages(self):
    #    tmp_list = self.daemonunneed.get_scan_result()
    #    self.scan_complete_msg('unneed')
    #    return tmp_list

    # the function of scan the oldkernel
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def oldkernel_scan_function(self):
    #    oldkernelfunc_obj = cleaner.CleanTheOldkernel()
    #    crufts_list = oldkernelfunc_obj.get_oldkernel_crufts()
    #    self.scan_complete_msg('oldkernel')
    #    return crufts_list

    @dbus.service.method(INTERFACE, in_signature='as', out_signature='')
    def package_scan_function(self, mode_list):
        packagefunc_obj = cleaner.CleanTheSpare()
        try:
            packagefunc_obj.get_all_package_crufts(mode_list, self)
        except Exception, e:
            pass
        else:
            pass

    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='')
    def cache_scan_function(self, mode_list, flag):
        cachefunc_obj = cleaner.CleanTheCache()
        try:
            cachefunc_obj.get_all_cache_crufts(mode_list, flag, self)
        except Exception, e:
            pass
        else:
            pass

    # the function of scan the apt cache
    ### input-'' output-['filepath<2_2>size', 'filepath<2_2>size', 'file...]
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def scan_apt_cruft(self):
    #    #tmp_dic = self.daemoncache.get_scan_result()
    #    tmp_dic = self.daemoncache.get_cache_crufts()
    #    self.scan_complete_msg('apt')
    #    return tmp_dic['apt'].split('<1_1>')

    # the function of scan the softwarecenter cache
    ### input-'' output-['filepath<2_2>size', 'filepath<2_2>size', 'file...]
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def scan_softwarecenter_cruft(self):
    #    #tmp_dic = self.daemoncache.get_scan_result()
    #    tmp_dic = self.daemoncache.get_cache_crufts()
    #    self.scan_complete_msg('softwarecenter')
    #    return tmp_dic['softwarecenter'].split('<1_1>')

    # a dbus signal which means access weather by kobe
    @dbus.service.signal(INTERFACE, signature='ss')
    def access_weather(self, key, msg):
        pass

    # a dbus signal which means scan complete by kobe
    @dbus.service.signal(INTERFACE, signature='s')
    def scan_complete(self, msg):
        pass
    
    @dbus.service.signal(INTERFACE, signature='ssss')
    def data_transmit_by_cache(self, flag0, path, flag1, size):
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

    @dbus.service.signal(INTERFACE, signature='ss')
    def data_transmit_by_large(self, size, filepath):
        pass

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

    #@dbus.service.signal(INTERFACE, signature='s')
    #def deb_exists_firefox(self, msg):
    #    pass

    #@dbus.service.signal(INTERFACE, signature='s')
    #def deb_exists_chromium(self, msg):
    #    pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def total_data_transmit(self, flag, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def display_scan_process(self, msg):
        pass

    def scan_complete_msg(self, para):
        self.scan_complete(para)

    #def deb_exists_firefox_msg(self, para):
    #    self.deb_exists_firefox(para)

    #def deb_exists_chromium_msg(self, para):
    #    self.deb_exists_chromium(para)

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

    #@dbus.service.signal(INTERFACE, signature='as')
    #def get_speed(self, speed):
    #    pass

    #def get_network_speed(self, speed):
    #    self.get_speed(speed)

    # -------------------------beautify start here-------------------------

    # -------------------------desktop-------------------------

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='b')
    def get_default_desktop_bool(self, schema, key):
        return self.desktopconf.get_default_schema_value(schema, key)

    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='')
    def set_default_desktop(self, schema, key, type):
        self.desktopconf.set_default_schema_value(schema, key, type)


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

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='i')
    def get_default_unity(self, name, key):
        return self.unityconf.get_default_schema_value(name, key)

    @dbus.service.method(INTERFACE, in_signature='ssi', out_signature='')
    def set_default_unity(self, key, type, value):
        self.unityconf.set_default_schema_value(key, type, value)

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

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='s')
    def get_default_font_sring(self, schema, key):
        return self.themeconf.get_default_schema_value(schema, key)

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='d')
    def get_default_font_double(self, schema, key):
        return self.themeconf.get_default_schema_value(schema, key)

    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='')
    def set_default_font(self, schema, key, type):
        self.themeconf.set_default_schema_value(schema, key, type)

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
    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='s')
    def get_default_system_sring(self, schema, key):
        return self.systemconf.get_default_schema_value(schema, key)

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='b')
    def get_default_system_bool(self, schema, key):
        return self.systemconf.get_default_schema_value(schema, key)

    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='')
    def set_default_system(self, schema, key, type):
        self.systemconf.set_default_schema_value(schema, key, type)

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

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='s')
    def get_default_sound_string(self, schema, key):
        return self.soundconf.get_default_schema_value(schema, key)

    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='')
    def set_default_sound(self, schema, key, type):
        self.soundconf.set_default_schema_value(schema, key, type)

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
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='')
    #def get_network_flow(self):
    #    speed_network = self.ballconf.get_network_flow()
    #    self.get_network_speed(speed_network)

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
    #    return self.weatherconf.getWeatherForecast(cityId)

    # get current day's weather
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def get_current_weather(self, cityId):
        self.weatherconf.getCurrentWeather(cityId)

    # get current day's weather from yahoo 0.3.3
    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='')
    def get_current_yahoo_weather(self, latlon, cityId):
        self.yahooconf.getYahooCurrentWeather(latlon, cityId)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_current_weather_dict(self):
        return self.weatherconf.get_current_weather_dict()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_current_yahoo_weather_dict(self):
        return self.yahooconf.get_current_yahoo_weather_dict()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_yahoo_forecast_dict(self):
        return self.yahooconf.get_yahoo_forecast_dict()

    # get current PM2.5
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def get_current_pm25(self, cityId):
        self.weatherconf.getPM25Info(cityId)

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
