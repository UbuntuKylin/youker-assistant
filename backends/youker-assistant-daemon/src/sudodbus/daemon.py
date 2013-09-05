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
log = logging.getLogger('SudoDaemon')

INTERFACE = "com.ubuntukylin.Ihu"
PATH = "/"

class SudoDaemon(PolicyKitService):
    def __init__ (self, bus, mainloop):
        bus_name = dbus.service.BusName(INTERFACE, bus=bus)
        PolicyKitService.__init__(self, bus_name, PATH)
        self.mainloop = mainloop
        self.daemonclean = cleaner.FunctionOfClean()

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
