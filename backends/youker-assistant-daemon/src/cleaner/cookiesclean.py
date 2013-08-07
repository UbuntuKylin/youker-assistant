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

import sqlite3

from common import get_mozilla_path


class CookiesClean():
    def __init__(self):
        self.filename = 'cookies.sqlite'
        path = get_mozilla_path()
        self.browser_conn = sqlite3.connect(path + self.filename)
        self.browser_cur = self.browser_conn.cursor()


    def scan_the_records(self):
        save = []
        sql_select = 'SELECT baseDomain, count(*) FROM moz_cookies GROUP BY baseDomain'
        self.browser_cur.execute(sql_select)
        for eachvisit in self.browser_cur.fetchall():
            #self.save.append(eachvisit)
            tmp = list(eachvisit)
            tmp[-1] = str(tmp[-1])
            tmp_str = '<2_2>'.join(tmp)
            save.append(tmp_str)
        #print save
        return save

    def clean_the_records(self, domain):
        sql_exist = "SELECT * FROM moz_cookies WHERE baseDomain='%s'" % domain
        self.browser_cur.execute(sql_exist)
        if self.browser_cur.fetchone():
            sql_delete = "DELETE FROM moz_cookies WHERE baseDomain='%s'" % domain
            self.browser_cur.execute(sql_delete)
            self.browser_conn.commit()
            return True
        else:
            return False

    def __del__(self):
        self.browser_cur.close()
        self.browser_conn.close()

if __name__ == "__main__":
    objc = CookiesClean()
    objc.scan_the_records()
    #objc.clean_the_records(['1188.com'])
    del objc
