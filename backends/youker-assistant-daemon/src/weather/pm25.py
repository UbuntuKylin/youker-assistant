#!/usr/bin/env python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd
# Authors: Zhang Zhao vaguedream@hotmail.com
#          Kobe Lee kobe24_lixiang@126.com
#          wyan yiwuhehe@163.com
#          binghe kylinhebing@163.com
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

import json
import os,sys
import urllib2,urllib

from base import PM25_URL, TOKEN

class Getpmdata:
	def get_url(self,cityplace):
		url = PM25_URL + cityplace + TOKEN
		return url
	def get_data(self,url):
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

#{u'pm2_5': 84, u'area': u'\u957f\u6c99', u'quality': u'\u8f7b\u5ea6\u6c61\u67d3', u'station_code': None, u'time_point': #u'2013-10-18T09:00:00Z', u'pm2_5_24h': 0, u'position_name': None, u'aqi': 122, u'primary_pollutant': None}
#{u'pm2_5': 84, u'area': u'\u957f\u6c99', u'quality': u'\u8f7b\u5ea6\u6c61\u67d3', u'station_code': None, u'time_point': #u'2013-10-18T09:00:00Z', u'pm2_5_24h': 0, u'position_name': None, u'aqi': 122, u'primary_pollutant': None}
def get_pm(cityplace):
    try:
        ob = Getpmdata()
        url = ob.get_url(cityplace)
        pmdata = ob.get_data(url)
	#return pmdata
	if pmdata.has_key('aqi') and pmdata.has_key('quality'):
		airQuality = pmdata['quality'] + ' ' +  str(pmdata['aqi'])
		return airQuality
	else:
		return "N/A"
    except Exception as e:
        print(e)
