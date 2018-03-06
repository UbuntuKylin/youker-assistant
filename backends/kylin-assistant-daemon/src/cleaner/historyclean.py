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

import os.path
import sqlite3
from .common import process_pid
from .common import get_mozilla_path


class HistoryClean():
    def __init__(self, homedir):
        self.filename = 'places.sqlite'
        self.path = get_mozilla_path(homedir)

    def scan_the_records(self):
        save = []
        if os.path.exists(self.path):
            scan_browser_conn = sqlite3.connect(self.path + self.filename)
            scan_browser_cur = scan_browser_conn.cursor()
            sql_select = "SELECT moz_historyvisits.place_id, moz_places.url, moz_places.title, count(*) FROM moz_historyvisits, moz_places WHERE moz_historyvisits.place_id=moz_places.id GROUP BY moz_historyvisits.place_id"
            scan_browser_cur.execute(sql_select)
            for eachvisit in scan_browser_cur.fetchall():

                tmp = list(eachvisit)
                tmp[0], tmp[-1] = str(tmp[0]), str(tmp[-1])
                if not isinstance(tmp[2], str):
                    tmp[2] = str(tmp[2])
                tmp_str = '<2_2>'.join(tmp)
                save.append(tmp_str)
            scan_browser_cur.close()
            scan_browser_conn.close()
        return save

    def scan_firefox_history_records(self, filepath):
        result = []
        if os.path.exists(filepath):
            scan_browser_conn = sqlite3.connect(filepath)
            scan_browser_cur = scan_browser_conn.cursor()
            sql_select = "SELECT moz_historyvisits.place_id, moz_places.url, count(*) FROM moz_historyvisits, moz_places WHERE moz_historyvisits.place_id=moz_places.id GROUP BY moz_historyvisits.place_id"
            scan_browser_cur.execute(sql_select)
            result = scan_browser_cur.fetchall()
            #result = ["%s<2_2>%s<2_2>%s" % (str(each[0]), each[1], str(each[2])) for each in allvisit]
            scan_browser_cur.close()
            scan_browser_conn.close()
        return result

    def scan_chromium_history_records(self, filepath):
        result = []
        if os.path.exists(filepath):
            scan_chromium_conn = sqlite3.connect(filepath)
            scan_chromium_cur = scan_chromium_conn.cursor()
            sql_select = "SELECT visits.url, urls.url, count(*) FROM visits, urls WHERE visits.url=urls.id GROUP BY visits.url"
            scan_chromium_cur.execute(sql_select)
            result = scan_chromium_cur.fetchall()
            #result = ["%s<2_2>%s<2_2>%s" % (str(each[0]), each[1], str(each[2])) for each in allvisit]
            scan_chromium_cur.close()
            scan_chromium_conn.close()

        return result

    def clean_firefox_all_records(self, filepath):
        if os.path.exists(filepath):
            clean_browser_conn = sqlite3.connect(filepath)
            clean_browser_cur = clean_browser_conn.cursor()
            sql_deletehistory = 'DELETE FROM moz_historyvisits'
            clean_browser_cur.execute(sql_deletehistory)
            clean_browser_conn.commit()

            sql_selectplace = 'SELECT place_id FROM moz_annos UNION SELECT fk FROM moz_bookmarks UNION SELECT place_id FROM moz_inputhistory'
            clean_browser_cur.execute(sql_selectplace)
            delete_place_id = clean_browser_cur.fetchall()
            delete_place_id_str = ','.join([ str(one[0]) for one in delete_place_id if one[0]])
            sql_deleteplace = 'DELETE FROM moz_places WHERE id NOT IN (%s)' % delete_place_id_str
            clean_browser_cur.execute(sql_deleteplace)
            clean_browser_conn.commit()

            sql_selectfavicons = 'SELECT favicon_id FROM moz_places'
            clean_browser_cur.execute(sql_selectfavicons)
            delete_favicon_id = clean_browser_cur.fetchall()
            delete_favicon_id_str = ','.join([ str(one[0]) for one in delete_favicon_id if one[0]])
            sql_deletefavicons = 'DELETE FROM moz_favicons WHERE id NOT in (%s)' %  delete_favicon_id_str
            clean_browser_cur.execute(sql_deletefavicons)
            clean_browser_conn.commit()

            clean_browser_cur.close()
            clean_browser_conn.close()

    def clean_chromium_all_records(self, filepath):
        if os.path.exists(filepath):
            clean_chromium_conn = sqlite3.connect(filepath)
            clean_chromium_cur = clean_chromium_conn.cursor()
            tables = ['visits', 'urls', 'keyword_search_terms', 'segment_usage', 'segments']
            for tn in tables:
                sql_delete = 'DELETE FROM %s' % tn
                clean_chromium_cur.execute(sql_delete)
            clean_chromium_conn.commit()

            clean_chromium_cur.close()
            clean_chromium_conn.close()

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
        if os.path.exists(self.path):
            clean_browser_conn = sqlite3.connect(self.path + self.filename)
            clean_browser_cur = clean_browser_conn.cursor()
            sql_deleteall = 'DELETE FROM moz_historyvisits'
            clean_browser_cur.execute(sql_deleteall)
            #self.browser_cur.execute('DELETE FROM moz_places WHERE visit_count=0')
            clean_browser_conn.commit()
            clean_browser_cur.close()
            clean_browser_conn.close()

if __name__ == "__main__":
    objc = HistoryClean()
    objc.scan_the_records()
    #objc.clean_the_records(['36'])
    del objc
