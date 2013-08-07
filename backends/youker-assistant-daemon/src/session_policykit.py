#!/usr/bin/python
# -*- coding: utf-8 -*-
# This class is modified from gnome-lirc-properties project
# the original file is gnome_lirc_properties/backend.py
# GPL v2+
### BEGIN LICENSE
# Copyright (C) 2008 Fluendo Embedded S.L.
# Copyright (C) 2010 TualatriX <tualatrix@gmail.com>
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

class AccessDeniedException(dbus.DBusException):
    '''This exception is raised when some operation is not permitted.'''

    _dbus_error_name = 'com.ubuntukylin.IhuSession.AccessDeniedException'


class PolicyKitService(dbus.service.Object):
    '''A D-BUS service that uses PolicyKit for authorization.'''

    def _check_permission(self, sender, action):
        '''
        Verifies if the specified action is permitted, and raises
        an AccessDeniedException if not.

        The caller should use ObtainAuthorization() to get permission.
        '''

        try:
            if sender:
                kit = dbus.SessionBus().get_object('org.freedesktop.PolicyKit1', '/org/freedesktop/PolicyKit1/Authority')
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
                    raise AccessDeniedException('System not authorized by PolicyKit')

        except AccessDeniedException:
            raise

        except dbus.DBusException as ex:
            raise AccessDeniedException(ex.message)
