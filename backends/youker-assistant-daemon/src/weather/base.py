#!/usr/bin/env python
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

import os, sys

def get_parent_path(folderpath, level=1):
    parent_path = os.path.realpath(folderpath)
    while(level > 0):
        parent_path = os.path.dirname(parent_path)
        level -= 1
    return parent_path

WEATHER_URL = 'http://m.weather.com.cn/data/%s.html'
WEATHER_URL1 = 'http://www.weather.com.cn/data/sk/%s.html'
WEATHER_URL2 = 'http://www.weather.com.cn/data/cityinfo/%s.html'

PROJECT_ROOT_DIRECTORY = os.path.abspath(
    os.path.dirname(os.path.dirname(os.path.realpath(sys.argv[0]))))
DATA_PATH = os.path.join(PROJECT_ROOT_DIRECTORY, "data")
ICON_PATH = os.path.join(PROJECT_ROOT_DIRECTORY, "icons")
