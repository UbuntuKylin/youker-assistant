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
import sys
import apt
import apt_pkg
import shutil
import commands
from apt.progress.base import InstallProgress
from apt.progress.text import AcquireProgress


import historyclean
import cookiesclean
import searchsame
import diskanalyse
import osslim
import common
import cacheclean

#test path
#path = '/home/kylin/ubuntu-tweak/'
HOMEDIR = ''

def get_user_homedir(homedir):
    global HOMEDIR
    HOMEDIR = homedir


# clean up by one key
class OneKeyClean():
    def __init__(self):
        #self.objsame = SearchTheSame(path)
        #self.objlarge = ManageTheLarge(path)
        self.objunneed = CleanTheUnneed()
        self.objcache = CleanTheCache()

    def get_user_homedir(self, homedir):
        self.homedir = homedir

    def get_scan_result_system(self, mode_list):
        result_dic = {}
        flag_dic = {'history': False, 'cookies': False, 'unneed': False, 'cache': False}
        for mode in mode_list:
            flag_dic['%s' % mode] = True
        ### the part of unneed
        if flag_dic['unneed']:
            unneed_list = []
            tmp_unneed_list = self.objunneed.get_scan_result()
            for record in tmp_unneed_list:
                resultunneed = record.split('<2_2>')[0]
                unneed_list.append(resultunneed)
            result_dic['unneed'] = unneed_list
        ### the part of cache
        if flag_dic['cache']:
            cache_list = []
            tmp_cache_dic = self.objcache.get_scan_result(self.homedir)
            for k in tmp_cache_dic:
                tmp_cache_list = tmp_cache_dic[k].split('<1_1>')
                for one in tmp_cache_list:
                    resultcache = one.split('<2_2>')[0]
                    cache_list.append(resultcache)
            result_dic['cache'] = cache_list
        return result_dic


    def get_scan_result(self, mode_list):
        global HOMEDIR
        result_dic = {}
        flag_dic = {'history': False, 'cookies': False, 'unneed': False, 'cache': False}
        for mode in mode_list:
            flag_dic['%s' % mode] = True
        ### the part of history
        if flag_dic['history']:
            history_list = []
            objhistory = CleanTheHistory()
            tmp_history_list = objhistory.get_scan_result(HOMEDIR)
            #tmp_history_str = '<1_1>'.join(tmp_history_list)
            for record in tmp_history_list:
                resulthistory = record.split('<2_2>')[0]
                history_list.append(resulthistory)
            result_dic['history'] = history_list
            del objhistory

        ### the part of cookies
        if flag_dic['cookies']:
            cookies_list = []
            objcookies = CleanTheCookies()
            tmp_cookies_list = objcookies.get_scan_result(HOMEDIR)
            for record in tmp_cookies_list:
                resultcookies = record.split('<2_2>')[0]
                cookies_list.append(resultcookies)
            #tmp_cookies_str = '<1_1>'.join(tmp_cookies_list)
            result_dic['cookies'] = cookies_list
            del objcookies

        ### the part of unneed
        if flag_dic['unneed']:
            unneed_list = []
            tmp_unneed_list = self.objunneed.get_scan_result()
            for record in tmp_unneed_list:
                resultunneed = record.split('<2_2>')[0]
                unneed_list.append(resultunneed)
            #tmp_unneed_str = '<1_1>'.join(tmp_unneed_list)
            result_dic['unneed'] = unneed_list

        ### the part of cache
        if flag_dic['cache']:
            cache_list = []
            tmp_cache_dic = self.objcache.get_scan_result(HOMEDIR)
            for k in tmp_cache_dic:
                tmp_cache_list = tmp_cache_dic[k].split('<1_1>')
                for one in tmp_cache_list:
                    resultcache = one.split('<2_2>')[0]
                    cache_list.append(resultcache)
            result_dic['cache'] = cache_list

        # the part of same
        #tmp_same_list = self.objsame.get_scan_result()
        #tmp_same_str = '<1_1>'.join(tmp_same_list)
        #self.result_dic['same'] = tmp_same_str

        # the part of large
        #tmp_large_list = self.objlarge.get_scan_result()
        #tmp_large_str = '<1_1>'.join(tmp_large_list)
        #self.result_dic['large'] = tmp_large_str

        #for k in self.result_dic:
        #    print k
        #    print self.result_dic[k]
        return result_dic


