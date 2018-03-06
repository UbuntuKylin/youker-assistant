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

import sys
import os
import signal
import glob
import fcntl
import shutil
import logging
import tempfile
import subprocess
import re
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GObject
#import apt
#import aptsources.sourceslist
#import apt_pkg
import threading
import _thread
from .server import PolicyKitService
from policykit import KYLIN_ASSISTANT_ACTION
import time
import cleaner
from detailinfo.cpuinfo import DetailInfo
from beautify.sound import Sound
from beautify.others import Others
#from appcollections.monitorball.monitor_ball import MonitorBall
#from softwarecenter.apt_daemon import AptDaemon
from beautify.theme import Theme
log = logging.getLogger('Daemon')


INTERFACE = 'com.kylin.assistant.systemdaemon'
UKPATH = '/com/kylin/assistant/systemdaemon'

#------------------------------------apt start----------------------------
from .apt_handler import AppActions, AptHandler, WorkitemError
#class WorkItem:
#     def __init__(self, pkgname, action, kwargs):
#        self.pkgname = pkgname
#        self.action = action
#        self.kwargs = kwargs

#class WorkThread(threading.Thread):
#    def __init__(self, dbusDaemon):
#        threading.Thread.__init__(self)
#        self.dbusDaemon = dbusDaemon
#        print "$$$$$$$$$$$$$$ ", type(self.dbusDaemon)

#    def run(self):
#        while(True):
#            if len(self.dbusDaemon.worklist) == 0:
#                time.sleep(0.2)
#                continue

#            self.dbusDaemon.mutex.acquire()
#            item = self.dbusDaemon.worklist.pop(0)  #get first item and remove it from list
#            self.dbusDaemon.mutex.release()

#            try:
#                func = getattr(self.dbusDaemon.aptHandler, item.action)
#                if func is None:
#                    print "Error action: ", item

#                res = func(item.pkgname,item.kwargs)
#                if res is False:
#                    print "Action exec failed..."
#            except WorkitemError as e:
#                kwarg = {"apt_appname": item.pkgname,
#                        "apt_percent": str(-e.errornum),
#                        "action": str(item.action),
#                        }
#                self.dbusDaemon.youker_apt_signal("apt_error", kwarg)

#            time.sleep(0.3)
#------------------------------------apt end----------------------------

class Daemon(PolicyKitService):
    def __init__ (self, bus, mainloop):
        self.infoconf = DetailInfo()
        self.otherconf = Others()
        self.soundconf = Sound()
#        self.ballconf = MonitorBall()
        self.themeconf = Theme()
#        self.daemonsame = cleaner.SearchTheSame()
#        self.daemonlarge = cleaner.ManageTheLarge()
#        self.daemonunneed = cleaner.CleanTheUnneed()
#        self.daemonclean = cleaner.FunctionOfClean()
        self.daemononekey = cleaner.OneKeyClean()
#        self.daemoncache = cleaner.CleanTheCache()
#        self.daemonApt = AptDaemon()
        #self.daemonApt = AptDaemon(self)

        #--------------apt start----------------
        self.aptHandler = AptHandler(self)
#        self.worklist = []
#        self.mutex = threading.RLock()
#        self.worker_thread = WorkThread(self)
#        self.worker_thread.setDaemon(True)
#        self.worker_thread.start()
        #--------------apt end----------------

        bus_name = dbus.service.BusName(INTERFACE, bus=bus)
        PolicyKitService.__init__(self, bus_name, UKPATH)
        self.mainloop = mainloop

    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def exit(self):
        self.mainloop.quit()

    #--------------apt start----------------
#    def add_worker_item(self, item):
#        print "####add_worker_item:", item
#        self.mutex.acquire()
#        self.worklist.append(item)
#        self.mutex.release()

    # package download status signal
    '''parm mean
        type:
            start:start download
            stop:all work is finish
            done:all items download finished
            fail:download failed
            fetch:one item download finished
            pulse:download status, this msg given a string like dict
        msg:
            a message of type, sometimes is None
    '''
    @dbus.service.signal(INTERFACE, signature='sas')
    def youker_fetch_signal(self, type, msg):
        pass

    # package install/update/remove signal
    '''parm mean
        type:
            start:start work
            stop:work finish
            error:got a error
            pulse:work status, this msg given a string like dict
        msg:
            a message of type, sometimes is None
    '''
    @dbus.service.signal(INTERFACE, signature='sas')
    def youker_apt_signal(self, type, msg):
        pass

    def start_install_uk(self, pkgName):
        self.aptHandler.install(pkgName)

    # install package sa:youker_fetch_signal() and youker_apt_signal()
    #sudo apt-get install youker-assistant=1.3.1-0ubuntu1
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b', sender_keyword='sender')
    def install(self, pkgName, sender=None):
        print("####install: ",pkgName)
