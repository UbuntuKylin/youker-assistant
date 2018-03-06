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
import sys
import apt
import apt_pkg
import shutil
import subprocess
import threading
import ctypes
from apt.progress.base import InstallProgress
import time
from . import historyclean
from . import cookiesclean
from . import searchsame
from . import diskanalyse
from . import osslim
from . import common
from . import cacheclean
from . import oldkernel
from . import systemhistory
from . import dashhistory
from . import softwareconfigfile

HOMEDIR = ''

def get_user_homedir(homedir):
    global HOMEDIR
    HOMEDIR = homedir

def return_homedir_sysdaemon():
    global HOMEDIR
    return HOMEDIR

# clean up by one key
class OneKeyClean():
    def __init__(self):
        self.objunneed = CleanTheUnneed()
        self.objcache = CleanTheCache()

    def get_onekey_crufts(self, sesdaemon, mode_list):
        homedir = common.return_homedir_sesdaemon()
        crufts_dic = {}
        total_dic = {}
        flag_dic = {'history': False, 'cookies': False, 'cache': False}
        for mode in mode_list:
            flag_dic['%s' % mode] = True
        time.sleep(1)
        if flag_dic['history']:
            historysize = 0
            objhg = historyclean.HistoryClean(homedir)
            filepathf = "%s/.mozilla/firefox/%s/places.sqlite" % (homedir, common.analytical_profiles_file(homedir))
            if os.path.exists(filepathf):
                tempf_list = objhg.scan_firefox_history_records(filepathf)
                for onef in tempf_list:
                    sesdaemon.display_scan_process(onef[1])
                    #sesdaemon.display_scan_process_msg(onef[1])
                    historysize += onef[2]
            filepathc = "%s/.config/chromium/Default/History" % homedir
            if os.path.exists(filepathc):
                run = common.process_pid("chromium-browser")
                if not run:
                    tempc_list = objhg.scan_chromium_history_records(filepathc)
                    for onec in tempc_list:
                        sesdaemon.display_scan_process(onec[1])
                        #sesdaemon.display_scan_process_msg(onec[1])
                        historysize += onec[2]
            total_dic['history'] = str(historysize)
            sesdaemon.total_data_transmit('h', total_dic['history'])
        time.sleep(1)
        if flag_dic['cookies']:
            cookiessize = 0
            objcg = cookiesclean.CookiesClean(homedir)
            filepathff = "%s/.mozilla/firefox/%s/cookies.sqlite" % (homedir, common.analytical_profiles_file(homedir))
            if os.path.exists(filepathff):
                pamf = [filepathff, 'moz_cookies', 'baseDomain']
                tempff_list = objcg.scan_cookies_records(pamf[0], pamf[1], pamf[2])
                for oneff in tempff_list:
                    sesdaemon.display_scan_process(oneff[0])
                    #sesdaemon.display_scan_process_msg(oneff[0])
                    cookiessize += oneff[1]
            filepathcc = "%s/.config/chromium/Default/Cookies" % homedir
            if os.path.exists(filepathcc):
                pamc = [filepathcc, 'cookies', 'host_key']
                tempcc_list = objcg.scan_cookies_records(pamc[0], pamc[1], pamc[2])
                for onecc in tempcc_list:
                    sesdaemon.display_scan_process(onecc[0])
                    #sesdaemon.display_scan_process_msg(onecc[0])
                    cookiessize += onecc[1]
            total_dic['cookies'] = str(cookiessize)
            sesdaemon.total_data_transmit('k', total_dic['cookies'])
        time.sleep(1)
        if flag_dic['cache']:
            cachesize = 0
            objcache = cacheclean.CacheClean()
            apt_path = "/var/cache/apt/archives"
            temp_apt_list = objcache.scan_apt_cache(apt_path)
            for oneapt in temp_apt_list:
                sesdaemon.display_scan_process(oneapt)
                #sesdaemon.display_scan_process_msg(oneapt)
                cachesize += os.path.getsize(oneapt)
            swcenterpath = '%s/.cache/software-center' % homedir
            temp_swcenter_list = objcache.public_scan_cache(swcenterpath)
            for oneswcenter in temp_swcenter_list:
                sesdaemon.display_scan_process(oneswcenter)
                #sesdaemon.display_scan_process_msg(oneswcenter)
                if os.path.isdir(oneswcenter):
                    cachesize += common.get_dir_size(oneswcenter)
                else:
                    cachesize += os.path.getsize(oneswcenter)
            total_dic['cache'] = common.confirm_filesize_unit(cachesize)
            sesdaemon.total_data_transmit('c', total_dic['cache'])
        # add by kobe
        sesdaemon.scan_complete_msg('onekey')

    def clean_all_onekey_crufts(self, sysdaemon, mode_list):
        homedir = return_homedir_sysdaemon()
        flag_dic = {'history': False, 'cookies': False, 'cache': False}
        for mode in mode_list:
            flag_dic['%s' % mode] = True
        #if flag_dic['cache']:
        time.sleep(1)
        if mode_list[0] in '1':
            try:
                objclean = FunctionOfClean()
                objcache = cacheclean.CacheClean()
                apt_path = "/var/cache/apt/archives"
                temp_apt_list = objcache.scan_apt_cache(apt_path)
                for cachea in temp_apt_list:
                    sysdaemon.status_for_quick_clean('apt', cachea)
                    objclean.clean_the_file(cachea)
                sysdaemon.status_for_quick_clean('apt', 'end')

                swcenterpath = '%s/.cache/software-center' % homedir
                temp_swcenter_list = objcache.public_scan_cache(swcenterpath)
                for caches in temp_swcenter_list:
                    sysdaemon.status_for_quick_clean('software_center', caches)
                    objclean.clean_the_file(caches)
                sysdaemon.status_for_quick_clean('software_center', 'end')
            except Exception as e:
                sysdaemon.clean_error_onekey('ce')
            else:
                sysdaemon.clean_complete_onekey('c')
        #if flag_dic['history']:
        time.sleep(1)
        if mode_list[1] in '1':
            try:
                sysdaemon.status_for_quick_clean('firefoxhistory', 'start')
                objca = historyclean.HistoryClean(homedir)
                filepathf = "%s/.mozilla/firefox/%s/places.sqlite" % (homedir, common.analytical_profiles_file(homedir))
                objca.clean_firefox_all_records(filepathf)
                sysdaemon.status_for_quick_clean('firefoxhistory', 'end')

                run = common.process_pid("chromium-browser")
                if not run:
                    sysdaemon.status_for_quick_clean('chromiumhistory', 'start')
                    filepathc = "%s/.config/chromium/Default/History" % homedir
                    objca.clean_chromium_all_records(filepathc)
                    sysdaemon.status_for_quick_clean('chromiumhistory', 'end')
            except Exception as e:
                sysdaemon.clean_error_onekey('he')
            else:
                sysdaemon.clean_complete_onekey('h')
                
        #if flag_dic['cookies']:
        time.sleep(1)
        if mode_list[2] in '1':
            try:
                objcc = cookiesclean.CookiesClean(homedir)
                sysdaemon.status_for_quick_clean('firefoxcookies', 'start')
                filepathfc = "%s/.mozilla/firefox/%s/cookies.sqlite" % (homedir, common.analytical_profiles_file(homedir))
                pamfc = [filepathfc, 'moz_cookies', 'baseDomain']
                objcc.clean_all_records(pamfc[0], pamfc[1], pamfc[2])
                sysdaemon.status_for_quick_clean('firefoxcookies', 'end')
                
                sysdaemon.status_for_quick_clean('chromiumcookies', 'start')
                filepathcc = "%s/.config/chromium/Default/Cookies" % homedir
                pamcc = [filepathcc, 'cookies', 'host_key']
                objcc.clean_all_records(pamcc[0], pamcc[1], pamcc[2])
                sysdaemon.status_for_quick_clean('chromiumcookies', 'end')
            except Exception as e:
                sysdaemon.clean_error_onekey('ke')
            else:
                sysdaemon.clean_complete_onekey('k')
        sysdaemon.clean_complete_onekey('o')

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