# the functions of search the same files
class SearchTheSame():
    def __init__(self):
        self.objs = searchsame.SearchSame()

    def get_scan_result(self, path):
        self.path = path
        self.objs.search_by_style(self.path)
        samefile_list = self.objs.adjust_the_dic()
        return samefile_list

# the functions of manage the large files
class ManageTheLarge():
    def __init__(self):
        self.objl = diskanalyse.DiskAnalyse()

    def get_user_size(self, size):
        tmpsize = size
        self.filesize = tmpsize * 1024 * 1024

    def get_scan_result(self, path):
        self.path = path
        self.objl.hundred_large_files(self.path, self.filesize)
        self.objl.type_of_file()
        largefile_dic = self.objl.adjust_the_list()
        return largefile_dic
        
# the functions of clean the history
class CleanTheHistory():
    def __init__(self):
        pass
        #self.objh = historyclean.HistoryClean()

    def get_scan_result(self, homedir = ''):
        objhg = historyclean.HistoryClean(homedir)
        idurlcount = objhg.scan_the_records()
        return idurlcount

    def clean_the_cruftlist(self):
        global HOMEDIR
        objhc = historyclean.HistoryClean(HOMEDIR)
        objhc.clean_all_records()

    def __del__(self):
        pass
        #del self.objh

# the function of clean the cookies
class CleanTheCookies():
    def __init__(self):
        pass
        #self.objc = cookiesclean.CookiesClean()

    def get_scan_result(self, homedir = ''):
        objcg = cookiesclean.CookiesClean(homedir)
        domaincount = objcg.scan_the_records()
        return domaincount

    def clean_the_cruftlist(self, cruftlist):
        global HOMEDIR
        flag = None
        objcc = cookiesclean.CookiesClean(HOMEDIR)
        for cruft in cruftlist:
            flag = objcc.clean_the_records(cruft)

    def __del__(self):
        pass
        #del self.objc

# the function of scan the unneedpackages
class CleanTheUnneed():
    def __init__(self):
        self.objc = osslim.OsSlim()

    def get_scan_result(self):
        namesummarysize = self.objc.get_spare_packages()
        return namesummarysize

# the function of scan the cache
class CleanTheCache():
    def __init__(self):
        self.objc = cacheclean.CacheClean()

    def get_scan_result(self, homedir = ''):
        result_dic = {}
        tmp_apt_str = '<1_1>'.join(self.objc.get_apt_cache())
        tmp_center_str = '<1_1>'.join(self.objc.get_softwarecenter_cache(homedir))
        result_dic['apt'] = tmp_apt_str
        result_dic['softwarecenter'] = tmp_center_str
        return result_dic

# the function of clean cruft files and cruft packages
class FunctionOfClean():
    def __init__(self):
        pass

    def clean_the_file(self, cruftlist):
        for cruft in cruftlist:
            if cruft:
                if os.path.isdir(cruft):
                    shutil.rmtree(cruft)
                else:
                    os.remove(cruft)

    def clean_the_package(self, cruftlist):
        cache = common.get_cache_list()
        for cruft in cruftlist:
            pkg = cache[cruft]
            if pkg.is_installed:
                pkg.mark_delete()
        cache.commit(AcquireProgress(), TextInstallProgress())

    def uninstall_the_package(self, cruftlist):
        if not cruftlist:
            return
        program = 'apt-get'
        mode = 'remove'
        cache = common.get_cache_list()
        for cruft in cruftlist:
            pkg = cache[cruft]
            if pkg.is_installed:
                cmd = '%s %s -y %s' % (program, mode, cruft)
                (status, output) = commands.getstatusoutput(cmd)
                if status:
                    raise Exception(output)

        

class TextInstallProgress(InstallProgress):
        def __init__(self):
            InstallProgress.__init__(self)

        def statusChange(self, pkg, percent, status):
            pass

        def error(self, errorstr):
            pass

