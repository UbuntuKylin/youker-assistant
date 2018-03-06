# This class is modified from gnome-lirc-properties project
# the original file is gnome_lirc_properties/backend.py
# GPL v2+
# Copyright (C) 2008 Fluendo Embedded S.L.
# Copyright (C) 2010 TualatriX <tualatrix@gmail.com>
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd

import dbus.service

class AccessDeniedException(dbus.DBusException):
    '''This exception is raised when some operation is not permitted.'''

    _dbus_error_name = 'com.kylin.assistant.systemdaemon.AccessDeniedException'


class PolicyKitService(dbus.service.Object):
    '''A D-BUS service that uses PolicyKit for authorization.'''

    def _check_permission(self, sender, action):
        if not sender: raise ValueError('sender == None')
        kit = dbus.SystemBus().get_object('org.freedesktop.PolicyKit1', '/org/freedesktop/PolicyKit1/Authority')
        kit = dbus.Interface(kit, 'org.freedesktop.PolicyKit1.Authority')
        (granted, _, details) = kit.CheckAuthorization(
                        ('system-bus-name', {'name': sender}),
                        action, {}, dbus.UInt32(1), '', timeout=600)
        return granted