#    def get_large_files(self, size, path, sesdaemon):
#        objlg = diskanalyse.DiskAnalyse()
#        finalsize = size * 1024 * 1024
#        largefile_list = objlg.hundred_large_files(finalsize, path)
#        for one in largefile_list:
#            sesdaemon.data_transmit_by_large(common.confirm_filesize_unit(one[0]), one[1])
#        sesdaemon.large_transmit_complete()

    def get_scan_result(self, size, path):
        self.path = path
        finalsize = size * 1024 * 1024
        #self.objl.hundred_large_files(finalsize, self.path)
        #self.objl.type_of_file()
        largefile_dic = self.objl.adjust_the_list(finalsize, self.path)
        return largefile_dic
        
# the functions of clean the browser history
class CleanTheHistory():
    def __init__(self):
        pass

    #def new_get_history_crufts(self, flag, sesdaemon):
    #    homedir = common.return_homedir_sesdaemon()
    #    objhg = historyclean.HistoryClean(homedir)
    #    crufts_list = []
    #    cache = common.get_cache_list()

    #    if flag in "firefox":
    #        if cache['firefox'].is_installed:
    #            filepathf = "%s/.mozilla/firefox/%s/places.sqlite" % (homedir, common.analytical_profiles_file(homedir))
    #            if not common.process_pid("firefox"):
    #                if os.path.exists(filepathf):
    #                    temp_list = objhg.scan_firefox_history_records(filepathf)
    #                    sesdaemon.data_transmit_by_history(sum([sin[2] for sin in temp_list]))
    #            else:
    #                sesdaemon.browser_status_by_history('fruning')
    #        else:
    #            sesdaemon.history_transmit_complete('funinstall')
    #    if flag in "chromium":
    #        if cache['chromium'].is_installed:
    #            filepathc = "%s/.config/chromium/Default/History" % homedir
    #            if not common.process_pid("chromium-browser"):
    #                if os.path.exists(filepathc):
    #                    temp_list = objhg.scan_chromium_history_records(filepathc)
    #                    sesdaemon.data_transmit_by_history(sum([sin[2] for sin in temp_list]))
    #            else:
    #                sesdaemon.browser_status_by_history('cruning')
    #        else:
    #            sesdaemon.history_transmit_complete('cuninstall')

    def get_history_crufts(self, flag):
        homedir = common.return_homedir_sesdaemon()
        objhg = historyclean.HistoryClean(homedir)
        crufts_list = []
        cache = common.get_cache_list()

        if flag in "firefox":
            filepathf = "%s/.mozilla/firefox/%s/places.sqlite" % (homedir, common.analytical_profiles_file(homedir))
            if cache['firefox'].is_installed:
                if os.path.exists(filepathf):
                    temp_list = objhg.scan_firefox_history_records(filepathf)
                    crufts_list = ["%s<2_2>%s<2_2>%s" % (str(each[0]), each[1], str(each[2])) for each in temp_list]
            else:
                return 'No'
        if flag in "chromium":
            filepathc = "%s/.config/chromium/Default/History" % homedir
            if cache['chromium-browser'].is_installed:
                if os.path.exists(filepathc):
                    run = common.process_pid("chromium-browser")
                    if not run:
                        temp_list = objhg.scan_chromium_history_records(filepathc)
                        crufts_list = ["%s<2_2>%s<2_2>%s" % (str(each[0]), each[1], str(each[2])) for each in temp_list]
                    else:
                        return 'True'
            else:
                return 'No'
        return crufts_list

    def clean_all_history_crufts(self, flag):
        homedir = return_homedir_sysdaemon()
        objca = historyclean.HistoryClean(homedir)
        running = False

        if flag in "firefox":
            filepathf = "%s/.mozilla/firefox/%s/places.sqlite" % (homedir, common.analytical_profiles_file(homedir))
            objca.clean_firefox_all_records(filepathf)
        if flag in "chromium":
            run = common.process_pid("chromium-browser")
            if not run:
                filepathc = "%s/.config/chromium/Default/History" % homedir
                objca.clean_chromium_all_records(filepathc)
            else:
                running = True
        return running

