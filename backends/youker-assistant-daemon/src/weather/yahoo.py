#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2010 Sebastian MacDonald Sebas310@gmail.com
# Copyright (C) 2010 Mehdi Rejraji mehd36@gmail.com
# Copyright (C) 2011 Vadim Rutkovsky roignac@gmail.com
# Copyright (C) 2013 Joshua Tasker jtasker@gmail.com
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

import os, sys, shutil, tempfile
import threading
import pywapi
import string
import locale
import urllib2, urllib
from urllib import urlencode
from xml.dom.minidom import parseString
import re
import json
import datetime
import calendar
from pytz import timezone
import pytz
import time
import math

class YahooWeather(threading.Thread):
    # Available conditions by yahoo condition code
    # Format: condition code: (day icon, night icon, is a severe weather condition, localized condition name)
    _YahooConditions = {
        '0' : ("weather-storm",             "weather-storm",            True,  "Tornado"),
        '1' : ("weather-storm",             "weather-storm",            True,  "Tropical storm"),
        '2' : ("weather-storm",             "weather-storm",            True,  "Hurricane"),
        '3' : ("weather-storm",             "weather-storm",            True,  "Severe thunderstorms"),
        '4' : ("weather-storm",             "weather-storm",            True,  "Thunderstorms"),
        '5' : ("weather-snow",              "weather-snow",             False, "Mixed rain and snow"),
        # Use American meaning of sleet - see http://en.wikipedia.org/wiki/Sleet
        '6' : ("weather-showers",           "weather-showers",          False, "Mixed rain and sleet"),
        '7' : ("weather-snow",              "weather-snow",             False, "Mixed snow and sleet"),
        '8' : ("weather-showers",           "weather-showers",          False, "Freezing drizzle"),
        '9' : ("weather-showers",           "weather-showers",          False, "Drizzle"),
        '10': ("weather-snow",              "weather-snow",             False, "Freezing rain"),
        '11': ("weather-showers",           "weather-showers",          False, "Showers"),
        '12': ("weather-showers",           "weather-showers",          False, "Showers"),
        '13': ("weather-snow",              "weather-snow",             False, "Snow flurries"),
        '14': ("weather-snow",              "weather-snow",             False, "Light snow showers"),
        '15': ("weather-snow",              "weather-snow",             False, "Blowing snow"),
        '16': ("weather-snow",              "weather-snow",             False, "Snow"),
        '17': ("weather-showers",           "weather-showers",          False, "Hail"),
        '18': ("weather-snow",              "weather-snow",             False, "Sleet"),
        '19': ("weather-fog",               "weather-fog",              False, "Dust"),
        '20': ("weather-fog",               "weather-fog",              False, "Foggy"),
        '21': ("weather-fog",               "weather-fog",              False, "Haze"),
        '22': ("weather-fog",               "weather-fog",              False, "Smoky"),
        '23': ("weather-clear",             "weather-clear-night",      False, "Blustery"),
        '24': ("weather-clear",             "weather-clear-night",      False, "Windy"),
        '25': ("weather-clear",             "weather-clear-night",      False, "Cold"),
        '26': ("weather-clouds",            "weather-clouds-night",     False, "Cloudy"),
        '27': ("weather-clouds",            "weather-clouds-night",     False, "Mostly cloudy"),
        '28': ("weather-clouds",            "weather-clouds-night",     False, "Mostly cloudy"),
        '29': ("weather-few-clouds",        "weather-few-clouds-night", False, "Partly cloudy"),
        '30': ("weather-few-clouds",        "weather-few-clouds-night", False, "Partly cloudy"),
        '31': ("weather-clear",             "weather-clear-night",      False, "Clear"),
        '32': ("weather-clear",             "weather-clear-night",      False, "Sunny"),
        '33': ("weather-clear",             "weather-clear-night",      False, "Fair"),
        '34': ("weather-clear",               "weather-clear-night",      False, "Fair"),
        '35': ("weather-showers-scattered",   "weather-showers-scattered",False, "Mixed rain and hail"),
        '36': ("weather-clear",               "weather-clear-night",      False, "Hot"),
        '37': ("weather-storm",               "weather-storm",            True,  "Isolated thunderstorms"),
        '38': ("weather-storm",               "weather-storm",            True,  "Scattered thunderstorms"),
        '39': ("weather-storm",               "weather-storm",            True,  "Scattered thunderstorms"),
        '40': ("weather-showers-scattered",   "weather-showers-scattered",False, "Scattered showers"),
        '41': ("weather-snow",                "weather-snow",             False, "Heavy snow"),
        '42': ("weather-snow",                "weather-snow",             False, "Scattered snow showers"),
        '43': ("weather-snow",                "weather-snow",             False, "Heavy snow"),
        '44': ("weather-few-clouds",          "weather-few-clouds-night", False, "Partly cloudy"),
        '45': ("weather-storm",               "weather-storm",            True,  "Thundershowers"),
        '46': ("weather-snow",                "weather-snow",             False, "Snow showers"),
        '47': ("weather-storm",               "weather-storm",            True,  "Isolated thundershowers"),
        #'3200': (False,                     False,                      False, "Unknown condition")
        '3200': ("weather-indicator-unknown", "weather-indicator-unknown", False, "Unknown condition"),
        '9999': ("weather-indicator-error", "weather-indicator-error", False, "Network connection unavailable")
    }

    _WeathercomConditions = _YahooConditions
    def __init__(self, sessionDaemon):
        threading.Thread.__init__(self)
        self.sessionDaemon = sessionDaemon
        self.cityName = None
        self.geonameId = None
        self.__lat = None
        self.__lon = None
        self.code = ''
        self.locale_name = ''
        self.get_locale()
        self.weatherData = {}
        self.forecastData = {}

    def get_locale(self):
        (localeName, encode) = locale.getdefaultlocale()
        if localeName is not None:
            self.locale_name = localeName.split('_')[0]
        else:
            #locale.setlocale(locale.LC_ALL, 'C') # use default (C) locale
            self.locale_name = 'en'

    def get_weather(self, id):
        #self.yahoo_result = pywapi.get_weather_from_yahoo(id, 'en')
        self.yahoo_result = pywapi.get_weather_from_yahoo(id, self.locale_name)#'CHXX0008'  2151330         10001   USNY0996
        self.get_temperature_unit()
        self.get_code()
        #fp = open("/tmp/yahoo1.txt", "w")
        #print >> fp, "--------------"
        #print >> fp, self.yahoo_result
        #fp.close()
        self.sessionDaemon.access_weather('yahoo', 'kobe')
        #print self.yahoo_result

    # Get current weather
    def getYahooCurrentWeather(self, latlon, cityId):
        cityIdStr = str(cityId)
        self.__lat = latlon[0]
        self.__lon = latlon[1]
        threading.Thread(target=self.get_weather, args=(cityIdStr,), name='YahooWeather').start()

    def get_current_yahoo_weather_dict(self):
        self.weatherData.clear()
        self.weatherData['code'] = self.code
        self.weatherData['city'] = self.get_city()
        self.weatherData['temp'] = self.get_temperature()
        #self.weatherData['humidity'] = self.get_humidity()
        #self.weatherData['pressure'] = self.get_pressure()
        #self.weatherData['visibility'] = self.get_visibility()
        self.weatherData['text'] = self.get_weather_text()
        self.weatherData['time'] = self.get_release_time()
        self.weatherData['wind'] = self.get_wind()
        (self.weatherData['sunrise'], self.weatherData['sunset']) = self.get_sun()
        #fp = open("/tmp/yahoo2.txt", "w")
        #print >> fp, "--------------"
        #print >> fp, self.weatherData
        #fp.close()
        return self.weatherData

    def get_yahoo_forecast_dict(self):
        self.forecastData.clear()
        self.forecastData['city'] = self.get_city()
        self.forecastData['time'] = self.get_release_time()
        for i in range(len(self.yahoo_result['forecasts'])):
            high = '---'
            low = '---'
            temp = '---'
            if 'code' in self.yahoo_result['forecasts'][i]:
                self.forecastData['code%s' %(str(i))] = self.yahoo_result['forecasts'][i]['code']
            if 'text' in self.yahoo_result['forecasts'][i]:
                self.forecastData['text%s' %(str(i))] = self.yahoo_result['forecasts'][i]['text']
            if 'high' in self.yahoo_result['forecasts'][i] \
                and 'low' in self.yahoo_result['forecasts'][i]:
                high = self.yahoo_result['forecasts'][i]['high']
                low = self.yahoo_result['forecasts'][i]['low']
                self.forecastData['temp%s' %(str(i))] = "%s %s ~ %s %s" % (low, self._unit, high, self._unit)
            if 'date' in self.yahoo_result['forecasts'][i]:
                self.forecastData['date%s' %(str(i))] = self.yahoo_result['forecasts'][i]['date']
            if 'day' in self.yahoo_result['forecasts'][i]:
                self.forecastData['day%s' %(str(i))] = self.yahoo_result['forecasts'][i]['day']
        return self.forecastData

    def get_code(self):
        if 'error' in self.yahoo_result:
            icon_name = '9999'
        elif 'condition' not in self.yahoo_result:
            icon_name = '3200'
        elif 'code' in self.yahoo_result['condition']:
            icon_name = self.yahoo_result['condition']['code']
        else:
            icon_name = '3200'
        self.__current_condition = self._YahooConditions.get(icon_name)
        self.code = icon_name

    def get_temperature_unit(self):
        self._unit = ""
        if 'units' in self.yahoo_result \
            and 'temperature' in self.yahoo_result['units']:
            self._unit = u"°%s" % self.yahoo_result['units']['temperature']

    def get_temperature(self):
        _value = None
        try:
            if 'temp' in self.yahoo_result['condition']:
                _value = self.yahoo_result['condition']['temp']
        except KeyError:
            pass
        if _value is None:
            _value = "---"
        return "%s %s" % (_value, self._unit)

    def get_humidity(self):
        humidity = "---"
        if 'atmosphere' in self.yahoo_result \
           and 'humidity' in self.yahoo_result['atmosphere']:
            humidity = "%s%%" % (self.yahoo_result['atmosphere']['humidity'])
        return humidity

    def get_visibility(self):
        visibility = "---"
        if 'atmosphere' in self.yahoo_result \
           and 'visibility' in self.yahoo_result['atmosphere']:
            visibility = self.yahoo_result['atmosphere']['visibility']
        return visibility

    def get_wind(self):
        wind_speed = "---"
        wind_units = "---"
        if 'wind' in self.yahoo_result \
            and 'speed' in self.yahoo_result['wind']:
            wind_speed = self.yahoo_result['wind']['speed']
        if 'units' in self.yahoo_result \
            and 'speed' in self.yahoo_result['units']:
            wind_units = self.yahoo_result['units']['speed']
        wind  = "%s %s" % (wind_speed, wind_units)
        return wind

    def get_pressure(self):
        _value = "---"
        _unit = ""
        if 'pressure' in self.yahoo_result['atmosphere'] \
           and 'pressure' in self.yahoo_result['units']:
            _value = self.yahoo_result['atmosphere']['pressure']
            _unit = self.yahoo_result['units']['pressure']
        return "%s %s" % (_value, _unit)

    def get_release_time(self):
        release = "---"
        if 'condition' in self.yahoo_result \
            and 'date' in self.yahoo_result['condition']:
            release = self.yahoo_result['condition']['date']
            if ',' in release:
                release = release.split(',')[1]
        return release

    def get_weather_text(self):
        weather = "---"
        if 'condition' in self.yahoo_result \
           and 'text' in self.yahoo_result['condition']:
            weather = self.yahoo_result['condition']['text']
        return weather

    def get_sun(self):
        sunrise = "---"
        sunset = "---"
        if 'astronomy' in self.yahoo_result:
            if 'sunrise' in self.yahoo_result['astronomy']:
                sunrise = self.yahoo_result['astronomy']['sunrise']
            if 'sunset' in self.yahoo_result['astronomy']:
                sunset = self.yahoo_result['astronomy']['sunset']
        return sunrise, sunset

    def get_city(self):
        city = "---"
        if 'location' in self.yahoo_result \
           and 'city' in self.yahoo_result['location']:
            city = self.yahoo_result['location']['city']
        return city

if __name__ == '__main__':
    pass
