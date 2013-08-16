# Ubuntu Tweak - Ubuntu Configuration Tool
#
# Copyright (C) 2007-2011 Tualatrix Chou <tualatrix@gmail.com>
#
# Ubuntu Tweak is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# Ubuntu Tweak is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Ubuntu Tweak; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA

import dbus
import logging

#log = logging.getLogger("DbusProxy")

SHOWED = False

def show_message(*args):
    from gui.dialogs import ErrorDialog
    message = 'The UbuntuKylin Tools daemon error'
    ErrorDialog(message=message).launch()

def nothing(*args):
    return None

class DbusProxy:
    INTERFACE = "com.ubuntukylin.Ihu"
    print '0'
    try:
        print '1'
        __system_bus = dbus.SystemBus()
        print '2'
        __object = __system_bus.get_object('com.ubuntukylin.Ihu', '/')
        print '3'
    except Exception, e:
        #log.error(e)
        print '1111'
        print e
        __object = None

    def __getattr__(self, name):
        global SHOWED
        print '4'
        print name
        try:
            print '5'
            return self.__object.get_dbus_method(name, dbus_interface=self.INTERFACE)
        except Exception, e:
            #log.error(e)
            print '2222'
            print e
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