# the function of clean the system history
class CleanSystemHistory():
    def get_scan_result(self, homedir = ''):
        objhg = systemhistory.SystemHistory()
        url = objhg.scan_the_xml(homedir)
        return url

    def clean_the_cruftlist(self):
        global HOMEDIR
        objhc = systemhistory.SystemHistory()
        objhc.clean_the_xml(HOMEDIR)


# the function of clean the dash history
class CleanDashHistory():
    def get_scan_result(self, homedir = ''):
        objhg = dashhistory.DashHistory(homedir)
        num = objhg.scan_the_records()
        return num

    def clean_the_cruftlist(self):
        global HOMEDIR
        objhc = dashhistory.DashHistory(HOMEDIR)
        objhc.clean_the_records()

# the function of clean the cookies
class CleanTheCookies():
    def __init__(self, daemon_obj):
        self.daemon_obj = daemon_obj

    def get_cookie_crufts(self, flag, sesdaemon):
        homedir = common.return_homedir_sesdaemon()
        objcg = cookiesclean.CookiesClean(homedir)
        cache = common.get_cache_list()
        crufts_list = []

        if flag in "firefox":
            if cache["firefox"].is_installed:
                filepathf = "%s/.mozilla/firefox/%s/cookies.sqlite" % (homedir, common.analytical_profiles_file(homedir))
                if os.path.exists(filepathf):
                    pamf = [filepathf, 'moz_cookies', 'baseDomain']
                    temp_firefox_list = objcg.scan_cookies_records(pamf[0], pamf[1], pamf[2])
                    for one in temp_firefox_list:
                        sesdaemon.data_transmit_by_cookies("firefox", one[0], str(one[-1]))
                    sesdaemon.cookies_transmit_complete('firefox')
            else:
                sesdaemon.cookies_transmit_complete('funinstall')

        if flag in "chromium":
            if cache["chromium-browser"].is_installed:
                filepathc = "%s/.config/chromium/Default/Cookies" % homedir
                if os.path.exists(filepathc):
                    pamc = [filepathc, 'cookies', 'host_key']
                    temp_chromium_list = objcg.scan_cookies_records(pamc[0], pamc[1], pamc[2])
                    for one in temp_chromium_list:
                        sesdaemon.data_transmit_by_cookies("chromium", one[0], str(one[-1]))
                    sesdaemon.cookies_transmit_complete('chromium')
            else:
                sesdaemon.cookies_transmit_complete('cuninstall')

    def get_cookies_crufts(self, flag):
        homedir = common.return_homedir_sesdaemon()
        objcg = cookiesclean.CookiesClean(homedir)
        crufts_list = []

        if flag in "firefox":
            filepathf = common.analytical_profiles_file(homedir) + "cookies.sqlite"
            if os.path.exists(filepathf):
                pamf = [filepathf, 'moz_cookies', 'baseDomain']
                temp_list = objcg.scan_cookies_records(pamf[0], pamf[1], pamf[2])
                crufts_list = ["%s<2_2>%s" % (eachone[0], str(eachone[-1])) for eachone in temp_list]
            else:
                crufts_list.append('None')
                return crufts_list
        if flag in "chromium":
            filepathc = "%s/.config/chromium/Default/Cookies" % homedir
            if os.path.exists(filepathc):
                pamc = [filepathc, 'cookies', 'host_key']
                temp_list = objcg.scan_cookies_records(pamc[0], pamc[1], pamc[2])
                crufts_list = ["%s<2_2>%s" % (eachone[0], str(eachone[-1])) for eachone in temp_list]
            else:
                crufts_list.append('None')
                return crufts_list

        return crufts_list

    def clean_one_cookies_cruft(self, flag, domain):
        homedir = return_homedir_sysdaemon()
        objcc = cookiesclean.CookiesClean(homedir)

        if flag in "firefox":
            filepathf = "%s/.mozilla/firefox/%s/cookies.sqlite" % (homedir, common.analytical_profiles_file(homedir))
            pamf = [filepathf, 'moz_cookies', 'baseDomain', domain]
            objcc.clean_cookies_record(pamf[0], pamf[1], pamf[2], pamf[3])
        if flag in "chromium":
            filepathc = "%s/.config/chromium/Default/Cookies" % homedir
            pamc = [filepathc, 'cookies', 'host_key', domain]
            objcc.clean_cookies_record(pamc[0], pamc[1], pamc[2], pamc[3])
            
    def clean_all_cookies_crufts(self, flag):
        homedir = return_homedir_sysdaemon()
        objcc = cookiesclean.CookiesClean(homedir)

        if flag in "firefox":
            filepathf = "%s/.mozilla/firefox/%s/cookies.sqlite" % (homedir, common.analytical_profiles_file(homedir))
            pamf = [filepathf, 'moz_cookies', 'baseDomain']
            objcc.clean_all_records(pamf[0], pamf[1], pamf[2])
        if flag in "chromium":
            filepathc = "%s/.config/chromium/Default/Cookies" % homedir
            pamc = [filepathc, 'cookies', 'host_key']
            objcc.clean_all_records(pamc[0], pamc[1], pamc[2])