#        item = WorkItem(pkgName, AppActions.INSTALL, None)
#        self.add_worker_item(item)
#        self.aptHandler.install(pkgName)
        _thread.start_new_thread(self.start_install_uk, (pkgName,))
        print("####install return")
        return True

    def start_update_source_list(self):
        self.aptHandler.update()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b', sender_keyword='sender')
    def update(self, sender=None):
        _thread.start_new_thread(self.start_update_source_list, ())
#        self.aptHandler.update()
        return True

#    @dbus.service.method(INTERFACE, in_signature='as', out_signature='b', sender_keyword='sender')
#    def upgrade(self, pkgNames, sender=None):
#        print "####upgrade: ", pkgNames
#        item = WorkItem(pkgNames, AppActions.UPGRADE, None)
#        self.add_worker_item(item)
#        #        self.aptHandler.upgrade_pkg(pkgName)
#        print "####upgrade return"
#        return True
    #--------------apt end----------------


    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_homedir(self, homedir):
        self.soundconf.set_homedir(homedir)

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def adjust_cpufreq_scaling_governer(self, value):
#        cpufreq_file = "/etc/init.d/cpufrequtils"
#        oldvalue = ''
#        if os.path.exists(cpufreq_file):
#            fp = open(cpufreq_file, "rw+")
#            line = fp.readline()
#            while line:
#                if line.startswith("GOVERNOR="):
#                    if value not in line:
#                        oldvalue = line.split("=")[1].replace('"', '').replace('\n', '')
#                        break
#                line = fp.readline()
#            fp.close()
#            if oldvalue not in ['', None] and value not in ['', None]:
#                cmd = "sed -i 's/%s/%s/g' %s" % (oldvalue, value, cpufreq_file)
#                os.system(cmd)
#                os.system('service cpufrequtils restart')
#        else:
        fpath = os.path.expanduser("/sys/devices/system/cpu/")
        for line in os.listdir(fpath):
            line = line.strip('\n')
            #pattern = re.compile(r'cpu.*[0-9]$')
            pattern = re.compile(r'cpu.*\d\Z')
            m = pattern.match(line)
            if m:
                filepath = "/sys/devices/system/cpu/%s/cpufreq/scaling_governor" % line
                if os.path.exists(filepath):
                    cmd = 'echo %s > %s' % (value, filepath)
                    os.system(cmd)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_cpufreq_scaling_governer_list(self):
        cmd = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors"
        fp = os.popen(cmd)
        msg = fp.read().strip('\n')
        fp.close()
        cpulist = []
        if msg not in ['', None]:
            cpulist = msg.split(' ')
        return cpulist

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_current_cpufreq_scaling_governer(self):
        cmd = "cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
        fp = os.popen(cmd)
        msg = fp.read().strip('\n')
        fp.close()
        return msg

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def copy_file(self, filename):
        des_path = '/var/lib/youker-assistant-daemon/custom'
        filename = filename.encode('utf-8')
        if not os.path.exists(des_path):
            os.makedirs(des_path)
        try:
            shutil.copy(filename, des_path)
            return True
        except os.error:
            pass
        return False

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def delete_file(self, filename):
        filename = filename.encode('utf-8')
