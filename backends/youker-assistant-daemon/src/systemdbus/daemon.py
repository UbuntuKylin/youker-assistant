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
import glob
import fcntl
import shutil
import logging
import tempfile
import subprocess
import re

from subprocess import PIPE
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GObject
import apt
import apt_pkg
from server import PolicyKitService
from policykit import UK_ACTION_YOUKER
import time
import cleaner
from beautify.sound import Sound
from beautify.others import Others
from appcollections.monitorball.monitor_ball import MonitorBall

log = logging.getLogger('Daemon')

INTERFACE = 'com.ubuntukylin_tools.daemon'
UKPATH = '/'

class Daemon(PolicyKitService):
    def __init__ (self, bus, mainloop):
        self.otherconf = Others()
        self.soundconf = Sound()
        self.ballconf = MonitorBall()
        self.daemonsame = cleaner.SearchTheSame()
        self.daemonlarge = cleaner.ManageTheLarge()
        self.daemonunneed = cleaner.CleanTheUnneed()
        self.daemonclean = cleaner.FunctionOfClean()
        self.daemononekey = cleaner.OneKeyClean()
        self.daemoncache = cleaner.CleanTheCache()
        bus_name = dbus.service.BusName(INTERFACE, bus=bus)
        PolicyKitService.__init__(self, bus_name, UKPATH)
        self.mainloop = mainloop

    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def exit(self):
        self.mainloop.quit()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_homedir(self, homedir):
        self.soundconf.set_homedir(homedir)

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_user_homedir(self, homedir):
        cleaner.get_user_homedir(homedir)

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_system_daemon(self):
        return "SystemDaemon"

    @dbus.service.signal(INTERFACE, signature='as')
    def get_speed(self, speed):
        pass

    def get_network_speed(self, speed):
        self.get_speed(speed)

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
    
    # -------------------------monitorball-------------------------

    # get cpu percent
    @dbus.service.method(INTERFACE, in_signature='', out_signature='d')
    def get_cpu_percent(self):
        return self.ballconf.get_cpu_percent()
        
    # get total memory
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_total_memory(self):
        return self.ballconf.get_total_memory()

    # get used memory
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_used_memory(self):
        return self.ballconf.get_used_memory()

    # get free memory
    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_free_memory(self):
        return self.ballconf.get_free_memory()

    # get network flow total, return (up, down)
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_network_flow_total(self):
        return self.ballconf.get_network_flow_total()

    # get network flow, return (up, down)
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def get_network_flow(self):
        speed_network = self.ballconf.get_network_flow()
        self.get_network_speed(speed_network)

    # clean up memory
    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def cleanup_memory(self):
        self.ballconf.cleanup_memory()

    # -------------------------monitorball end-------------------------

    # a dbus method which means scan complete
    @dbus.service.signal(INTERFACE, signature='s')
    def scan_complete(self, msg):
        pass

    # a dbus method which means clean complete by main one key 
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete_main(self, msg):
        pass

    # a dbus method which means clean complete by second one key 
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete_second(self, msg):
        pass

    # a dbus method which means clean complete
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete(self, msg):
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

    # the function of clean cruft by main one key
    ###input-['history', 'cach....] output-''
    @dbus.service.method(INTERFACE, in_signature='as', out_signature='', sender_keyword='sender')
    def clean_by_main_one_key(self, mode_list, sender=None):
        #mode_list = ['history', 'cookies', 'cache', 'unneed']
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.clean_complete_main_msg('')
            return
        flag_str = ''
        #tmp_mode_list = self.dbusstring_to_string(mode_list)
        cruft_dic = {}
        cruft_dic = self.daemononekey.get_scan_result(mode_list)
        if 'history' in cruft_dic:
            history_cruft_list = cruft_dic['history']
            daemonhistory = cleaner.CleanTheHistory()
            try:
                daemonhistory.clean_the_cruftlist()
            except Exception, e:
                self.clean_error_main_msg('he')
            else:
                self.clean_complete_main_msg('h')

        if 'cookies' in cruft_dic:
            cookies_cruft_list = cruft_dic['cookies']
            daemoncookies = cleaner.CleanTheCookies()
            try:
                daemoncookies.clean_the_cruftlist(cookies_cruft_list)
            except Exception, e:
                self.clean_error_main_msg('ke')
            else:
                self.clean_complete_main_msg('k')

        if 'unneed' in cruft_dic:
            unneed_cruft_list = cruft_dic['unneed']
            try:
                self.daemonclean.clean_the_package(unneed_cruft_list)
            except Exception, e:
                self.clean_error_main_msg('ue')
            else:
                self.clean_complete_main_msg('u')

        if 'cache' in cruft_dic:
            cache_cruft_list = cruft_dic['cache']
            try:
                self.daemonclean.clean_the_file(cache_cruft_list)
            except Exception, e:
                self.clean_error_main_msg('ce')
            else:
                self.clean_complete_main_msg('c')
        self.clean_complete_main_msg('o')

    # the function of clean cruft by second one key
    ###input-['history', 'cach....] output-''
    @dbus.service.method(INTERFACE, in_signature='as', out_signature='', sender_keyword='sender')
    def clean_by_second_one_key(self, mode_list, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            self.clean_complete_second_msg('')
            return
        flag_str = ''
        #mode_list = ['history', 'cookies', 'cache', 'unneed']
        #tmp_mode_list = self.dbusstring_to_string(mode_list)
        cruft_dic = self.daemononekey.get_scan_result(mode_list)
        if 'history' in cruft_dic:
            history_cruft_list = cruft_dic['history']
            daemonhistory = cleaner.CleanTheHistory()
            try:
                daemonhistory.clean_the_cruftlist()
            except Exception, e:
                self.clean_error_second_msg('he')
            else:
                self.clean_complete_second_msg('h')

        if 'cookies' in cruft_dic:
            cookies_cruft_list = cruft_dic['cookies']
            daemoncookies = cleaner.CleanTheCookies()
            try:
                daemoncookies.clean_the_cruftlist(cookies_cruft_list)
            except Exception, e:
                self.clean_error_second_msg('ke')
            else:
                self.clean_complete_second_msg('k')

        if 'unneed' in cruft_dic:
            unneed_cruft_list = cruft_dic['unneed']
            try:
                self.daemonclean.clean_the_package(unneed_cruft_list)
            except Exception, e:
                self.clean_error_second_msg('ue')
            else:
                self.clean_complete_second_msg('u')

        if 'cache' in cruft_dic:
            cache_cruft_list = cruft_dic['cache']
            try:
                self.daemonclean.clean_the_file(cache_cruft_list)
            except Exception, e:
                self.clean_error_second_msg('ce')
            else:
                self.clean_complete_second_msg('c')
        self.clean_complete_second_msg('o')

    @dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
    def clean_history_records(self, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            return
        daemonhistory = cleaner.CleanTheHistory()
        try:
            daemonhistory.clean_the_cruftlist()
        except Exception, e:
            self.clean_error_msg('history')
        else:
            self.clean_complete_msg('history')

    ### input-['domain','dom...]   output-''
    @dbus.service.method(INTERFACE, in_signature='as', out_signature='', sender_keyword='sender')
    def clean_cookies_records(self, cruftlist, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            return
        daemoncookies = cleaner.CleanTheCookies()
        try:
            daemoncookies.clean_the_cruftlist(cruftlist)
        except Exception, e:
            self.clean_error_msg('cookies')
        else:
            self.clean_complete_msg('cookies')

    # the function of clean files
    ### input-['filepath', 'file...]   output-''
    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='', sender_keyword='sender')
    def clean_file_cruft(self, cruftlist, flagstr, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            return
        try:
            self.daemonclean.clean_the_file(cruftlist)
        except Exception, e:
            self.clean_error_msg(flagstr)
        else:
            self.clean_complete_msg(flagstr)

    # the function of clean packages
    ### input-['packagename', 'pack...]   output-''
    @dbus.service.method(INTERFACE, in_signature='as', out_signature='', sender_keyword='sender')
    def clean_package_cruft(self, cruftlist, sender=None):
        status = self._check_permission(sender, UK_ACTION_YOUKER)
        if not status:
            return
        try:
            self.daemonclean.uninstall_the_package(cruftlist)
            #self.daemonclean.clean_the_package(cruftlist)
        except Exception, e:
            self.clean_error_msg('package')
        else:
            self.clean_complete_msg('package')

    def dbusstring_to_string(self, string):
        tmp_string = str(string)
        patt = "u'[\S]+'"
        tmp_list = re.findall(patt, tmp_string)
        return [ok.split("'")[1] for ok in tmp_list]

    def scan_complete_msg(self, para):
        self.scan_complete(para)

    def clean_complete_main_msg(self, para):
        self.clean_complete_main(para)

    def clean_complete_second_msg(self, para):
        self.clean_complete_second(para)

    def clean_complete_msg(self, para):
        self.clean_complete(para)

    def clean_error_msg(self, para):
        self.clean_error(para)

    def clean_error_main_msg(self, para):
        self.clean_error_main(para)

    def clean_error_second_msg(self, para):
        self.clean_error_second(para)

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    mainloop = GObject.MainLoop()
    Daemon(dbus.SystemBus(), mainloop)
    mainloop.run()
