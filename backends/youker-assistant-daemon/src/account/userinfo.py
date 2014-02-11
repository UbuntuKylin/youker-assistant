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

import time
import httplib

class UserInfo():
    def __init__(self):
        self.time = {}
        self.net = False
        #self.get_httptime()

    def time_points(self, time):
        if time >= 1 and time < 2:
            return 2
        elif time >= 2 and time < 4:
            return 4
        elif time >= 4 and time < 6:
            return 8
        elif time >= 6 and time < 10:
            return 12
        elif time >= 10 and time < 15:
            return 20
        elif time >= 15:
            return 30
        else:
            return 0

    def get_httptime(self):
        try:
            conn = httplib.HTTPConnection("www.beijing-time.org")
            conn.request("GET", "/time.asp")
            response = conn.getresponse()
            if response.status == 200:
                result = response.read()
                data = result.split("\r\n")
                #self.time = {}
                self.time['year'] = data[1][len("nyear")+1 : len(data[1])-1]
                self.time['month'] = data[2][len("nmonth")+1 : len(data[2])-1]
                self.time['day'] = data[3][len("nday")+1 : len(data[3])-1]
                self.time['hour'] = data[5][len("nhrs")+1 : len(data[5])-1]
                self.time['minute'] = data[6][len("nmin")+1 : len(data[6])-1]
                self.time['sec'] = data[7][len("nsec")+1 : len(data[7])-1]
                self.net = True
                #return self.time
        except Exception,e:
            pass
            #return False
            #print e

    # Get current date by kobe
    def get_currrent_date(self):
        self.get_httptime()
        current_date = "0000-00-00"
        #self.get_httptime()
        if self.time.has_key('year') and self.time.has_key('month') and self.time.has_key('day'):
            current_date = str(self.time['year']) + "-" + str(self.time['month']) + "-" + str(self.time['day'])
        print current_date
        return current_date


        #current_date =
        #self.get_httptime()
        #if self.time.has_key('aqi') and self.time.has_key('quality'):
            #return 0000-00-00 00:00:00
        #current_time = self.get_httptime()
        #if not current_time:
        #    return
        #current_date = str(current_time['year']) + "-" + str(current_time['month']) + "-" + str(current_time['day'])
        #return current_date

    # Get current time by kobe
    def get_current_time(self):
        current_time = "0000-00-00 00:00:00"
        #self.get_httptime()
        if self.net:
            self.net = False
            current_time = str(self.time['year']) + "-" + str(self.time['month']) + "-" + str(self.time['day']) + " " + str(self.time['hour']) + ":" + str(self.time['minute']) + ":" + str(self.time['sec'])
        print current_time
        return current_time


        #tmp_time = self.get_httptime()
        #if not tmp_time:
        #    return
        #current_time = str(tmp_time['year']) + "-" + str(tmp_time['month']) + "-" + str(tmp_time['day']) + " " + str(tmp_time['hour']) + ":" + str(tmp_time['minute']) + ":" + str(tmp_time['sec'])
        #print current_time
        #return current_time

    def login_in_forum(self, login_flag, org_date):
        current_date = self.get_currrent_date()
        if login_flag:#first login today
            return 5
        else:
            if not current_date == org_date:
                return 5
        return 0

    # Login judgment day for the first time
    #def first_login(self, yesterday_login, user_points):
    #    '''Like this: {'hour': '13', 'month': '1', 'sec': '27', 'year': '2014', 'day': '21', 'minute': '55'}'''
    #    #current_time = self.get_httptime()
    #    #if not current_time :
    #    #    return None
    #    #current_date = str(current_time['year']) + "-" + str(current_time['month']) + "-" + str(current_time['day'])
    #    current_date = self.get_currrent_date()
    #    flogin = 0
    #    if not current_date == yesterday_login:
    #        user_points += 5
    #        yesterday_login = current_date
    #        flogin = 1
    #    return (yesterday_login, user_points, flogin)

    #def login(self):
    #    current_time = self.get_httptime()
    #    if not current_time :
    #        return None
    #    login_time = int(current_time['day'])*24 + int(current_time['hour'])
    #    print login_time
    #    return login_time

    #def quit(self, login_time, user_points, today_time):
    #    current_time = self.get_httptime()
    #    if not current_time :
    #        return None
    #    quit_time = int(current_time['day'])*24 + int(current_time['hour'])
    #    add_time = quit_time - login_time
    #    #Less accumulated login time score increases
    #    user_points -= self.time_points(today_time)
    #    today_time += add_time
    #    #Increased cumulative time score increases
    #    user_points += self.time_points(today_time)
    #    #print today_time,user_points
    #    return (today_time, user_points)

if __name__ == '__main__':
    wb = UserInfo()
    wb.get_currrent_date()
    wb.get_current_time()
    #print wb.get_currrent_date()
    #wb.first_login('2014-01-16', 1000)
    #wb.login()
    #wb.quit(418, 1005, 0)