# the function of scan the unneedpackages
class CleanTheUnneed():
    def __init__(self):
        self.objc = osslim.OsSlim()

    def get_scan_result(self):
        namesummarysize = self.objc.get_spare_packages()
        return namesummarysize

# the function of clean old kernel
class CleanTheOldkernel():
    def __init__(self):
        pass

    def get_oldkernel_crufts(self):
        objc = oldkernel.OldKernel()
        pkgobj_list = objc.scan_oldkernel_packages()
        crufts_list = ["%s<2_2>%s" % (pkg.name, pkg.installed.summary, common.confirm_filesize_unit(pkg.installed.installed_size))for pkg in pkgobj_list]
        return crufts_list

# the function of clean spare packages
class CleanTheSpare():
    def __init__(self):
        pass

    def get_all_package_crufts(self, mode_list, sesdaemon):
        if 'unneed' in mode_list:
            upkg_obj = osslim.OsSlim()
            temp_unneed_list = upkg_obj.scan_spare_packages()
            for upkg in temp_unneed_list:
                sesdaemon.data_transmit_by_package('unneed', upkg.name, upkg.installed.summary, common.confirm_filesize_unit(upkg.installed.installed_size))
        
        if 'oldkernel' in mode_list:
            opkg_obj = oldkernel.OldKernel()
            temp_oldkernel_list = opkg_obj.scan_oldkernel_packages()
            for opkg in temp_oldkernel_list:
                sesdaemon.data_transmit_by_package('oldkernel', opkg.name, opkg.installed.summary, common.confirm_filesize_unit(opkg.installed.installed_size))

        if 'configfile' in mode_list:
            spkg_obj = softwareconfigfile.SoftwareConfigfile()
            temp_configfile_list = spkg_obj.scan_configfile_packages()
            for spkg in temp_configfile_list:
                sesdaemon.data_transmit_by_package('configfile', spkg.name, '', '')
        sesdaemon.package_transmit_complete()

# the function of scan the cache
class CleanTheCache():
    def __init__(self):
        self.objc = cacheclean.CacheClean()

    def get_all_cache_crufts(self, mode_list, flag, sesdaemon):
        homedir = common.return_homedir_sesdaemon()

        if 'apt' in mode_list:
            aptpath = "/var/cache/apt/archives"
            temp_apt_list = self.objc.scan_apt_cache(aptpath)
            for one in temp_apt_list:
                sesdaemon.data_transmit_by_cache('apt', one, 'False', '%s' % common.confirm_filesize_unit(os.path.getsize(one)))

        if 'software-center' in mode_list:
            softwarecenterpath = "%s/.cache/software-center" % homedir
            temp_softwarecenter_list = self.objc.public_scan_cache(softwarecenterpath)
            for one in temp_softwarecenter_list:
                if os.path.isdir(one):
                    sesdaemon.data_transmit_by_cache('software-center', one, 'True', common.confirm_filesize_unit(common.get_dir_size(one)))
                else:
                    sesdaemon.data_transmit_by_cache('software-center', one, 'False', common.confirm_filesize_unit(os.path.getsize(one)))

        if 'thumbnails' in mode_list:
            thumbnailspath = "%s/.cache/thumbnails" % homedir
            temp_thumbnails_list = self.objc.public_scan_cache(thumbnailspath)
            for one in temp_thumbnails_list:
                if os.path.isdir(one):
                    sesdaemon.data_transmit_by_cache('thumbnails', one, 'True', common.confirm_filesize_unit(common.get_dir_size(one)))
                else:
                    sesdaemon.data_transmit_by_cache('thumbnails', one, 'False',common.confirm_filesize_unit(os.path.getsize(one)))
        if 'firefox' in mode_list:
            firefoxpath = "%s/.cache/mozilla/firefox/%s" % (homedir, common.analytical_profiles_file(homedir))
            #sesdaemon.path_transmit_by_cache('firefox', firefoxpath)
            temp_firefox_list = self.objc.firefox_scan_cache(firefoxpath)
            for one in temp_firefox_list:
                if os.path.isdir(one):
                    sesdaemon.data_transmit_by_cache('firefox', one, 'True', common.confirm_filesize_unit(common.get_dir_size(one)))
                else:
                    sedaemon.data_transmit_by_cache('firefox', one, 'False', common.confirm_filesize_unit(os.path.getsize(one)))
        if 'chromium' in mode_list:
            chromiumpath = "%s/.cache/chromium/Default" % homedir
            #sesdaemon.path_transmit_by_cache('chromium', chromiumpath)
            temp_chromium_list = self.objc.public_scan_cache(chromiumpath)
            for one in temp_chromium_list:
                if os.path.isdir(one):
                    sesdaemon.data_transmit_by_cache('chromium', one, 'True', common.confirm_filesize_unit(common.get_dir_size(one)))
                else:
                    sesdaemon.data_transmit_by_cache('chromium', one, 'False',common.confirm_filesize_unit(os.path.getsize(one)))

        sesdaemon.cache_transmit_complete(flag)

