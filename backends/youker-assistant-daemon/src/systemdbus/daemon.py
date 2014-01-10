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
import apt
import aptsources.sourceslist
import apt_pkg
from server import PolicyKitService
from policykit import UK_ACTION_YOUKER
import time
import cleaner
from detailinfo.cpuinfo import DetailInfo
from beautify.sound import Sound
from beautify.others import Others
from appcollections.monitorball.monitor_ball import MonitorBall
from softwarecenter.apt_daemon import AptDaemon

log = logging.getLogger('Daemon')


INTERFACE = 'com.ubuntukylin.youker'
UKPATH = '/'

class Daemon(PolicyKitService):
    def __init__ (self, bus, mainloop):
        self.infoconf = DetailInfo()
        self.otherconf = Others()
        self.soundconf = Sound()
        self.ballconf = MonitorBall()
        self.daemonsame = cleaner.SearchTheSame()
        self.daemonlarge = cleaner.ManageTheLarge()
        self.daemonunneed = cleaner.CleanTheUnneed()
        self.daemonclean = cleaner.FunctionOfClean()
        self.daemononekey = cleaner.OneKeyClean()
        self.daemoncache = cleaner.CleanTheCache()
        self.daemonApt = AptDaemon(self)
        bus_name = dbus.service.BusName(INTERFACE, bus=bus)
        PolicyKitService.__init__(self, bus_name, UKPATH)
        self.mainloop = mainloop

    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def exit(self):
        self.mainloop.quit()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_homedir(self, homedir):
        self.soundconf.set_homedir(homedir)

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b', sender_keyword='sender')
    def kill_root_process(self, pid, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            return False
        cmd = 'kill -9 %s' % pid
        subprocess.Popen(cmd, shell=True, close_fds=True)#加上close_fds=True,避免子进程一直存在
        return True

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_user_homedir(self, homedir):
        cleaner.get_user_homedir(homedir)

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_homedir_sysdaemon(self, homedir):
        cleaner.common.get_homedir_sysdaemon(homedir)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_system_daemon(self):
        return "SystemDaemon"

    @dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    def get_computer_info(self):
        return self.infoconf.get_computer()

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

    # judge ubuntukylin source is in /etc/apt/sources.list or not
    @dbus.service.method(INTERFACE, in_signature='', out_signature='b')
    def judge_source_ubuntukylin(self):
        source = aptsources.sourceslist.SourcesList()
        for item in source.list:
            if(item.str().find("deb http://archive.ubuntukylin.com/ubuntukylin") != -1):
                return True
        return False

    # add ubuntukylin source in /etc/apt/sources.list
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def add_source_ubuntukylin(self, version):
        source = aptsources.sourceslist.SourcesList(())
        #for item in source.list:
        #    if(item.str().find("deb http://archive.ubuntukylin.com/ubuntukylin") != -1):
        #        return
        osversion = str(version) + (" main")
        source.add("deb", "http://archive.ubuntukylin.com/ubuntukylin/", osversion, "")
        source.save()

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
    @dbus.service.method(INTERFACE, in_signature='ss', out_signature='')
    def add_new_plymouth(self, customBG, plymouthName):
        self.otherconf.add_new_plymouth(customBG, plymouthName)

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
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='b')
    def delete_plymouth(self,plymouthName):
        return self.otherconf.delete_plymouth(plymouthName)
    
    # -------------------------monitorball-------------------------
    # clean up memory
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def cleanup_memory(self):
        self.ballconf.cleanup_memory()
    # -------------------------monitorball end-------------------------

    # a dbus method which means clean complete by main one key 
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete_main(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete_onekey(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def clean_error_onekey(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def clean_data_main(self, category, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def clean_process_main(self, msg):
        pass
    
    @dbus.service.signal(INTERFACE, signature='ss')
    def status_for_quick_clean(self, flag, status):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def deb_exists_firefox(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def deb_exists_chromium(self, msg):
        pass

    # a dbus method which means clean complete by second one key 
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete_second(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def clean_data_second(self, category, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def total_data_onekey(self, category, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='s')
    def clean_process_second(self, msg):
        pass

    # a dbus method which means clean complete
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete(self, msg):
        pass

    # a dbus method which means quit clean by clicking the policykit's quit button
    @dbus.service.signal(INTERFACE, signature='s')
    def quit_clean(self, msg):
        pass

    # a dbus method which means clean single complete
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_single_complete(self, msg):
        pass

    # a dbus method which means an error occurred with main one key
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_error_main(self, msg):
        pass

    # a dbus method which means an error occurred with second one key
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_error_second(self, msg):
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
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            #self.clean_complete_msg('')
            self.revoke_clean_onekey('')
            return
        daemononekey = cleaner.OneKeyClean()
        try:
            daemononekey.clean_all_onekey_crufts(self, mode_list)
        except Exception, e:
            self.clean_error_msg('onekey')
        else:
            self.clean_complete_msg('onekey')

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='', sender_keyword='sender')
    def history_clean_records_function(self, flag, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.clean_complete_msg('')
            return
        daemonhistory = cleaner.CleanTheHistory(None)
        try:
            running = daemonhistory.clean_all_history_crufts(flag)
        except Exception, e:
            self.clean_error_msg(flag)
        else:
            self.clean_complete_msg(flag)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
    def clean_system_history(self, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.clean_complete_msg('')
            return
        daemonsystem = cleaner.CleanSystemHistory()
        try:
            daemonsystem.clean_the_cruftlist()
        except Exception, e:
            self.clean_error_msg('system')
        else:
            self.clean_complete_msg('system')

    @dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
    def clean_dash_history(self, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.clean_complete_msg('')
            return
        daemondash = cleaner.CleanDashHistory()
        try:
            daemondash.clean_the_cruftlist()
        except Exception, e:
            self.clean_error_msg('dash')
        else:
            self.clean_complete_msg('dash')

    @dbus.service.method(INTERFACE, in_signature = 'as', out_signature = '', sender_keyword = 'sender')
    def cookies_clean_record_function(self, flag, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.clean_single_complete_msg('')
            return
        daemoncookies = cleaner.CleanTheCookies(None)
        try:
            daemoncookies.clean_one_cookies_cruft(flag[0], flag[1])
        except Exception, e:
            self.clean_single_error_msg('cookies')
        else:
            self.clean_single_complete_msg('cookies')

    @dbus.service.method(INTERFACE, in_signature = 's', out_signature = '', sender_keyword = 'sender')
    def cookies_clean_records_function(self, flag, sender = None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.quit_clean_work(flag)
            return
        daemoncookies = cleaner.CleanTheCookies(None)
        try:
            daemoncookies.clean_all_cookies_crufts(flag)
        except Exception, e:
            self.clean_error_msg(flag)
        else:
            self.clean_complete_msg(flag)

    # the function of clean files
    ### input-['filepath', 'file...]   output-''
    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='', sender_keyword='sender')
    def clean_file_cruft(self, cruft_list, flagstr, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.clean_complete_msg('')
            return
        try:
            for cruft in cruft_list:
                self.daemonclean.clean_the_file(cruft)
        except Exception, e:
            self.clean_error_msg(flagstr)
        else:
            self.clean_complete_msg(flagstr)

    def dbusstring_to_string(self, string):
        tmp_string = str(string)
        patt = "u'[\S]+'"
        tmp_list = re.findall(patt, tmp_string)
        return [ok.split("'")[1] for ok in tmp_list]

    def clean_complete_main_msg(self, para):
        self.clean_complete_main(para)

    def clean_data_main_msg(self, category, para):
        self.clean_data_main(category, para)

    def clean_process_main_msg(self, para):
        self.clean_process_main(para)

    def deb_exists_firefox_msg(self, para):
        self.deb_exists_firefox(para)

    def deb_exists_chromium_msg(self, para):
        self.deb_exists_chromium(para)

    def clean_complete_second_msg(self, para):
        self.clean_complete_second(para)

    def clean_data_second_msg(self, category, para):
        self.clean_data_second(category, para)

    def clean_process_second_msg(self, para):
        self.clean_process_second(para)

    def clean_complete_msg(self, para):
        self.clean_complete(para)

    def quit_clean_work(self, para):
        self.quit_clean(para)

    def clean_single_complete_msg(self, para):
        self.clean_single_complete(para)

    def clean_error_msg(self, para):
        self.clean_error(para)

    def clean_single_error_msg(self, para):
        self.clean_single_error(para)

    def clean_error_main_msg(self, para):
        self.clean_error_main(para)

    def clean_error_second_msg(self, para):
        self.clean_error_second(para)

    def revoke_clean_onekey(self, para):
        self.clean_complete_onekey(para)

#-------------------------------------------
    @dbus.service.signal(INTERFACE, signature='s')
    def work_finish(self, msg):
        pass

    def start_to_emit_signal(self, msg):
        self.work_finish(msg)

    # a dbus method which means clean complete
    @dbus.service.signal(INTERFACE, signature='s')
    def sudo_finish_clean(self, msg):
        pass

    @dbus.service.signal(INTERFACE, signature='ss')
    def status_remove_packages(self, type, msg):
        pass

    # a dbus method which means an error occurred
    @dbus.service.signal(INTERFACE, signature='s')
    def sudo_clean_error(self, msg):
        pass

    # the function of clean packages
    ### input-['packagename', 'pack...]   output-''
    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='', sender_keyword='sender')
    def clean_package_cruft(self, cruftlist, flag, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.sudo_finish_clean_msg('')
            return
        try:
            self.daemonclean.clean_the_package(cruftlist, self)
        except Exception, e:
            self.sudo_clean_error_msg(flag)
        else:
            self.sudo_finish_clean_msg(flag)

    def sudo_finish_clean_msg(self, para):
        self.sudo_finish_clean(para)

    def sudo_clean_error_msg(self, para):
        self.sudo_clean_error(para)

    # -------------------------software-center-------------------------
    # install package sa:software_fetch_signal() and software_apt_signal()
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def install_pkg(self, pkgName):
        self.daemonApt.install_pkg(pkgName)

    # uninstall package sa:software_apt_signal()
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def uninstall_pkg(self, pkgName):
        self.daemonApt.uninstall_pkg(pkgName)

    # update package sa:software_fetch_signal() and software_apt_signal()
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def update_pkg(self, pkgName):
        self.daemonApt.update_pkg(pkgName)

    # check packages status by pkgNameList sa:software_check_status_signal()
    @dbus.service.method(INTERFACE, in_signature='as', out_signature='')
    def check_pkgs_status(self, pkgNameList):
        self.daemonApt.check_pkgs_status_rtn_list(pkgNameList)

    # check one package status by pkgName
    @dbus.service.method(INTERFACE, in_signature='s', out_signature='s')
    def check_pkg_status(self, pkgName):
        return self.daemonApt.check_pkg_status(pkgName)

    # apt-get update sa:software_fetch_signal()
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def apt_get_update(self):
        self.daemonApt.apt_get_update()

    # add ubuntukylin source in /etc/apt/sources.list
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='')
    #def add_source_ubuntukylin(self):
    #    self.daemonApt.add_source_ubuntukylin()

    # remove ubuntukylin source in /etc/apt/sources.list
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='')
    #def remove_source_ubuntukylin(self):
    #    self.daemonApt.remove_source_ubuntukylin()

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
    @dbus.service.signal(INTERFACE, signature='ss')
    def software_fetch_signal(self, type, msg):
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
    @dbus.service.signal(INTERFACE, signature='ss')
    def software_apt_signal(self, type, msg):
        pass

    # get packages status signal
    '''parm mean
        dict{packageName, packageStatus}
        packageStatus:
            i:installed
            u:installed and can update
            n:notinstall
    '''
    @dbus.service.signal(INTERFACE, signature='as')
    def software_check_status_signal(self, statusList):
        pass

if __name__ == '__main__':
    os.environ["TERM"] = "xterm"
    os.environ["PATH"] = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/X11R6/bin"
    os.environ["DEBIAN_FRONTEND"] = "noninteractive"
    if os.path.exists("/var/lib/apt/lists/lock"):
        os.remove("/var/lib/apt/lists/lock")
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    GObject.threads_init()
    mainloop = GObject.MainLoop()
    signal.signal(signal.SIGINT, lambda : mainloop.quit())
    Daemon(dbus.SystemBus(), mainloop)
    mainloop.run()
