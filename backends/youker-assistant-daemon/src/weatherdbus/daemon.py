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
import tempfile
import subprocess
import re
from subprocess import PIPE
import apt
import apt_pkg
import dbus
import dbus.service
import dbus.mainloop.glib
import pywapi
import urllib2, urllib
from urllib import urlencode
from xml.dom.minidom import parseString
import json
import locale
import threading
from weather.database import Database

INTERFACE = "com.ubuntukylin.weather"
UKPATH = "/"

class WeatherDaemon(dbus.service.Object):
    def __init__ (self, mainloop):
        self.weatherdb = Database()
        self.__cities = []
        self.__idList = []
        self.__latList = []
        self.__lonList = []
        bus_name = dbus.service.BusName(INTERFACE, bus=dbus.SessionBus())
        dbus.service.Object.__init__(self, bus_name, UKPATH)
        self.mainloop = mainloop

    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def exit(self):
        self.mainloop.quit()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_province_list(self):
        return self.weatherdb.get_province_list()

    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='as')
    def search_counties(self, province, city):
        county_list = []
        db_list = self.weatherdb.search_counties(province, city)
        for line in db_list:
            county_list.append(line[0])
        return county_list

    @dbus.service.method(INTERFACE, in_signature='sss', out_signature='s')
    def search_id(self, province, city, county):
        selected_id = self.weatherdb.search_id(province, city, county)
        selected_id = selected_id[0][0]
        return selected_id

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    def search_city_table(self, province):
        city_list = []
        db_list = self.weatherdb.search_city_table(province)
        for line in db_list:
            city_list.append(line[0])
        return city_list



    #---------------------------------------------------------yahoo------------------------
    # a dbus signal
    @dbus.service.signal(INTERFACE, signature='s')
    def trans_yahoo_city_id(self, cityId):
        pass

    def real_get_yahoo_city_id(self, geonameId):
        #""" Get Yahoo id from geonameid """
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
            self.trans_yahoo_city_id("error")
            return
        #print displayed_city_name#Beijing, Beijing, China
        woeid_result = pywapi.get_woeid_from_yahoo(displayed_city_name)
        #print woeid_result#{'count': 1, 0: (u'2151330', u'Beijing, Beijing, China')}
        if 'error' in woeid_result:
            self.trans_yahoo_city_id("error")
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
            self.trans_yahoo_city_id("error")
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
            self.trans_yahoo_city_id("error")
            return
        p = re.compile('([^_]*)_')
        m = p.match(guid_value)
        try:
            yahoo_id =  m.group(1)
        except AttributeError:
            print "No yahoo id via woeid. "
        dom.unlink()
        self.trans_yahoo_city_id(yahoo_id)
#        return yahoo_id

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def get_yahoo_city_id(self, geonameId):
        t = threading.Thread(target = self.real_get_yahoo_city_id, args = (geonameId,))
        t.start()

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

    # a dbus signal
    @dbus.service.signal(INTERFACE, signature='as')
    def trans_yahoo_cities(self, cities):
        pass

    def real_search_city_names(self, search_string):
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
        self.trans_yahoo_cities(self.__cities)
#        return self.__cities

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def search_city_names(self, search_string):
        t = threading.Thread(target = self.real_search_city_names, args = (search_string,))
        t.start()