# the function of clean cruft files and cruft packages
#class FunctionOfClean(threading.Thread):
class FunctionOfClean():
    def __init__(self):
        #threading.Thread.__init__(self)
        #self.msgdaemon = msgdaemon
        pass

    def clean_the_file(self, cruft):
        tmp = cruft.encode("UTF-8")
        #sysdaemon.data_of_remove_file(tmp)
        if tmp:
            if os.path.isdir(tmp):
                shutil.rmtree(tmp)
            else:
                os.remove(tmp)

    #def clean_the_file(self, cruftlist):
    #    threading.Thread(target=self.clean_the_file_thread, args=(cruftlist,), name='CleanFile').start()

    def clean_the_package(self, cruftlist, sysdaemon):
        if cruftlist:
            cache = common.get_cache_list()
            cache.open()
            for cruft in cruftlist:
                pkg = cache[cruft]
                if pkg.is_installed:
                    pkg.mark_delete()
                else:
                    pkg.mark_delete(purge=True)
            iprogress = MyInstallProgress(sysdaemon)
            cache.commit(None, iprogress)

    def purge_the_package(self, cruftlist, sysdaemon):
        if cruftlist:
            cache = common.get_cache_list()
            cache.open()
            for cruft in cruftlist:
                pkg = cache[cruft]
                pkg.mark_delete(purge=True)
            iprogress = MyInstallProgress(sysdaemon)
            cache.commit(None, iprogress)

    #def clean_the_package(self, cruftlist):
    #    threading.Thread(target=self.clean_the_package_thread, args=(cruftlist,), name='CleanPackage').start()

class MyInstallProgress(InstallProgress):
        def __init__(self, sysdaemon):
            InstallProgress.__init__(self)
            self.sysdaemon = sysdaemon

        def status_change(self, pkg, percent, status):
            self.sysdaemon.status_remove_packages("apt_pulse", "percent: %s, status: %s" % (str(int(percent)), status))

        def error(self, errorstr):
            pass
        
        def finish_update(self):
            self.sysdaemon.status_remove_packages("apt_stop", "")

        def start_update(self):
            self.sysdaemon.status_remove_packages("apt_start", "")

def cancel_mainpage_function(target_tid, exception):
    pass
    #found = False
    #target_tid = 0
    #for tid, tobj in threading._active.items():
    #    if tobj is thread_obj:
    #        found = True
    #        target_tid = tid
    #        break
    #if not found:
    #    raise ValueError("Invalid thread object")
#    res = ctypes.pythonapi.PyThreadState_SetAsyncExc(ctypes.c_long(target_tid), ctypes.py_object(exception))

#    if res = 0:
#        raise ValueError("Invalid thread ID")
#    elif res > 1:
#        ctypes.pythonapi.PyThreadState_SetAsyncExc(ctypes.c_long(target_tid), None)
#        raise SystemError("PyThreadState_SetAsyncExc failed")

def get_threadid(thread_obj):
    found = False
    target_tid = 0
    for tid, tobj in list(threading._active.items()):
        if tobj is thread_obj:
            found = True
            target_tid = tid
            break
    if not found:
        raise ValueError("Invalid thread object")
    return target_tid


