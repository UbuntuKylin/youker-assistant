#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Copyright (C) 2010 Canonical
#
# Authors:
#  Michael Vogt
#  Robert <luolei@ubuntukylin.com>
#
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU General Public License as published by the Free Software
# Foundation; version 3.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

import dbus
import logging

from dbus.mainloop.glib import DBusGMainLoop
DBusGMainLoop(set_as_default=True)

from ubuntu_kylin_sso import (
    DBUS_BUS_NAME,
    DBUS_CREDENTIALS_IFACE,
    DBUS_CREDENTIALS_PATH,
)

from sso.login import LoginBackend

from sso.enums import SOFTWARE_CENTER_NAME_KEYRING

LOG = logging.getLogger(__name__)

def utf8(s):
    """
    Takes a string or unicode object and returns a utf-8 encoded
    string, errors are ignored
    """
    if s is None:
        return None
    if isinstance(s, str):
        return s.encode("utf-8", "ignore")
    return str(s, "utf8", "ignore").encode("utf8")

class LoginBackendDbusSSO(LoginBackend):

    def __init__(self, window_id, appname, help_text):
        super(LoginBackendDbusSSO, self).__init__()
        if not appname:
            self.appname = SOFTWARE_CENTER_NAME_KEYRING
        else:
            self.appname = appname
        self.help_text = help_text
        self.bus = dbus.SessionBus()
        obj = self.bus.get_object(bus_name=DBUS_BUS_NAME,
                                  object_path=DBUS_CREDENTIALS_PATH,
                                  follow_name_owner_changes=True)
        self.proxy = dbus.Interface(object=obj,
                               dbus_interface=DBUS_CREDENTIALS_IFACE)
        self.proxy.connect_to_signal("CredentialsFound",
                                     self._on_credentials_found)
        self.proxy.connect_to_signal("CredentialsNotFound",
                                     self._on_credentials_not_found)
        self.proxy.connect_to_signal("CredentialsError",
                                     self._on_credentials_error)
        self.proxy.connect_to_signal("AuthorizationDenied",
                                     self._on_authorization_denied)
        self.proxy.connect_to_signal("CredentialsCleared",
                                     self._on_credential_cleared)
        self._window_id = window_id
        self._credentials = None

    def _get_params(self):
        p = {}
        if self.help_text:
            p['help_text'] = utf8(self.help_text)
        if self._window_id:
            p['window_id'] = self._window_id
        return p

    def find_credentials(self):
        LOG.debug("find_credentials()")
        self._credentials = None
        self.proxy.find_credentials(self.appname, self._get_params())

    def login(self):
        LOG.debug("login()")
        self._credentials = None
        self.proxy.login(self.appname, self._get_params())

    def login_or_register(self):
        LOG.debug("login_or_register()")
        self._credentials = None
        # print "login_sso::login_or_register:", self.appname, self._get_params()
        self.proxy.register(self.appname, self._get_params())

    def logout(self):
        LOG.debug("login_or_register()")
        self._credentials = None
        self.proxy.clear_credentials(self.appname, {})

    def _on_credentials_not_found(self, app_name):
        LOG.debug("_on_credentials_not_found for '%s'" % app_name)
        if app_name != self.appname:
            return
        self.emit("login-failed")

    def _on_credentials_found(self, app_name, credentials):
        LOG.debug("_on_credentials_found for '%s'" % app_name)
        if app_name != self.appname:
            return
        # only emit signal here once, otherwise it may happen that a
        # different process that triggers the on the dbus triggers
        # another signal emission here!
        if self._credentials != credentials:
            self.emit("login-successful", credentials)
        self._credentials = credentials

    def _on_credentials_error(self, app_name, error, detailed_error=""):
        LOG.error("_on_credentials_error for %s: %s (%s)" % (
                app_name, error, detailed_error))
        if app_name != self.appname:
            return
        # FIXME: do something useful with the error
        self.emit("login-failed")

    def _on_authorization_denied(self, app_name):
        LOG.info("_on_authorization_denied: %s" % app_name)
        if app_name != self.appname:
            return
        self.cancel_login()
        self.emit("login-canceled")

    def _on_credential_cleared(self, app_name):
        LOG.info("_on_credential_cleared: %s" % app_name)
        if app_name != self.appname:
            return
        self.emit("logout-successful")
