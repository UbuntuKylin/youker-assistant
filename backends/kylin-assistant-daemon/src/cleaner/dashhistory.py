#!/usr/bin/python3
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

import os
import subprocess
import sqlite3


class DashHistory():
    def __init__(self, homedir):
        self.full_path = ''
        if homedir:
            path = '%s/.local/share/zeitgeist/' % homedir 
        else:
            path = os.path.expanduser('~/.local/share/zeitgeist/')
        self.full_path = path + 'activity.sqlite'
        if not os.path.exists(self.full_path):
            raise Exception("Dashhistory: path did not exist")

    def scan_the_records(self):
        self.browser_conn = sqlite3.connect(self.full_path)
        self.browser_cur = self.browser_conn.cursor()

        sql_select = "SELECT COUNT(*) FROM event_view"
        self.browser_cur.execute(sql_select)
        number = self.browser_cur.fetchone()[0]

        self.browser_cur.close()
        self.browser_conn.close()
        return number

    def clean_the_records(self):
        tmp_path = self.full_path
        user = tmp_path.split('/')[2]
        os.remove(tmp_path)
        cmd = "su - %s -c 'zeitgeist-daemon --replace & >& /dev/null'" % user
        (status, output) = subprocess.getstatusoutput(cmd)
        return


