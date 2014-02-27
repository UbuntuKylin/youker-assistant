#!/usr/bin/python
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
import commands
#import threading
from apt.progress.base import InstallProgress

import historyclean
import cookiesclean
import searchsame
import diskanalyse
import osslim
import common
import cacheclean
import oldkernel
import systemhistory
import dashhistory
import softwareconfigfile

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

    def clean_all_onekey_crufts(self, sysdaemon, mode_list):
        homedir = return_homedir_sysdaemon()
        flag_dic = {'history': False, 'cookies': False, 'cache': False}
        for mode in mode_list:
            flag_dic['%s' % mode] = True
        #if flag_dic['cache']:
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
            except Exception, e:
                sysdaemon.clean_error_onekey('ce')
            else:
                sysdaemon.clean_complete_onekey('c')
        #if flag_dic['history']:
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
            except Exception, e:
                sysdaemon.clean_error_onekey('he')
            else:
                sysdaemon.clean_complete_onekey('h')
                
        #if flag_dic['cookies']:
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
            except Exception, e:
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

    def get_large_files(self, size, path, sesdaemon):
        objlg = diskanalyse.DiskAnalyse()
        finalsize = size * 1024 * 1024
        largefile_list = objlg.hundred_large_files(finalsize, path)
        for one in largefile_list:
            sesdaemon.data_transmit_by_large(common.confirm_filesize_unit(one[0]), one[1])
        sesdaemon.large_transmit_complete()

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
            temp_firefox_list = self.objc.firefox_scan_cache(firefoxpath)
            for one in temp_firefox_list:
                if os.path.isdir(one):
                    sesdaemon.data_transmit_by_cache('firefox', one, 'True', common.confirm_filesize_unit(common.get_dir_size(one)))
                else:
                    sedaemon.data_transmit_by_cache('firefox', one, 'False', common.confirm_filesize_unit(os.path.getsize(one)))
        if 'chromium' in mode_list:
            chromiumpath = "%s/.cache/chromium/Default" % homedir
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
