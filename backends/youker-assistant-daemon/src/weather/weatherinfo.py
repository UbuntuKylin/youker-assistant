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

import os, sys
import pycwapi
from pm25 import *
from settings import Settings
from base import VERSION, PROJECT_ROOT_DIRECTORY
CHN_CITY_LIST_FILE = os.path.join(PROJECT_ROOT_DIRECTORY, 'weather/location.txt')

class WeatherInfo():
    def __init__(self):
        from pycwapi import get_location_from_cityid
        self.settings = Settings()
        self.settings.prepare_settings_store()
        self.city_id = self.settings.get_value("city_id")
        #print self.city_id #101250101
        self.temp = self.settings.get_value("show_temperature")
        #print self.temp #True
        self.rate = self.settings.get_value("refresh_rate")
        #print self.rate #30
        self.city_change_flag = False
        if self.rate in (False, None):
            default_value = 60
            self.settings.set_value("refresh_rate", default_value)
            self.rate = default_value
        self.weather_data={}
        self.forecast_data={}
        self.place = None
        self.pm = {}
        self.confData = {}
        self.cityList = []
        self.places = str(self.settings.get_value("places"))
        #print self.places #[['101250101', '\xe6\xb9\x96\xe5\x8d\x97,\xe9\x95\xbf\xe6\xb2\x99,\xe9\x95\xbf\xe6\xb2\x99']]
        self.placechosen = self.settings.get_value("placechosen")
        #print self.placechosen #0
        self.actualization_time = 0
        self.pm25_flag = False


        if self.city_id in (False, None, '[]', ''):
            print 'cityid is none'
        else:
            self.places = eval(self.places)
            if self.placechosen >= len(self.places):
                self.placechosen = 0
            self.place = self.places[self.placechosen]

    # Get forecast
    def get_forecast(self):
        self.forecast_data = pycwapi.get_weather_from_nmc(self.city_id, 1)
        return self.forecast_data

    # Get and set weather
    def get_set_weather(self):
        self.weather_data = pycwapi.get_weather_from_nmc(self.city_id, 0)
        if self.weather_data is not None:
            self.ptime = self.weather_data['ptime']
            return self.weather_data

    # Get PM2.5 information from website
    def get_pm_info(self):
        from pycwapi import get_location_from_cityid
        cityName = self.place[1].split(',')[2]
        self.pm = get_pm(cityName)
        return self.pm

    # Update weather and forecast
    def update_data(self):
        self.get_set_weather()
        return True
        #self.get_forecast()
        #self.get_pm_info()

    def change_city(self, cityName):
        for place in self.places:
            if (place[1] == cityName):
                self.placechosen = self.places.index(place)
                break

        if self.placechosen >= len(self.places):
            self.placechosen = 0
        self.place = self.places[self.placechosen]
        self.settings.set_value("placechosen", self.placechosen)
        self.city_id = self.places[self.placechosen][0]
        self.settings.set_value("city_id", self.city_id)
        self.update_data()

    def read_conf_data(self):
        self.confData['city_id'] = self.settings.get_value("city_id")
        self.confData['refresh_rate'] = self.settings.get_value("refresh_rate")
        self.confData['places'] = self.settings.get_value("places")
        self.confData['placechosen'] = self.settings.get_value("placechosen")
        return self.confData

    def write_conf_data(self, key, value):
        self.settings.set_value(key, value)

    def list_city_names(self, cityName):
        new_text = cityName.lower().replace(' ', '')
        self.cityList = []
        f = open(CHN_CITY_LIST_FILE, 'r')
        self.dist = {}
        for line in f.readlines():
            if new_text in line:
                keys = line.split(':')[0]
                values = line.split(':')[1]
                self.cityList.append([keys])
                self.dist[keys] = values
        return self.cityList

if __name__ == "__main__":
    wi = WeatherInfo()
    #data = wi.get_forecast();
    data = wi.get_set_weather()
    #data = wi.get_pm_info()
    print data