class MainPage():
    def __init__(self):
        pass

    def get_cache(self, sesdaemon):
        flag = False
        totalsize = 0
        homedir = ''
        cache_obj = cacheclean.CacheClean()
        if sesdaemon:
            homedir = common.return_homedir_sesdaemon()
        else:
            homedir = return_homedir_sysdaemon()

        self.cache_dic = {'apt':[], 'softwarecenter':[], 'thumbnail':[]}
        aptpath = "/var/cache/apt/archives"
        temp_apt_list = cache_obj.scan_apt_cache(aptpath)
        if sesdaemon:
            for one in temp_apt_list:
                self.cache_dic['apt'].append(one)
                totalsize += common.get_size(one)
                sesdaemon.check_scan_garbage_process(one)
        else:
            for one in temp_apt_list:
                self.cache_dic['apt'].append(one)
        softwarecenterpath = "%s/.cache/software-center" % homedir
        temp_softwarecenter_list = cache_obj.public_scan_cache(softwarecenterpath)
        if sesdaemon:
            for one in temp_softwarecenter_list:
                self.cache_dic['softwarecenter'].append(one)
                totalsize += common.get_size(one)
                sesdaemon.check_scan_garbage_process(one)
        else:
            for one in temp_softwarecenter_list:
                self.cache_dic['softwarecenter'].append(one)
        thumbnailspath = "%s/.cache/thumbnails" % homedir
        try:
            temp_thumbnails_list = cache_obj.public_scan_cache(thumbnailspath)
        except Exception as e:
            print(e)
        if sesdaemon:
            for one in temp_thumbnails_list:
                self.cache_dic['thumbnail'].append(one)
                totalsize += common.get_size(one)
                sesdaemon.check_scan_garbage_process(one)
        else:
            for one in temp_thumbnails_list:
                self.cache_dic['thumbnail'].append(one)
        if sesdaemon:
            for key in list(self.cache_dic.keys()):
                if self.cache_dic[key]:
                    flag = True
                    break
            if flag:
                sesdaemon.scan_complete('True')
            else:
                sesdaemon.scan_complete('False')
            size_str = common.confirm_filesize_unit(totalsize)
            sesdaemon.check_scan_complete(size_str)
        else:
            pass

    def clean_cache(self, sysdaemon):
        totalsize = 0
        self.get_cache(None)
        for key in list(self.cache_dic.keys()):
            for f in self.cache_dic[key]:
                totalsize += common.get_size(f)
                if os.path.isdir(f):
                    sysdaemon.info_for_mainpage_clean(f)
                    shutil.rmtree(f)
                else:
                    sysdaemon.info_for_mainpage_clean(f)
                    os.remove(f)
        size_str = common.confirm_filesize_unit(totalsize)
        sysdaemon.mainpage_clean(size_str)
#----------------------------NEW YOUKER--------------------

#---------------------SubPage---------------------

def append_cacheinfo_to_list(belong, path):
    info = []
    info.append('Belong:%s' % belong)
    info.append('Path:%s' % path)
    if os.path.isdir(path):
        info.append('Type:directory')
        info.append('Size:%s' % common.confirm_filesize_unit(common.get_dir_size(path)))
    else:
        info.append('Type:file')
        info.append('Size:%s' % common.confirm_filesize_unit(os.path.getsize(path)))

    return info

