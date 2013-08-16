#!/usr/bin/python

# Copyright (C) 2007-2011 Tualatrix Chou <tualatrix@gmail.com>
#
# The class AptAuth is modified from softwareproperty. Author: Michael Vogt <mvo@debian.org>
# The original file is: softwareproperties/AptAuth.py
# GPL v2+
# Copyright (c) 2004 Canonical

import sys
reload(sys)
sys.setdefaultencoding('utf8')
import os
import glob
import fcntl
import shutil
import logging
import tempfile
import subprocess

from subprocess import PIPE

import apt
import apt_pkg
import dbus
import dbus.service
import dbus.mainloop.glib
from gi.repository import GObject

from server import PolicyKitService
from policykit import UK_ACTION_YOUKER
PK_ACTION_SOURCE = 'com.ubuntu-tweak.daemon.edit-sources'
log = logging.getLogger('Daemon')


INTERFACE = "com.ubuntukylin_tools.daemon"
PATH = "/"

class Daemon(PolicyKitService):
    #TODO use signal
    def __init__ (self, bus, mainloop):
        bus_name = dbus.service.BusName(INTERFACE, bus=bus)
        PolicyKitService.__init__(self, bus_name, PATH)
        self.mainloop = mainloop

    @dbus.service.method(INTERFACE,
                         in_signature='', out_signature='s')
    def get_user_cache(self):
        return "KOBE"

    @dbus.service.method(INTERFACE,
                         in_signature='', out_signature='s',
                         sender_keyword='sender')
    def set_source_enable(self, sender=None):
        self._check_permission(sender, UK_ACTION_YOUKER)
        #self._check_policykit(sender)
        return "LIXIANG"

    @dbus.service.method(INTERFACE,
                        in_signature='', out_signature='')
    def exit(self):
        self.mainloop.quit()

if __name__ == '__main__':
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    mainloop = GObject.MainLoop()
    Daemon(dbus.SystemBus(), mainloop)
    mainloop.run()
