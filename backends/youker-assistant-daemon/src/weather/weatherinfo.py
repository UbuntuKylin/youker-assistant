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
import threading
import urllib2, urllib
import json
from base import PROJECT_ROOT_DIRECTORY, PROJECT_ROOT_DIRECTORY, WEATHER_URL, WEATHER_URL1, WEATHER_URL2, PM25_URL, TOKEN

CHN_CITY_LIST_FILE = '/usr/lib/python2.7/dist-packages/youker-assistant-daemon/src/weather/location.txt'

class Getpmdata:
    def get_url(self, cityplace):
        url = PM25_URL + cityplace + TOKEN
        return url

    def get_data(self, url):
        request = urllib2.Request(url, headers={'User-Agent ' : 'Magic Browser'})
        f = urllib2.urlopen(request)
        json_data = f.read()
        f.close()
        python_data = json.loads(json_data)
        if isinstance(python_data,dict):
            python_need_data = python_data
        else:
            python_need_data = python_data[-1]
        return python_need_data

class WeatherInfo(threading.Thread):
    def __init__(self, sessionDaemon):
        threading.Thread.__init__(self)
        self.sessionDaemon = sessionDaemon
        self.weatherData={}
        self.forecastData={}
        self.pmData = ''

    # Get weahter forecast
    def getWeatherForecast(self, cityId):
        cityIdStr = str(cityId)
        self.location_id = cityIdStr
        threading.Thread(target=self.get_weather_from_nmc, args=(1,), name='Forecast').start()

    # Get current weather
    def getCurrentWeather(self, cityId):
        cityIdStr = str(cityId)
        self.location_id = cityIdStr
        threading.Thread(target=self.get_weather_from_nmc, args=(0,), name='CurrrentWeather').start()

    # Get PM2.5 information from website
    def getPM25Info(self, cityId):
        cityIdStr = str(cityId)
        cityName = self.get_location_from_cityid(cityIdStr)
        cityName = cityName.split(',')[2]
        threading.Thread(target=self.get_pm, args=(cityName,), name='PM25').start()

    # Update weather and forecast
    def updateCurrentWeather(self, cityId):
        self.getCurrentWeather(cityId)
        return True

    def getCityId(self, cityName):
        cityNameStr = str(cityName)
        return self.get_id_from_cityname(cityNameStr)

    def read_from_url(self, url):
        # returns weather info by json_string
        request = urllib2.Request(url, headers={'User-Agent' : 'Magic Browser'})
        f = urllib2.urlopen(request)
        json_string = f.read()
        f.close()
        return json_string

    def get_pm(self, cityplace):
        try:
            ob = Getpmdata()
            url = ob.get_url(cityplace)
            pmdata = ob.get_data(url)
            #return pmdata
            if pmdata.has_key('aqi') and pmdata.has_key('quality'):
                self.pmData = pmdata['quality'] + ' ' +  str(pmdata['aqi'])
            else:
                self.pmData = "N/A"
            self.sessionDaemon.access_weather('pm25', 'kobe')
        except Exception as e:
            self.pmData = "N/A"

    #according to get_pm get pm25 data when it run over.
    def get_pm25_str(self):
        return self.pmData

    def get_weather_from_nmc(self, method = 0):
        """
        Fetches weather report from NMC

        Parameters:
          location_id: City ID for request weather
          method: 'simple' 0 or 'complex' 1

        Returns:
          weather_data: a dictionary of weather data that exists in Json feed.
        """
        if method == 0:
            url1 = WEATHER_URL1 % (self.location_id)
            url2 = WEATHER_URL2 % (self.location_id)
            json_string1 = self.read_from_url(url1)
            json_string2 = self.read_from_url(url2)
            parsed_json1 = json.loads(json_string1)
            parsed_json2 = json.loads(json_string2)
            for key in ('city', 'temp', 'SD', 'WD', 'WS', 'time'):
                self.weatherData[key] = parsed_json1['weatherinfo'][key]
            for key in ('weather', 'temp1', 'temp2', 'img1', 'img2', 'ptime'):
                self.weatherData[key] = parsed_json2['weatherinfo'][key]
            self.sessionDaemon.access_weather('weather', 'kobe')
        elif method == 1:
            url = WEATHER_URL % (self.location_id)
            json_string = self.read_from_url(url)
            parsed_json = json.loads(json_string)
            tp_forecast = ('city', 'date_y', 'fchh', 'temp1', 'temp2', 'temp3', 'temp4', 'temp5', 'temp6', \
            'weather1', 'weather2', 'weather3', 'weather4', 'weather5', 'weather6', \
            'wind1', 'wind2', 'wind3', 'wind4', 'wind5', 'wind6', \
            'img1', 'img2', 'img3', 'img4', 'img5', 'img6', 'img7', 'img8', 'img9', 'img10', 'img11', 'img12', 'img_single', \
            'img_title1', 'img_title2', 'img_title3', 'img_title4', 'img_title5', 'img_title6', \
            'img_title7', 'img_title8', 'img_title9', 'img_title10', 'img_title11', 'img_title12', 'img_title_single', \
            'wind1', 'wind2', 'wind3', 'wind4', 'wind5', 'wind6', \
            'fx1', 'fx2', 'fl1', 'fl2', 'fl3', 'fl4', 'fl5', 'fl6', \
            'index', 'index_d', 'index48', 'index48_d', 'index_uv', 'index_xc', 'index_tr', 'index_co', 'index_cl', 'index_ls', 'index_ag')
            for key in tp_forecast:
                self.forecastData[key] = parsed_json['weatherinfo'][key]
            self.sessionDaemon.access_weather('forecast', 'kobe')
        else:
            print "Error,choose method for 0 or 1"
            exit(1)

    #according to get_weather_from_nmc get forecast data when it run over.
    def get_current_weather_dict(self):
        return self.weatherData

    #according to get_weather_from_nmc get forecast data when it run over.
    def get_forecast_dict(self):
        return self.forecastData

    def get_location_from_cityid(self, cityid):
        """
        returns city location by search cityid, added by kobe
        """
        location = ''
        f = open(CHN_CITY_LIST_FILE, 'r')
        for line in f.readlines():
            if cityid in line:
                location = line.split(':')[0]
                break
        return location

    def get_id_from_cityname(self, cityName):
        cityId = ''
        f = open(CHN_CITY_LIST_FILE, 'r')
        for line in f.readlines():
            location = line.split(':')[0]
            location = location.split(',')[2]
            if (cityName == location):
                cityId = line.split(':')[1]
                break
        f.close()
        return cityId

if __name__ == "__main__":
    pass
