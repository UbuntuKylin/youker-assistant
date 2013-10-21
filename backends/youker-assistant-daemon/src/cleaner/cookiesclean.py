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

import os.path
import sqlite3

from common import get_mozilla_path


class CookiesClean():
    def __init__(self, homedir):
        self.filename = 'cookies.sqlite'
        self.path = get_mozilla_path(homedir)

    def scan_the_records(self):
        save = []
        if os.path.exists(self.path):
            scan_browser_conn = sqlite3.connect(self.path + self.filename)
            scan_browser_cur = scan_browser_conn.cursor()
            sql_select = 'SELECT baseDomain, count(*) FROM moz_cookies GROUP BY baseDomain'
            scan_browser_cur.execute(sql_select)
            for eachvisit in scan_browser_cur.fetchall():
                tmp = list(eachvisit)
                tmp[-1] = str(tmp[-1])
                tmp_str = '<2_2>'.join(tmp)
                save.append(tmp_str)
            scan_browser_cur.close()
            scan_browser_conn.close()
        return save

    def clean_the_records(self, domain):
        if os.path.exists(self.path):
            clean_browser_conn = sqlite3.connect(self.path + self.filename)
            clean_browser_cur = clean_browser_conn.cursor()
            sql_exist = "SELECT * FROM moz_cookies WHERE baseDomain='%s'" % domain
            clean_browser_cur.execute(sql_exist)
            if clean_browser_cur.fetchone():
                sql_delete = "DELETE FROM moz_cookies WHERE baseDomain='%s'" % domain
                clean_browser_cur.execute(sql_delete)
                clean_browser_conn.commit()
            clean_browser_cur.close()
            clean_browser_conn.close()
            return True
        else:
            return False

if __name__ == "__main__":
    objc = CookiesClean()
    objc.scan_the_records()
    #objc.clean_the_records(['1188.com'])
    del objc
