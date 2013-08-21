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
import pprint
import shutil
from apt.progress import InstallProgress, TextFetchProgress


import historyclean
import cookiesclean
import searchsame
import diskanalyse
import osslim
import common
import cacheclean

#test path
path = '/home/kylin/ubuntu-tweak/'

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
        resault_dic = {}
        flag_dic = {'history': False, 'cookies': False, 'unneed': False, 'cache': False}
        for mode in mode_list:
            flag_dic['%s' % mode] = True
        ### the part of unneed
        if flag_dic['unneed']:
            unneed_list = []
            tmp_unneed_list = self.objunneed.get_scan_resault()
            for record in tmp_unneed_list:
                resaultunneed = record.split('<2_2>')[0]
                unneed_list.append(resaultunneed)
            resault_dic['unneed'] = unneed_list
        ### the part of cache
        if flag_dic['cache']:
            cache_list = []
            tmp_cache_dic = self.objcache.get_scan_resault(self.homedir)
            for k in tmp_cache_dic:
                tmp_cache_list = tmp_cache_dic[k].split('<1_1>')
                for one in tmp_cache_list:
                    resaultcache = one.split('<2_2>')[0]
                    cache_list.append(resaultcache)
            resault_dic['cache'] = cache_list
        return resault_dic


    def get_scan_resault(self, mode_list):
        resault_dic = {}
        flag_dic = {'history': False, 'cookies': False, 'unneed': False, 'cache': False}
        for mode in mode_list:
            flag_dic['%s' % mode] = True
        ### the part of history
        if flag_dic['history']:
            history_list = []
            objhistory = CleanTheHistory()
            tmp_history_list = objhistory.get_scan_resault()
            #tmp_history_str = '<1_1>'.join(tmp_history_list)
            for record in tmp_history_list:
                resaulthistory = record.split('<2_2>')[0]
                history_list.append(resaulthistory)
            resault_dic['history'] = history_list
            del objhistory

        ### the part of cookies
        if flag_dic['cookies']:
            cookies_list = []
            objcookies = CleanTheCookies()
            tmp_cookies_list = objcookies.get_scan_resault()
            for record in tmp_cookies_list:
                resaultcookies = record.split('<2_2>')[0]
                cookies_list.append(resaultcookies)
            #tmp_cookies_str = '<1_1>'.join(tmp_cookies_list)
            resault_dic['cookies'] = cookies_list
            del objcookies

        ### the part of unneed
        #if flag_dic['unneed']:
        #    unneed_list = []
        #    tmp_unneed_list = self.objunneed.get_scan_resault()
        #    for record in tmp_unneed_list:
        #        resaultunneed = record.split('<2_2>')[0]
        #        unneed_list.append(resaultunneed)
            #tmp_unneed_str = '<1_1>'.join(tmp_unneed_list)
        #    resault_dic['unneed'] = unneed_list

        ### the part of cache
        #if flag_dic['cache']:
        #    cache_list = []
        #    tmp_cache_dic = self.objcache.get_scan_resault(self.homedir)
        #    for k in tmp_cache_dic:
        #        tmp_cache_list = tmp_cache_dic[k].split('<1_1>')
        #        for one in tmp_cache_list:
        #            resaultcache = one.split('<2_2>')[0]
        #            cache_list.append(resaultcache)
        #    resault_dic['cache'] = cache_list

        # the part of same
        #tmp_same_list = self.objsame.get_scan_resault()
        #tmp_same_str = '<1_1>'.join(tmp_same_list)
        #self.resault_dic['same'] = tmp_same_str

        # the part of large
        #tmp_large_list = self.objlarge.get_scan_resault()
        #tmp_large_str = '<1_1>'.join(tmp_large_list)
        #self.resault_dic['large'] = tmp_large_str

        #for k in self.resault_dic:
        #    print k
        #    print self.resault_dic[k]
        return resault_dic


# the functions of search the same files
class SearchTheSame():
    def __init__(self):
        self.objs = searchsame.SearchSame()

    def get_scan_resault(self, path):
        self.path = path
        self.objs.search_by_style(self.path)
        samefile_list = self.objs.adjust_the_dic()
        #pprint.pprint(samefile_list)
        return samefile_list

# the functions of manage the large files
class ManageTheLarge():
    def __init__(self):
        self.objl = diskanalyse.DiskAnalyse()

    def get_scan_resault(self, path):
        self.path = path
        self.objl.hundred_large_files(self.path)
        self.objl.type_of_file()
        largefile_dic = self.objl.adjust_the_list()
        #pprint.pprint(largefile_dic)
        #print len(largefile_dic)
        return largefile_dic
        
# the functions of clean the history
class CleanTheHistory():
    def __init__(self):
        self.objh = historyclean.HistoryClean()

    def get_scan_resault(self):
        idurlcount = self.objh.scan_the_records()
        #print idurlcount
        return idurlcount

    def clean_the_cruftlist(self):
        self.objh.clean_all_records()

    def __del__(self):
        del self.objh

# the function of clean the cookies
class CleanTheCookies():
    def __init__(self):
        self.objc = cookiesclean.CookiesClean()

    def get_scan_resault(self):
        domaincount = self.objc.scan_the_records()
        #print domaincount
        return domaincount

    def clean_the_cruftlist(self, cruftlist):
        flag = None
        for cruft in cruftlist:
            flag = self.objc.clean_the_records(cruft)

    def __del__(self):
        del self.objc

# the function of scan the unneedpackages
class CleanTheUnneed():
    def __init__(self):
        self.objc = osslim.OsSlim()

    def get_scan_resault(self):
        namesummarysize = self.objc.get_spare_packages()
        #print namesummarysize
        return namesummarysize

# the function of scan the cache
class CleanTheCache():
    def __init__(self):
        self.objc = cacheclean.CacheClean()

    def get_scan_resault(self, homedir = ''):
        resault_dic = {}
        tmp_apt_str = '<1_1>'.join(self.objc.get_apt_cache())
        tmp_center_str = '<1_1>'.join(self.objc.get_softwarecenter_cache(homedir))
        resault_dic['apt'] = tmp_apt_str
        resault_dic['softwarecenter'] = tmp_center_str
        #print resault_dic
        return resault_dic

# the function of clean cruft files and cruft packages
class FunctionOfClean():
    def __init__(self):
        pass

    def clean_the_file(self, cruftlist):
        for cruft in cruftlist:
            if cruft:
                print 'cleaning %s' % cruft
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
        cache.commit(TextFetchProgress(), TextInstallProgress())
        

class TextInstallProgress(InstallProgress):
        def __init__(self):
            InstallProgress.__init__(self)

        def statusChange(self, pkg, percent, status):
            pass

        def error(self, errorstr):
            pass


if __name__ == "__main__":
    objtest1 = SearchTheSame()
    objtest1.get_scan_resault(path)
    #objtest2 = ManageTheLarge()
    #objtest2.get_scan_resault(path)
    #objtest3 = CleanTheHistory()
    #objtest3.get_scan_resault()
    #del objtest3
    #objtest4 = CleanTheCookies()
    #objtest4.get_scan_resault()
    #objtest4.clean_the_cruftlist(['win4000.com'])
    #objtest4.get_scan_resault()
    #del objtest4
    #objtest5 = OneKeyClean()
    #objtest5.get_scan_resault(['cookies','history'])
    #objtest6 = CleanTheUnneed()
    #objtest6.get_scan_resault()
    #objtest7 = CleanTheCache()
    #objtest7.get_scan_resault()
