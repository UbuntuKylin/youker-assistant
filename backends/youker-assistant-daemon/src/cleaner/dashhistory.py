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

import os
import sqlite3


class DashHistory():
    def __init__(self, homedir):
        filename = 'activity.sqlite'
        if homedir:
            path = '%s/.local/share/zeitgeist/' % homedir 
        else:
            path = os.path.expanduser('~/.local/share/zeitgeist/')
        self.browser_conn = sqlite3.connect(path + filename)
        self.browser_cur = self.browser_conn.cursor()

    def scan_the_records(self):
        sql_select = "SELECT COUNT(*) FROM event_view"
        self.browser_cur.execute(sql_select)
        number = self.browser_cur.fetchone()[0]
        return number

    def __del__(self):
        self.browser_cur.close()
        self.browser_conn.close()

