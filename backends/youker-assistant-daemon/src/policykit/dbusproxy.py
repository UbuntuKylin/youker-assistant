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
import dbus.service
import logging

log = logging.getLogger("DbusProxy")

INTERFACE = 'com.ubuntukylin_tools.daemon'
PATH = '/'
SHOWED = False

def show_message(*args):
    from dialogs import ErrorDialog
    title = 'Daemon start failed'
    message = ('Youker Assisant systemdaemon didn\'t start correctly.\n'
                'If you want to help developers debugging, try to run "<b>sudo /usr/share/youker-assistant-daemon/src/youkersystem-daemon</b>" in a terminal.')
    ErrorDialog(title=title, message=message).launch()

def nothing(*args):
    return None

class DbusProxy:
    try:
        __system_bus = dbus.SystemBus()
        __object = __system_bus.get_object(INTERFACE, PATH)
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

class AccessDeniedException(dbus.DBusException):
    '''This exception is raised when some operation is not permitted.'''

    _dbus_error_name = 'com.ubuntukylin_tools.daemon.AccessDeniedException'


#def _check_policykit(self, sender):
#    if not sender: raise ValueError('sender == None')
#    bus = dbus.SystemBus()
#    proxy = bus.get_object('org.freedesktop.PolicyKit1', '/org/freedesktop/PolicyKit1/Authority')
#    authority = dbus.Interface(proxy, dbus_interface='org.freedesktop.PolicyKit1.Authority')
#    subject = ('system-bus-name', {'name' : sender})
#    action_id = DBUS_IFACE
#    details = {}
#    flags = 1            # AllowUserInteraction flag
#    cancellation_id = '' # No cancellation id
#    (granted, _, details) = authority.CheckAuthorization(subject, action_id, details, flags, cancellation_id, timeout=600)
#    return granted

def check_permission(self, sender, action):
    '''
    Verifies if the specified action is permitted, and raises
    an AccessDeniedException if not.

    The caller should use ObtainAuthorization() to get permission.
    '''

    try:
        if sender:
            kit = dbus.SystemBus().get_object('org.freedesktop.PolicyKit1', '/org/freedesktop/PolicyKit1/Authority')
            kit = dbus.Interface(kit, 'org.freedesktop.PolicyKit1.Authority')

            # Note that we don't use CheckAuthorization with bus name
            # details because we have no ways to get the PID of the
            # front-end, so we're left with checking that its bus name
            # is authorised instead
            # See http://bugzilla.gnome.org/show_bug.cgi?id=540912
            (granted, _, details) = kit.CheckAuthorization(
                            ('system-bus-name', {'name': sender}),
                            action, {}, dbus.UInt32(1), '', timeout=600)

            if not granted:
                raise AccessDeniedException('Session not authorized by PolicyKit')

    except AccessDeniedException:
        raise

    except dbus.DBusException, ex:
        raise AccessDeniedException(ex.message)


def init_dbus(dbus_iface=INTERFACE, dbus_path=PATH):
    '''init dbus'''
    proxy = DbusProxy()
    return proxy

if __name__ == '__main__':
    print init_dbus()