def interface_get_subpage_session(session, mode_dic):
    homedir = common.return_homedir_sesdaemon()

    cache = mode_dic.get('Cache', [])
    if cache:
        cache_obj = cacheclean.CacheClean()
        if 'apt' in cache:
            aptpath = "/var/cache/apt/archives"
            apt_list = cache_obj.scan_apt_cache(aptpath)
            for value in apt_list:
                info = append_cacheinfo_to_list('Cache.apt', value)

                session.subpage_data_signal(info)
        #else:
            #info = []
            #info.append('Belong:Cache.apt')
            #info.append('')
            #session.subpage_data_signal(info)

        if 'software-center' in cache:
            swcenterpath = "%s/.cache/software-center" % homedir
            swcenter_list = cache_obj.public_scan_cache(swcenterpath)
            for value in swcenter_list:
                info = append_cacheinfo_to_list('Cache.software-center', value)
                session.subpage_data_signal(info)
        #else:
            #info = []
            #info.append('Belong:Cache-apt')
            #info.append('')
            #session.subpage_data_signal(info)

        if 'thumbnails' in cache:
            thumbnailspath = "%s/.cache/thumbnails" % homedir
            thumbnails_list = cache_obj.public_scan_cache(thumbnailspath)
            for value in thumbnails_list:
                info = append_cacheinfo_to_list('Cache.thumbnails', value)
                session.subpage_data_signal(info)
        #else:
            #info = []
            #info.append('Belong:Cache.thumbnails')
            #info.append('')
            #session.subpage_data_signal(info)


        if 'firefox' in cache:
            firefoxpath = "%s/.cache/mozilla/firefox/%s" % (homedir, common.analytical_profiles_file(homedir))
            firefox_cache_list = cache_obj.firefox_scan_cache(firefoxpath)
            for value in firefox_cache_list:
                info = append_cacheinfo_to_list('Cache.firefox', value)
                session.subpage_data_signal(info)
        #else:
            #info = []
            #info.append('Belong:Cache.firefox')
            #info.append('')
            #session.subpage_data_signal(info)

        if 'chromium' in cache:
            chromiumpath = "%s/.cache/chromium/Default" % homedir
            chromium_cache_list = cache_obj.public_scan_cache(chromiumpath)
            for value in chromium_cache_list:
                info = append_cacheinfo_to_list('Cache.chromium', value)
                session.subpage_data_signal(info)
        #else:
            #info = []
            #info.append('Belong:Cache.chromium')
            #info.append('')
            #session.subpage_data_signal(info)

        session.subpage_status_signal('Complete:Cache')

    cookies = mode_dic.get('Cookies', [])
    if cookies:
        cache = common.get_cache_list()
        cookies_obj = cookiesclean.CookiesClean(homedir)
        

        if 'firefox' in cookies:
            if cache['firefox'].is_installed:
                ffcpath = "%s/.mozilla/firefox/%s/cookies.sqlite" % (homedir, common.analytical_profiles_file(homedir))
                if os.path.exists(ffcpath):
                    ffcpam = [ffcpath, 'moz_cookies', 'baseDomain']
                    firefox_cookies_list = cookies_obj.scan_cookies_records(ffcpam[0], ffcpam[1], ffcpam[2])

                    for value in firefox_cookies_list:
                        info = []
                        info.append('Belong:Cookies.firefox')
                        info.append('Content:%s' % value[0])
                        info.append('Count:%s' % str(value[-1]))
                        session.subpage_data_signal(info)
                    
                else:
                    info = []
                    info.append('Belong:Cookies.firefox')
                    info.append('')
                    session.subpage_data_signal(info)
            else:
                session.subpage_error_signal('Uninstalled:Firefox')
                    
        
        if 'chromium' in cookies:
            try:
                pkg = cache['chromium-browser']
            except KeyError:
                pass
            else:
                if pkg.is_installed:
                    chcpath = "%s/.config/chromium/Default/Cookies" % homedir
                    if os.path.exists(chcpath):
                        chcpam = [chcpath, 'cookies', 'host_key']
                        chromium_cookies_list = cookies_obj.scan_cookies_records(chcpam[0], chcpam[1], chcpam[2])
                        for value in chromium_cookies_list:
                            info = []
                            info.append('Belong:Cookies.chromium')
                            info.append('Content:%s' % value[0])
                            info.append('Count:%s' % str(value[-1]))
                            session.subpage_data_signal(info)
                    else:
                        info = []
                        info.append('Belong:Cookies.chromium')
                        info.append('')
                        session.subpage_data_signal(info)
                else:
                    session.subpage_error_signal('Uninstalled:Chromium')
        session.subpage_status_signal('Complete:Cookies')


    history = mode_dic.get('History', [])
    if history:
        cache = common.get_cache_list()
        brohistory_obj = historyclean.HistoryClean(homedir)

        if 'firefox' in history:
            if cache['firefox'].is_installed:
                ffhpath = "%s/.mozilla/firefox/%s/places.sqlite" % (homedir, common.analytical_profiles_file(homedir))
                if os.path.exists(ffhpath):
                    firefox_history_list = brohistory_obj.scan_firefox_history_records(ffhpath)
                    #for single in firefox_history_list:
                    #    info = []
                    #    info.append('Belong:History.firefox')
                    #    info.append('Id:%s' % str(single[0]))
                    #    info.append('Url:%s' % single[1])
                    #    info.append('Count:%s' % str(single[2]))
                    #    session.subpage_data_signal(info)
                    info = []
                    info.append('Belong:History.firefox')
                    info.append('Count:%s' % str(len(firefox_history_list)))
                    session.subpage_data_signal(info)
                else:
                    info = []
                    info.append('Belong:History.firefox')
                    info.append('')
                    session.subpage_data_signal(info)
                    
            else:
                session.subpage_error_signal('Uninstalled:Firefox')

        if 'chromium' in history:
            chhpath = "%s/.config/chromium/Default/History" % homedir
            try:
                pkg = cache['chromium-browser']
            except KeyError:
                pass
            else:
                if pkg.is_installed:
                    run = common.process_pid("chromium-browser")
                    if not run:
                        chromium_history_list = brohistory_obj.scan_chromium_history_records(chhpath)
                        #for single in chromium_history_list:
                        #    info = []
                        #    info.append('Belong:History.chromium')
                        #    info.append('Id:%s' % str(single[0]))
                        #    info.append('Url:%s' % single[1])
                        #    info.append('Count:%s' % str(single[2]))
                        #    session.subpage_data_signal(info)
                        info = []
                        info.append('Belong:History.chromium')
                        info.append('Count:%s' % str(len(chromium_history_list)))
                        session.subpage_data_signal(info)
                    else:
                        session.subpage_error_signal('Working:Chromium')
                else:
                    session.subpage_error_signal('Uninstalled:Chromium')
        if 'bash' in history:
            path = os.path.join(homedir, ".bash_history")
            size = 0
            if os.path.exists(path):
                size = common.confirm_filesize_unit(os.path.getsize(path))
                info = []
                info.append('Belong:History.bash')
                info.append('Size:%s' % str(size))
                info.append('Path:%s' % path)
                session.subpage_data_signal(info)
            else:
                pass
            

        if 'X11' in history:
            x11_list = [os.path.join(homedir, x) for x in os.listdir(homedir) if x.startswith(".xsession-errors")]
            for value in x11_list:
                info = append_cacheinfo_to_list('History.X11', value)
                session.subpage_data_signal(info)

        if 'system' in history:
            syshistory_obj = systemhistory.SystemHistory()
            url_list = syshistory_obj.scan_the_xml(homedir)
            #for value in url_list:
            #    info = []
            #    info.append('Belong:History.system')
                #info.append('Count:%s' % len(url_list))
            #    info.append('Href:%s' % value)
            #    session.subpage_data_signal(info)
            info = []
            info.append('Belong:History.system')
            info.append('Count:%s' % str(len(url_list)))
            session.subpage_data_signal(info)
        session.subpage_status_signal('Complete:History')

    packages = mode_dic.get('Packages', [])
    if packages:
        if 'unneed' in packages:
            unneed_obj = osslim.OsSlim()
            
            unneed_packages_list = unneed_obj.get_unneed_packages()
            for value in unneed_packages_list:
                info = value.split(";")
                info.insert(0, 'Belong:Packages.unneed')
                session.subpage_data_signal(info)
        
        if 'oldkernel' in packages:
            oldkernel_obj = oldkernel.OldKernel()

            oldkernel_list = oldkernel_obj.get_oldkernel_packages()
            for value in oldkernel_list:
                info = value.split(";")
                info.insert(0, 'Belong:Packages.oldkernel')
                session.subpage_data_signal(info)
        
        if 'configfile' in packages:
            configfile_obj = softwareconfigfile.SoftwareConfigfile()
            
            configfile_list = configfile_obj.get_configfile_packages()
            for value in configfile_list:
                info = value.split(";")
                info.insert(0, 'Belong:Packages.configfile')
                session.subpage_data_signal(info)
        session.subpage_status_signal('Complete:Packages')
    session.subpage_status_signal('Complete:All')


