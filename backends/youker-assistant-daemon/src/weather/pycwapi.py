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

"""
Fetches weather reports from Chinese Weather
"""

import os, sys
import urllib2, urllib
import json

from base import PROJECT_ROOT_DIRECTORY, WEATHER_URL, WEATHER_URL1, WEATHER_URL2

#CHN_CITY_LIST_FILE = os.path.join(PROJECT_ROOT_DIRECTORY, 'src/location.txt')
CHN_CITY_LIST_FILE = '/usr/lib/python2.7/dist-packages/youker-assistant-daemon/src/weather/location.txt'

def read_from_url(url):
    # returns weather info by json_string
    request = urllib2.Request(url, headers={'User-Agent' : 'Magic Browser'})
    f = urllib2.urlopen(request)
    json_string = f.read()
    f.close()
    return json_string

def get_forecast_weather_from_nmc(location_id):
    """
    Fetches forecast weather report from NMC

    Parameters:
      location_id: City ID for request weather

    Returns:
      weather_data: a string of weather data that exists in Json feed.
    """

    weather_data = []
    url = WEATHER_URL % (location_id)
    json_string = read_from_url(url)
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
        tmp = key + '<1_1>' + parsed_json['weatherinfo'][key]
        weather_data = weather_data + '<2_2>' + tmp
    return weather_data

def get_weather_from_nmc(location_id, method = 0):
    """
    Fetches weather report from NMC
    
    Parameters:
      location_id: City ID for request weather
      method: 'simple' 0 or 'complex' 1
    
    Returns:
      weather_data: a dictionary of weather data that exists in Json feed.
    """
    weather_data = {}
    if method == 0:
        url1 = WEATHER_URL1 % (location_id)
        url2 = WEATHER_URL2 % (location_id)
        json_string1 = read_from_url(url1)
        json_string2 = read_from_url(url2)
        parsed_json1 = json.loads(json_string1)
        parsed_json2 = json.loads(json_string2)
        for key in ('city', 'temp', 'SD', 'WD', 'WS', 'time'):
            weather_data[key] = parsed_json1['weatherinfo'][key]
        for key in ('weather', 'temp1', 'temp2', 'img1', 'img2', 'ptime'):
            weather_data[key] = parsed_json2['weatherinfo'][key]
    elif method == 1:
        url = WEATHER_URL % (location_id)
        json_string = read_from_url(url)
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
            weather_data[key] = parsed_json['weatherinfo'][key]
    else:
        print "Error,choose method for 0 or 1"
        exit(1)
    return weather_data

def get_location_from_cityid(cityid):
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

def get_id_from_cityname(cityName):
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
    weatherinfo = get_weather_from_nmc('101281601', 0)
    cities = get_cities_from_localfile('长沙')
    download_icon_from_nmc('d0.gif', 'd')