#        output = open("/tmp/default.txt", 'w+')
#        output.write(filename)
#        output.close()
#        fp = open("/tmp/default.txt", "w")
#        print >> fp, "--------------"
#        print >> fp, filename
#        print >> fp, "------22222222--------"
#        fp.close()
#        if os.path.exists(filename):
        if os.path.isfile(filename):
            try:
                os.remove(filename)
                return True
            except os.error:
                pass
        return False

    # set cursor theme
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def set_cursor_theme_with_root(self, theme):
        return self.themeconf.set_cursor_theme_with_root(theme)

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b', sender_keyword='sender')
    def kill_root_process(self, pid, sender=None):
        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
        if not status:
            return False
        cmd = 'kill -9 %s' % pid
        subprocess.Popen(cmd, shell=True, close_fds=True)#加上close_fds=True,避免子进程一直存在
        return True

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def kill_uk_process(self):
        cmd = 'killall youker-assistant'
        subprocess.Popen(cmd, shell=True, close_fds=True)#加上close_fds=True,避免子进程一直存在
        return True

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_user_homedir(self, homedir):
        cleaner.get_user_homedir(homedir)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_system_daemon(self):
        return "SystemDaemon"

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_computer_info(self):
        return self.infoconf.get_computer()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_os_name(self):
        return self.infoconf.get_os_name()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_cpu_info(self):
        return self.infoconf.get_cpu()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_board_info(self):
        return self.infoconf.get_board()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_memory_info(self):
        return self.infoconf.get_memory()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_harddisk_info(self):
        return self.infoconf.get_disk()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_networkcard_info(self):
        return self.infoconf.get_network()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_monitor_info(self):
        return self.infoconf.get_monitor()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_cdrom_info(self):
        return self.infoconf.get_dvd()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_audiocard_info(self):
        return self.infoconf.get_multimedia()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_time_value(self):
        return self.infoconf.uptimeinfo()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_sensor_info(self):
        return self.infoconf.get_sensors()

    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def judge_sensors_exists_hb(self):
        return self.infoconf.judge_sensors_exists()


    # -------------------------sound-------------------------
    # get sound themes
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_sound_themes(self):
        return self.soundconf.get_sound_themes()

    # get sound files in current sound theme
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_sounds(self):
        return self.soundconf.get_sounds()

    # replace a sound file
    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='')
    def replace_sound_file(self, newSoundFile, targetSoundFile):
        self.soundconf.replace_sound_file(newSoundFile, targetSoundFile)

    # restore a sound file
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def restore_sound_file(self, targetSoundFile):
        self.soundconf.restore_sound_file(targetSoundFile)

    # restore all sound file in current sound theme
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def restore_all_sound_file(self, soundTheme):
        self.soundconf.restore_all_sound_file(soundTheme)
    
    # -------------------------others-------------------------
    
    # custom plymouth bg by plymouthName
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def custom_plymouth_bg(self, plymouthName):
        self.otherconf.custom_plymouth_bg(plymouthName)
    
    # add new custom plymouth
    #@dbus.service.method(INTERFACE, in_signature='ss', out_signature='')
    #def add_new_plymouth(self, customBG, plymouthName):
    #    self.otherconf.add_new_plymouth(customBG, plymouthName)

    # get existing plymouth list
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_existing_plymouth_list(self):
        return self.otherconf.get_existing_plymouth_list()
    
    # check and save current plymouth when init
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def plymouth_init_check(self):
        self.otherconf.plymouth_init_check()

    # get image path
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='s')
    def get_image_path(self,name):
        return self.otherconf.get_image_path(name)

    # Delete the boot animation from the list
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='s')
    def delete_plymouth(self,plymouthName):
        return self.otherconf.delete_plymouth(plymouthName)
    
    # -------------------------monitorball-------------------------
    # clean up memory
#    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
#    def cleanup_memory(self):
#        self.ballconf.cleanup_memory()
    # -------------------------monitorball end-------------------------

    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete_onekey(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def clean_error_onekey(self, msg):
        pass
    
    @dbus.service.signal(INTERFACE, signature='ss')
    def status_for_quick_clean(self, flag, status):
        pass

    # a dbus method which means clean complete
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete(self, msg):
        pass

    # a dbus method which means quit clean by clicking the policykit's quit button
    @dbus.service.signal(INTERFACE, signature='b')
    def quit_clean(self, status):
        pass

    # a dbus method which means clean single complete
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_single_complete(self, msg):
        pass

    # a dbus method which means an error occurred
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_error(self, msg):
        pass

    # a dbus method which means an single error occurred
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_single_error(self, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='as', out_signature='', sender_keyword='sender')
    def onekey_clean_crufts_function(self, mode_list, sender=None):
        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
        if not status:
            self.revoke_clean_onekey('yes')
            return
        else:
            self.revoke_clean_onekey('no')
        daemononekey = cleaner.OneKeyClean()
        try:
            t = threading.Thread(target = daemononekey.clean_all_onekey_crufts, args = (self, mode_list))
            t.start()
            #daemononekey.clean_all_onekey_crufts(self, mode_list)
        except Exception as e:
            self.clean_error_msg('onekey')
        else:
            self.clean_complete_msg('onekey')

#    @dbus.service.method(INTERFACE, in_signature='as', out_signature='', sender_keyword='sender')
#    def onekey_clean_crufts_function_by_threading(self, mode_list, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.revoke_clean_onekey('yes')
#            return
#        else:
#            self.revoke_clean_onekey('no')
#        daemononekey = cleaner.OneKeyClean()
#        try:
#            t = threading.Thread(target = daemononekey.clean_all_onekey_crufts, args = (self, mode_list))
#            #daemononekey.clean_all_onekey_crufts(self, mode_list)
#        except Exception, e:
#            self.clean_error_msg('onekey')
#        else:
#            self.clean_complete_msg('onekey')

#        return t

    def onekey_clean_cancel_function(self, t):
        daemononekey.cancel_onekey_clean(t, SystemExit)

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='', sender_keyword='sender')
#    def history_clean_records_function(self, flag, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.clean_complete_msg('')
#            return
#        daemonhistory = cleaner.CleanTheHistory()
#        try:
#            running = daemonhistory.clean_all_history_crufts(flag)
#        except Exception, e:
#            self.clean_error_msg(flag)
#        else:
#            self.clean_complete_msg(flag)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
#    def clean_system_history(self, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.clean_complete_msg('')
#            return
#        daemonsystem = cleaner.CleanSystemHistory()
#        try:
#            daemonsystem.clean_the_cruftlist()
#        except Exception, e:
#            self.clean_error_msg('system')
#        else:
#            self.clean_complete_msg('system')

    #@dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
    #def clean_dash_history(self, sender=None):
    #    status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
    #    if not status:
    #        self.clean_complete_msg('')
    #        return
    #    daemondash = cleaner.CleanDashHistory()
    #    try:
    #        daemondash.clean_the_cruftlist()
    #    except Exception, e:
    #        self.clean_error_msg('dash')
    #    else:
    #        self.clean_complete_msg('dash')

