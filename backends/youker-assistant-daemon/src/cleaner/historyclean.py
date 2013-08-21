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


class HistoryClean():
    def __init__(self):
        self.filename = 'places.sqlite'
        homedir = ''
        path = get_mozilla_path(homedir)
        self.browser_conn = sqlite3.connect(path + self.filename)
        self.browser_cur = self.browser_conn.cursor()

    def scan_the_records(self):
        save = []
        sql_select = "SELECT moz_historyvisits.place_id, moz_places.url, moz_places.title, count(*) FROM moz_historyvisits, moz_places WHERE moz_historyvisits.place_id=moz_places.id GROUP BY moz_historyvisits.place_id"
        self.browser_cur.execute(sql_select)
        for eachvisit in self.browser_cur.fetchall():

            tmp = list(eachvisit)
            tmp[0], tmp[-1] = str(tmp[0]), str(tmp[-1])
            if not isinstance(tmp[2], unicode):
                tmp[2] = str(tmp[2])
            tmp_str = '<2_2>'.join(tmp)
            save.append(tmp_str)
        return save

    def clean_the_records(self, history):
        int_history = int(history)
        sql_exist = 'SELECT * FROM moz_historyvisits WHERE place_id=%s' % int_history
        self.browser_cur.execute(sql_exist)
        if self.browser_cur.fetchone():
            sql_delete = 'DELETE FROM moz_historyvisits WHERE place_id=%s ' % int_history
            self.browser_cur.execute(sql_delete)
            #self.browser_cur.execute('DELETE FROM moz_places WHERE visit_count=0')
            self.browser_conn.commit()
            return True
        else:
            return False

    def clean_all_records(self):
        sql_deleteall = 'DELETE FROM moz_historyvisits'
        self.browser_cur.execute(sql_deleteall)
        #self.browser_cur.execute('DELETE FROM moz_places WHERE visit_count=0')
        self.browser_conn.commit()

    def __del__(self):
        self.browser_cur.close()
        self.browser_conn.close()

if __name__ == "__main__":
    objc = HistoryClean()
    objc.scan_the_records()
    #objc.clean_the_records(['36'])
    del objc
