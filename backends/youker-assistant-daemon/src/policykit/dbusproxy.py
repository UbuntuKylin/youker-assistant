#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2007-2011 Tualatrix Chou <tualatrix@gmail.com>
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

import dbus
import logging

#log = logging.getLogger("DbusProxy")

SHOWED = False

def show_message(*args):
    from gui.dialogs import ErrorDialog
    message = 'Youker Assisant systemdaemon has error.'
    ErrorDialog(message=message).launch()

def nothing(*args):
    return None

class DbusProxy:
    INTERFACE = "com.ubuntukylin_tools.daemon"
    try:
        __system_bus = dbus.SystemBus()
        __object = __system_bus.get_object('com.ubuntukylin_tools.daemon', '/')
    except Exception, e:
        #log.error(e)
        __object = None

    def __getattr__(self, name):
        global SHOWED
        try:
            return self.__object.get_dbus_method(name, dbus_interface=self.INTERFACE)
        except Exception, e:
            #log.error(e)
            if not SHOWED:
                SHOWED = True
                return show_message
            else:
                return nothing

    def get_object(self):
        return self.__object

proxy = DbusProxy()

if __name__ == '__main__':
    print proxy