#    @dbus.service.method(INTERFACE, in_signature = 'as', out_signature = '', sender_keyword = 'sender')
#    def cookies_clean_record_function(self, flag, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.clean_single_complete_msg('')
#            return
#        daemoncookies = cleaner.CleanTheCookies(None)
#        try:
#            daemoncookies.clean_one_cookies_cruft(flag[0], flag[1])
#        except Exception, e:
#            self.clean_single_error_msg('cookies')
#        else:
#            self.clean_single_complete_msg('cookies')

#    @dbus.service.method(INTERFACE, in_signature = 's', out_signature = '', sender_keyword = 'sender')
#    def cookies_clean_records_function(self, flag, sender = None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.quit_clean_work(flag)
#            return
#        daemoncookies = cleaner.CleanTheCookies(None)
#        try:
#            daemoncookies.clean_all_cookies_crufts(flag)
#        except Exception, e:
#            self.clean_error_msg(flag)
#        else:
#            self.clean_complete_msg(flag)

    # the function of clean files
    ### input-['filepath', 'file...]   output-''
#    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='', sender_keyword='sender')
#    def clean_file_cruft(self, cruft_list, flagstr, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.clean_complete_msg('')
#            return
#        try:
#            for cruft in cruft_list:
#                self.daemonclean.clean_the_file(cruft)
#        except Exception, e:
#            self.clean_error_msg(flagstr)
#        else:
#            self.clean_complete_msg(flagstr)

    #def dbusstring_to_string(self, string):
    #    tmp_string = str(string)
    #    patt = "u'[\S]+'"
    #    tmp_list = re.findall(patt, tmp_string)
    #    return [ok.split("'")[1] for ok in tmp_list]

    def clean_complete_msg(self, para):
        self.clean_complete(para)

#    def quit_clean_work(self, para):
#        self.quit_clean(para)
#    def quit_clean_work(self, status):
#        self.quit_clean(status)

    def clean_single_complete_msg(self, para):
        self.clean_single_complete(para)

    def clean_error_msg(self, para):
        self.clean_error(para)

    def clean_single_error_msg(self, para):
        self.clean_single_error(para)

    def revoke_clean_onekey(self, para):
        self.clean_complete_onekey(para)

    # a dbus method which means clean complete
#    @dbus.service.signal(INTERFACE, signature='s')
#    def finish_clean(self, msg):
#        pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def status_remove_packages(self, type, msg):
        pass

    # a dbus method which means an error occurred
#    @dbus.service.signal(INTERFACE, signature='s')
#    def sudo_clean_error(self, msg):
#        pass

    # the function of clean packages
    ### input-['packagename', 'pack...]   output-''
#    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='', sender_keyword='sender')
#    def clean_package_cruft(self, cruftlist, flag, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.finish_clean_msg('')
#            return
#        try:
#            self.daemonclean.clean_the_package(cruftlist, self)
#        except Exception, e:
#            self.sudo_clean_error_msg(flag)
#        else:
#            self.finish_clean_msg(flag)

#    def finish_clean_msg(self, para):
#        self.finish_clean(para)

#    def sudo_clean_error_msg(self, para):
#        self.sudo_clean_error(para)

#-----START-----------NEW-YOUKER---------------------------
#