def interface_remove_file_system(system, fp):
        filepath = fp.encode("UTF-8")
        if os.path.exists(fp):
            info = []
            if os.path.isdir(filepath):
                info.append('Path:%s' % filepath)
                info.append('Size:%s' % common.confirm_filesize_unit(common.get_dir_size(filepath)))
                shutil.rmtree(filepath)
                system.subpage_data_signal(info)
            else:
                info.append('Path:%s' % filepath)
                info.append('Size:%s' % common.confirm_filesize_unit(os.path.getsize(filepath)))
                os.remove(filepath)
                system.subpage_data_signal(info)
        else:
            system.subpage_error_signal('Non-existent:%s' % filepath)

def interface_remove_firefox_history_system(system):
    homedir = return_homedir_sysdaemon()
    firefox_history_obj = historyclean.HistoryClean(homedir)

    ffhpath = "%s/.mozilla/firefox/%s/places.sqlite" % (homedir, common.analytical_profiles_file(homedir))
    firefox_history_obj.clean_firefox_all_records(ffhpath)

    system.subpage_status_signal('Complete:History.firefox', 'history')

def interface_remove_system_history_system(system):
    homedir = return_homedir_sysdaemon()
    system_history_obj = systemhistory.SystemHistory()
    system_history_obj.clean_the_xml(homedir)
    system.subpage_status_signal('Complete:History.system', 'history')

def interface_remove_chromium_history_system(system):
    homedir = return_homedir_sysdaemon()
    chromium_history_obj = historyclean.HistoryClean(homedir)

    run = common.process_pid("chromium-browser")
    if not run:
        chhpath = "%s/.config/chromium/Default/History" % homedir
        chromium_history_obj.clean_chromium_all_records(chhpath)
        system.subpage_status_signal('Complete:History.chromium', 'history')
    else:
        system.subpage_error_signal('Working:Chromium')

def interface_remove_firefox_cookies_system(system, domain):
    homedir = return_homedir_sysdaemon()
    firefox_cookies_obj = cookiesclean.CookiesClean(homedir)
    #print(domain)

    ffcpath = "%s/.mozilla/firefox/%s/cookies.sqlite" % (homedir, common.analytical_profiles_file(homedir))
    ffcpam = [ffcpath, 'moz_cookies', 'baseDomain', domain]
    firefox_cookies_obj.clean_cookies_record(ffcpam[0], ffcpam[1], ffcpam[2], ffcpam[3])
    system.subpage_status_signal('Complete:Cookies.firefox', domain)

def interface_remove_chromium_cookies_system(system, domain):
    homedir = return_homedir_sysdaemon()
    chromium_cookies_obj = cookiesclean.CookiesClean(homedir)
    
    chcpath = "%s/.config/chromium/Default/Cookies" % homedir
    chcpam = [chcpath, 'cookies', 'host_key', domain]
    chromium_cookies_obj.clean_cookies_record(chcpam[0], chcpam[1], chcpam[2], chcpam[3])
    system.subpage_status_signal('Complete:Cookies.chromium', domain)
    

def interface_remove_package_system(system, packagename):
        if packagename:
            cache = common.get_cache_list()
            cache.open()
            try:
                pkg = cache[packagename]
            except KeyError:
                system.subpage_error_signal('Non-existent:%s' % packagename)
            if pkg.is_installed:
                pkg.mark_delete()
            else:
                pkg.mark_delete(purge=True)
            iprogress = NewInstallProgress(system)
            cache.commit(None, iprogress)

class NewInstallProgress(InstallProgress):
    def __init__(self, system):
        InstallProgress.__init__(self)
        self.system = system

    def status_change(self, pkg, percent, status):
        #self.system.status_remove_packages("apt_pulse", "percent: %s, status: %s" % (str(int(percent)), status))
        info = []
        info.append('Pkg:%s' % pkg)
        info.append('Percent:%s' % str(int(percent)))
        info.append('Status:%s' % status)
        self.system.subpage_data_signal(info)
        #self.system.subpage_status_signal(info, 'apt')

    def error(self, errorstr):
        pass

    def finish_update(self):
        #self.system.status_remove_packages("apt_stop", "")
        self.system.subpage_status_signal('Complete:', 'apt')

    def start_update(self):
        #self.system.status_remove_packages("apt_start", "")
        self.system.subpage_status_signal('Start:', 'apt')
