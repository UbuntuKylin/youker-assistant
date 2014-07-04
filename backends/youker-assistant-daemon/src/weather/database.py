#!/usr/bin/env python
# -*- coding: utf-8 -*-

### BEGIN LICENSE
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
# Author: Kobe Lee
#
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

import sqlite3
import os
import sys
reload(sys)
sys.setdefaultencoding("utf-8")
#from xdg import BaseDirectory as xdg

#CREATE_AREA = "create table area (id varchar(32) primary key, province varchar(64), \
#                city varchar(64), county varchar(64), pinyin varchar(64))"
#INSERT_AREA = "insert into area (id, province, city, county, pinyin) \
#        values('%s', '%s', '%s', '%s', '%s')"
#QUERY_AREA = "select * from area where id='%s'"
QUERY_COUNTY = "select county from area where province='%s' and city='%s'"
QUERY_ID = "select id from area where province='%s' and city='%s' and county='%s'"
#RESET_AREA = "delete from area"
#UPDATE_AREA = "update area set pinyin='%s' where id='%s'"



#CREATE_CITY = "create table city (province varchar(64), cityname varchar(64))"
#INSERT_CITY = "insert into city (province, cityname) \
#        values('%s', '%s')"
QUERY_CITY_LIST = "select cityname from city where province='%s'"


#WEATHER_CACHE_DIR = os.path.join(xdg.xdg_cache_home, "indicator-china-weather")
#CHN_CITY_LIST_FILE = os.path.join(os.path.abspath(os.path.curdir), "locations.txt")
#CITY_LIST_FILE = os.path.join(os.path.abspath(os.path.curdir), "city.txt")

#DB_PATH = os.path.join(os.path.abspath(os.path.curdir), "weather-app.db")

province_list = [
    '北京',
    '上海',
    '天津',
    '重庆',
    '黑龙江',
    '吉林',
    '辽宁',
    '内蒙古',
    '河北',
    '山西',
    '陕西',
    '山东',
    '新疆',
    '西藏',
    '青海',
    '甘肃',
    '宁夏',
    '河南',
    '江苏',
    '湖北',
    '浙江',
    '安徽',
    '福建',
    '江西',
    '湖南',
    '贵州',
    '四川',
    '广东',
    '云南',
    '广西',
    '海南',
    '香港',
    '澳门',
    '台湾'
]

class Database:

    def __init__(self):
        destFile = os.path.join('/var/lib/youker-assistant-daemon',"weather-app.db")
        if not os.path.exists(destFile):
            print "error with db file"
            return
        #工程调用
        self.connect = sqlite3.connect(destFile, check_same_thread=False)
        # 本地运行创建数据库
        # self.connect = sqlite3.connect(DB_PATH, check_same_thread=False)
        self.cursor = self.connect.cursor()

    def __del__(self):
        self.cursor.close()
        self.connect.close()

    # create table
#    def create_area_table(self):
#        self.cursor.execute(CREATE_AREA)

#    # reset table
#    def reset_area_table(self):
#        self.cursor.execute(RESET_AREA)
#        self.connect.commit()

#    def search_record(self, id):
#        self.cursor.execute(QUERY_AREA % (id))
#        res = self.cursor.fetchall()
#        if len(res) == 0:
#            return []
#        else:
#            return res
    def get_province_list(self):
        return province_list

    def search_counties(self, province, city):
        self.cursor.execute(QUERY_COUNTY % (province, city))
        res = self.cursor.fetchall()
        if len(res) == 0:
            return []
        else:
            return res

    def search_id(self, province, city, county):
        self.cursor.execute(QUERY_ID % (province, city, county))
        res = self.cursor.fetchall()
        if len(res) == 0:
            return []
        else:
            return res

    # insert data
#    def insert_area_data(self):
#        file = open(CHN_CITY_LIST_FILE, 'r')
#        for line in file.readlines():
#            if line not in (False, None, '') and ',' in line and ':' in line:
#                line_list = line.strip('\n').split(':')
#                city_list = line_list[0].split(',')
#                self.cursor.execute(INSERT_AREA % (line_list[1],city_list[0],city_list[1],city_list[2],line_list[2]))
#                self.connect.commit()
#        file.close()




    # create table
#    def create_city_table(self):
#        self.cursor.execute(CREATE_CITY)

#    # insert data
#    def insert_city_data(self):
#        file = open(CITY_LIST_FILE, 'r')
#        for line in file.readlines():
#            if line not in (False, None, '') and ',' in line:
#                line_list = line.strip('\n').split(',')
#                self.cursor.execute(INSERT_CITY % (line_list[0],line_list[1]))
#                self.connect.commit()
#        file.close()

    def search_city_table(self, province):
        self.cursor.execute(QUERY_CITY_LIST % (province))
        res = self.cursor.fetchall()
        if len(res) == 0:
            return []
        else:
            return res

if __name__ == "__main__":
    db = Database()
    # db.create_area_table()
    #db.insert_area_data()

    # db.create_city_table()
    # db.insert_city_data()



