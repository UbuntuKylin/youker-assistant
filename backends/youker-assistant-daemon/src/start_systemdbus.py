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

import os, sys
import signal
import dbus
import dbus.mainloop.glib
from gi.repository import GObject
from single import SingleInstance
#import gobject

if __name__ == '__main__':
    myapp = SingleInstance("/tmp/youker-assistant-systemdbus-%d.pid" % os.getuid())
    if myapp.is_already_running():
        print "Another instance of this systemdbus is already running"
        sys.exit("Another instance of this systemdbus is already running")
    os.environ["TERM"] = "xterm"
    os.environ["PATH"] = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/X11R6/bin"
    os.environ["DEBIAN_FRONTEND"] = "noninteractive"
    if os.path.exists("/var/lib/apt/lists/lock"):
        os.remove("/var/lib/apt/lists/lock")
    from systemdbus.daemon import Daemon
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    GObject.threads_init()
    mainloop = GObject.MainLoop()
    #gobject.threads_init()
    #mainloop = gobject.MainLoop()
    signal.signal(signal.SIGINT, lambda : mainloop.quit())
    Daemon(dbus.SystemBus(), mainloop)
    mainloop.run()
