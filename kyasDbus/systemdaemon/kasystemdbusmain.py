#!/usr/bin/python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
 # Copyright (C) 2021 KylinSoft Co., Ltd.
 #
 # Authors:
 #  Yang Min yangmin@kylinos.cn
 #
 # This program is free software; you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
### END LICENSE

from gi.repository import GLib

import os
import dbus
import signal
import dbus.service
import dbus.mainloop.glib

from kahwinfo import *
from kacpufm import *
from kadevmonitor import *

DBUSNAME = "com.kylin.assistant.systemdaemon"

class DemoException(dbus.DBusException):
    _dbus_error_name = "com.kylin.assistant.systemdaemon.KyasException"

class TestObject(dbus.service.Object):
    INTERFACE = "com.example.interface"
    def __init__(self, system_bus, mainloop):
        dbus.service.Object.__init__(self, system_bus,
                                     "/MyObject")
        self.mainloop = mainloop

    @dbus.service.method(INTERFACE,
                         in_signature = 's', out_signature = 'as')
    def HelloWorld(self, hello_message):
        print(str(hello_message))
        return ["Hello", "from example-service.py", "with unique name",
                bus.get_unique_name()]

    @dbus.service.method(INTERFACE,
                         in_signature = '', out_signature = 'ss')
    def GetTuple(self):
        return ("Hello Tuple", " from example-service.py")

    @dbus.service.method(INTERFACE,
                         in_signature = '', out_signature = '')
    def RaiseException(self):
        raise DemoException("The RaiseException method does what you might "
                            'expect')

    @dbus.service.method(INTERFACE,
                         in_signature = '', out_signature = '')
    def Exit(self):
        self.mainloop.quit()

if __name__ == '__main__':
    os.environ["TERM"] = "xterm"
    os.environ["PATH"] = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/X11R6/bin"

    dbus.mainloop.glib.DBusGMainLoop(set_as_default = True)
    mainloop = GLib.MainLoop()

    bus = dbus.SystemBus()
    name = dbus.service.BusName(DBUSNAME, bus)
    signal.signal(signal.SIGINT, lambda : mainloop.quit())
    ##obj = TestObject(bus, mainloop)
    obj = HardwareInfo(bus, mainloop)
    objCpuFM = KACpuFM(bus, mainloop)
    objDevMonitor = KADevMonitor(bus, mainloop)

    print("Running kyas_system_service...\n")
    mainloop.run()
    print("Ending kyas_system_service...\n")
    if objDevMonitor.cpuTimer :
        objDevMonitor.cpuTimer.cancel()
