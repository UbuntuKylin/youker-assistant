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

log = logging.getLogger('Daemon')

INTERFACE = "com.ubuntukylin_tools.daemon"
PATH = "/"
#PATH = "/com/ubuntukylin_assistant/daemon"
TIMEFORMAT = "%H:%M:%S"

class Daemon(PolicyKitService):
    def __init__ (self, bus, mainloop):
        #self.sysconf = Sysinfo()
        self.otherconf = Others()
        self.soundconf = Sound()
        self.daemonsame = cleaner.SearchTheSame()
        self.daemonlarge = cleaner.ManageTheLarge()
        self.daemonunneed = cleaner.CleanTheUnneed()
        self.daemonclean = cleaner.FunctionOfClean()
        self.daemononekey = cleaner.OneKeyClean()
        self.daemoncache = cleaner.CleanTheCache()
        bus_name = dbus.service.BusName(INTERFACE, bus=bus)
        PolicyKitService.__init__(self, bus_name, PATH)
        self.mainloop = mainloop

    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def exit(self):
        self.mainloop.quit()

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_homedir(self, homedir):
        self.soundconf.set_homedir(homedir)

    @dbus.service.method(INTERFACE, in_signature='s', out_signature='')
    def set_user_homedir(self, homedir):
        self.daemononekey.get_user_homedir(homedir)
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    #def get_user_cache(self):
    #    return "KOBE"

    #@dbus.service.method(INTERFACE, in_signature='', out_signature='s', sender_keyword='sender')
    #def set_source_enable(self, sender=None):
    #    self._check_permission(sender, UK_ACTION_YOUKER)
    #    return "LIXIANG"

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_system_daemon(self):
        return "SystemDaemon"

    # -------------------------sound-------------------------
    # get sound themes
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as', sender_keyword='sender')
    #def get_sound_themes(self, sender=None):
    @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    def get_sound_themes(self):
        #self._check_permission(sender, UK_ACTION_YOUKER)
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
        self._check_permission(sender, UK_ACTION_YOUKER)
        flag_str = ''
        tmp_mode_list = self.dbusstring_to_string(mode_list)
        cruft_dic = {}
        cruft_dic = self.daemononekey.get_scan_resault(tmp_mode_list)
        #if 'history' in cruft_dic:
        #    history_cruft_list = cruft_dic['history']
        #    daemonhistory = cleaner.CleanTheHistory()
        #    try:
        #        daemonhistory.clean_the_cruftlist()
        #    except Exception, e:
        #        self.clean_error_main_msg('he')
        #    else:
        #        self.clean_complete_main_msg('h')

        #if 'cookies' in cruft_dic:
        #    cookies_cruft_list = cruft_dic['cookies']
        #    daemoncookies = cleaner.CleanTheCookies()
        #    try:
        #        daemoncookies.clean_the_cruftlist(cookies_cruft_list)
        #    except Exception, e:
        #        self.clean_error_main_msg('ke')
        #    else:
        #        self.clean_complete_main_msg('k')

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

    # the function of clean cruft by second one key
    ###input-['history', 'cach....] output-''
    @dbus.service.method(INTERFACE, in_signature='as', out_signature='', sender_keyword='sender')
    def clean_by_second_one_key(self, mode_list, sender=None):
        self._check_permission(sender, UK_ACTION_YOUKER)
        flag_str = ''
        tmp_mode_list = self.dbusstring_to_string(mode_list)
        cruft_dic = self.daemononekey.get_scan_resault(tmp_mode_list)
        #if 'history' in cruft_dic:
        #    history_cruft_list = cruft_dic['history']
        #    daemonhistory = cleaner.CleanTheHistory()
        #    try:
        #        daemonhistory.clean_the_cruftlist()
        #    except Exception, e:
        #        self.clean_error_second_msg('he')
        #    else:
        #        self.clean_complete_second_msg('h')

        #if 'cookies' in cruft_dic:
        #    cookies_cruft_list = cruft_dic['cookies']
        #    daemoncookies = cleaner.CleanTheCookies()
        #    try:
        #        daemoncookies.clean_the_cruftlist(cookies_cruft_list)
        #    except Exception, e:
        #        self.clean_error_second_msg('ke')
        #    else:
        #        self.clean_complete_second_msg('k')

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

    # the function of search the same file below path
    ### input-'path'  output-['filea<2_2>filea','fileb<2_2>fileb'....]
    #@dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    #def scan_of_same(self, path):
    #    tmp_list = self.daemonsame.get_scan_resault(path)
    #    self.scan_complete_msg('same')
    #    return tmp_list

    # the function of sort the hundred files below path betown big to small
    ### input-'path'  output-['size<2_2>biggestfile<2_2>filestyle', 'size...]
    #@dbus.service.method(INTERFACE, in_signature='s', out_signature='as')
    #def scan_of_large(self, path):
    #    tmp_list = self.daemonlarge.get_scan_resault(path)
    #    self.scan_complete_msg('large')
    #    return tmp_list

    # the function of clean the history records
    ### input-''   output-['id<2_2>url<2_2>title<2_2>visitcount', 'id...]
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def scan_oldhistory_records(self):
    #    daemonhistory = cleaner.CleanTheHistory()
    #    return daemonhistory.get_scan_resault()

    # the function of clean the history records count
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='i')
    #def scan_history_records(self):
    #    daemonhistory = cleaner.CleanTheHistory()
    #    tmp_list = daemonhistory.get_scan_resault()
    #    self.scan_complete_msg('history')
    #    return sum([int(one.split('<2_2>')[-1]) for one in tmp_list])

    ### input-['id','id', 'i...]   output-''
    #@dbus.service.method(INTERFACE, in_signature='as', out_signature='')
    #def clean_history_records(self, cruftlist):
    #    daemonhistory = cleaner.CleanTheHistory()
    #    for cruft in cruftlist:
    #        try:
    #            flag = daemonhistory.clean_the_cruftlist(cruft)
    #        except Exception, e:
    #            self.clean_error_msg(e)
    #        else:
    #            if flag:
    #                self.clean_complete_msg(cruft)
    #            else:
    #                self.not_exist_msg(cruft)
    ### input-''   output-''
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='', sender_keyword='sender')
    #def clean_history_records(self, sender=None):
    #    self._check_permission(sender, UK_ACTION_YOUKER)
    #    daemonhistory = cleaner.CleanTheHistory()
    #    try:
    #        daemonhistory.clean_the_cruftlist()
    #    except Exception, e:
    #        self.clean_error_msg('history')
    #    else:
    #        self.clean_complete_msg('history')
         

    # the function of clean the cookies records
    ### input-''   output-['domain<2_2>number', 'dom...]
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def scan_cookies_records(self):
    #    daemoncookies = cleaner.CleanTheCookies()
    #    tmp_list = daemoncookies.get_scan_resault()
    #    self.scan_complete_msg('cookies')
    #    return tmp_list

    ### input-['domain','dom...]   output-''
    #@dbus.service.method(INTERFACE, in_signature='as', out_signature='', sender_keyword='sender')
    #def clean_cookies_records(self, cruftlist, sender=None):
    #    self._check_permission(sender, UK_ACTION_YOUKER)
    #    daemoncookies = cleaner.CleanTheCookies()
    #    try:
    #        daemoncookies.clean_the_cruftlist(cruftlist)
    #    except Exception, e:
    #        self.clean_error_msg('cookies')
    #    else:
    #        self.clean_complete_msg('cookies')

    # the function of scan the unneedpackages
    ### input-''   output-['pkgname<2_2>pkgsummary<2_2>installedsize', 'pkg...]
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def scan_unneed_packages(self):
    #    tmp_list = self.daemonunneed.get_scan_resault()
    #    self.scan_complete_msg('unneed')
    #    return tmp_list

    # the function of scan the cache
    ### input-''  output-'{'apt': 'filepath<2_2>size<1_1>filep...', 
    #                       'softwarecenter': 'filepath<2_2>size<1_1>filep...'}'
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='a{sv}')
    #def scan_cache_cruft(self):
    #    return self.daemoncache.get_scan_resault()

    # the function of scan the apt cache
    ### input-'' output-['filepath<2_2>size', 'filepath<2_2>size', 'file...]
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def scan_apt_cruft(self):
    #    tmp_dic = self.daemoncache.get_scan_resault()
    #    self.scan_complete_msg('apt')
    #    return tmp_dic['apt'].split('<1_1>')

    # the function of scan the softwarecenter cache
    ### input-'' output-['filepath<2_2>size', 'filepath<2_2>size', 'file...]
    #@dbus.service.method(INTERFACE, in_signature='', out_signature='as')
    #def scan_softwarecenter_cruft(self):
    #    tmp_dic = self.daemoncache.get_scan_resault()
    #    self.scan_complete_msg('softwarecenter')
    #    return tmp_dic['softwarecenter'].split('<1_1>')

    # the function of clean files
    ### input-['filepath', 'file...]   output-''
    @dbus.service.method(INTERFACE, in_signature='ass', out_signature='', sender_keyword='sender')
    def clean_file_cruft(self, cruftlist, flagstr, sender=None):
        self._check_permission(sender, UK_ACTION_YOUKER)
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
        self._check_permission(sender, UK_ACTION_YOUKER)
        try:
            self.daemonclean.clean_the_package(cruftlist)
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

    #def clean_complete_msg(self, para):
    #    if (para == "apt"):
    #        self.clean_complete_apt(para)
    #    else if (para == "software"):
    #        self.clean_complete_software(para)
    #    else if (para == "history"):
    #        self.clean_complete_history(para)
    #    else if (para == "cookies"):
    #        self.clean_complete_cookies(para)
    #    else if (para == "package"):
    #        self.clean_complete_package(para)

    def clean_error_msg(self, para):
        self.clean_error(para)

    def clean_error_main_msg(self, para):
        self.clean_error_main(para)

    def clean_error_second_msg(self, para):
        self.clean_error_second(para)


    #def test_signal(self, msg):
    #    self.pc_msg(msg)
if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    mainloop = GObject.MainLoop()
    Daemon(dbus.SystemBus(), mainloop)
    mainloop.run()