#    @dbus.service.method(INTERFACE, in_signature='a{sv}', out_signature='', sender_keyword='sender')
#    def remove_select_items(self, mode_dic, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.quit_clean(False)
##            self.quit_clean_work()
#            return
#        else:
#            self.quit_clean(True)
    def start_clean_all(self, mode_dic):
        filecache = mode_dic.get('file', [])
        if filecache:
            for tmpName in filecache:
                cleaner.interface_remove_file_system(self, tmpName)

        packagecache = mode_dic.get('package', [])
        if packagecache:
            for pkgName in packagecache:
                cleaner.interface_remove_package_system(self, pkgName)

        bashhistory = mode_dic.get('bash-history', [])
        if bashhistory:
            for tmpName in bashhistory:
                cleaner.interface_remove_file_system(self, tmpName)
        
        x11history = mode_dic.get('x11-history', [])
        if x11history:
            for tmpName in x11history:
                cleaner.interface_remove_file_system(self, tmpName)

        firefoxhistory = mode_dic.get('firefox-history', [])
        if firefoxhistory:
            cleaner.interface_remove_firefox_history_system(self)

        chromiumhistory = mode_dic.get('chromium-history', [])
        if chromiumhistory:
            cleaner.interface_remove_chromium_history_system(self)

        systemhistory = mode_dic.get('system-history', [])
        if systemhistory:
            cleaner.interface_remove_system_history_system(self)

        firefoxcookies = mode_dic.get('firefox-cookie', [])
        if firefoxcookies:
            for domain in firefoxcookies:
                cleaner.interface_remove_firefox_cookies_system(self, domain)

        chromiumcookies = mode_dic.get('chromium-cookie', [])
        if chromiumcookies:
            for domain in chromiumcookies:
                cleaner.interface_remove_chromium_cookies_system(self, domain)

        self.subpage_status_signal('Complete:All', "finish")

    @dbus.service.method(INTERFACE, in_signature='a{sv}', out_signature='', sender_keyword='sender')
    def remove_select_items(self, mode_dic, sender=None):
        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
        if not status:
            self.quit_clean(False)
            return
        else:
            self.quit_clean(True)
        _thread.start_new_thread(self.start_clean_all, (mode_dic,))
#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='', sender_keyword='sender')
#    def remove_file(self, fp):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.revoke_clean_onekey('yes')
#            return
#        else:
#            self.revoke_clean_onekey('no')
#        cleaner.interface_remove_file_system(self, fp)

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='', sender_keyword='sender')
#    def remove_package(self, pkgname, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.revoke_clean_onekey('yes')
#            return
#        else:
#            self.revoke_clean_onekey('no')
#        cleaner.interface_remove_package_system(self, pkgname)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
#    def remove_firefox_history(self, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.revoke_clean_onekey('yes')
#            return
#        else:
#            self.revoke_clean_onekey('no')
#        cleaner.interface_remove_firefox_history_system(self)

#    @dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
#    def remove_chromium_history(self, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.revoke_clean_onekey('yes')
#            return
#        else:
#            self.revoke_clean_onekey('no')
#        cleaner.interface_remove_chromium_history_system(self)

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='', sender_keyword='sender')
#    def remove_firefox_cookies(self, domain, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.revoke_clean_onekey('yes')
#            return
#        else:
#            self.revoke_clean_onekey('no')
#        cleaner.interface_remove_firefox_cookies_system(self, domain)

#    @dbus.service.method(INTERFACE, in_signature='s', out_signature='', sender_keyword='sender')
#    def remove_chromium_cookies(self, domain, sender=None):
#        status = self._check_permission(sender, KYLIN_ASSISTANT_ACTION)
#        if not status:
#            self.revoke_clean_onekey('yes')
#            return
#        else:
#            self.revoke_clean_onekey('no')
#        cleaner.interface_remove_chromium_cookies_system(self, domain)

    @dbus.service.signal(INTERFACE, signature='as')
    def subpage_data_signal(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def subpage_status_signal(self, msg, domain):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def subpage_error_signal(self, msg):
        pass
#-----END------------NEW-YOUKER---------------------------

if __name__ == '__main__':
    os.environ["TERM"] = "xterm"
    os.environ["PATH"] = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/X11R6/bin"
    os.environ["DEBIAN_FRONTEND"] = "noninteractive"
    if os.path.exists("/var/lib/apt/lists/lock"):
        os.remove("/var/lib/apt/lists/lock")
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    #gobject.threads_init()
    #mainloop = gobject.MainLoop()
    GObject.threads_init()
    mainloop = GObject.MainLoop()
    signal.signal(signal.SIGINT, lambda : mainloop.quit())
    Daemon(dbus.SystemBus(), mainloop)
    mainloop.run()
