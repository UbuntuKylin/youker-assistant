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

import cleaner
from subprocess import PIPE
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GObject
from server import PolicyKitService
from softwarecenter.apt_daemon import FetchProcess
from softwarecenter.apt_daemon import AptProcess
from softwarecenter.apt_daemon import AptDaemon
log = logging.getLogger('SudoDaemon')

INTERFACE = "com.ubuntukylin.Ihu"
PATH = "/"

class SudoDaemon(PolicyKitService):
    def __init__ (self, bus, mainloop):
        bus_name = dbus.service.BusName(INTERFACE, bus=bus)
        PolicyKitService.__init__(self, bus_name, PATH)
        self.mainloop = mainloop
        self.daemonclean = cleaner.FunctionOfClean()
        self.daemonApt = AptDaemon(self)

    @dbus.service.signal(INTERFACE, signature='s')
    def work_finish(self, msg):
        pass

    def start_to_emit_signal(self, msg):
        self.work_finish(msg)

    # a dbus method which means clean complete
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_complete(self, msg):
        pass

    # a dbus method which means an error occurred
    @dbus.service.signal(INTERFACE, signature='s')
    def clean_error(self, msg):
        pass

    @dbus.service.method(INTERFACE, in_signature='', out_signature='s')
    def get_sudo_daemon(self):
        return "SudoDaemon"

    @dbus.service.method(INTERFACE, in_signature='', out_signature='')
    def exit(self):
        self.mainloop.quit()


    # the function of clean packages
    ### input-['packagename', 'pack...]   output-''
    @dbus.service.method(INTERFACE, in_signature='as', out_signature='')
    def clean_package_cruft(self, cruftlist):
        try:
            self.daemonclean.clean_the_package(cruftlist)
        except Exception, e:
            self.clean_error_msg('package')
        else:
            self.clean_complete_msg('package')

    def clean_complete_msg(self, para):
        self.clean_complete(para)

    def clean_error_msg(self, para):
        self.clean_error(para)

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
        self.daemonApt.check_pkgs_status(pkgNameList)

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
    @dbus.service.signal(INTERFACE, signature='a{sv}')
    def software_check_status_signal(self, statusDict):
        pass