#!/usr/bin/python3
# -*- coding: utf-8 -*-

# Copyright (C) 2010 Canonical
#
# Authors:
#  Michael Vogt
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

from gi.repository import GObject

import logging
# import os

LOG = logging.getLogger(__name__)


class LoginBackend(GObject.GObject):

    NEW_ACCOUNT_URL = None
    FORGOT_PASSWORD_URL = None

    __gsignals__ = {
        "login-successful": (GObject.SIGNAL_RUN_LAST,
                             GObject.TYPE_NONE,
                             (GObject.TYPE_PYOBJECT,),
                             ),
        "login-failed": (GObject.SIGNAL_RUN_LAST,
                         GObject.TYPE_NONE,
                         (),
                         ),
        "login-canceled": (GObject.SIGNAL_RUN_LAST,
                           GObject.TYPE_NONE,
                           (),
                           ),
        "need-username-password": (GObject.SIGNAL_RUN_LAST,
                                   GObject.TYPE_NONE,
                                   (),
                                   ),
        "logout-successful": (GObject.SIGNAL_RUN_LAST,
                              GObject.TYPE_NONE,
                              (),
                              ),
    }

    def login(self):
        raise NotImplemented

    def login_or_register(self):
        raise NotImplemented

    def find_credentials(self):
        raise NotImplemented

    def cancel_login(self):
        self.emit("login-canceled")

    def logout(self):
        raise NotImplemented


def get_login_backend(window_id, appname, help_text):
    """
    factory that returns an SSO loader singleton
    """
    # if "SOFTWARE_CENTER_FAKE_REVIEW_API" in os.environ:
    #     from backend.login_impl.login_fake import (
    #         LoginBackendDbusSSOFake)
    #     sso_class = LoginBackendDbusSSOFake(window_id, appname, help_text)
    #     LOG.warn('Using fake login SSO functionality. Only meant for '
    #         'testing purposes')
    # else:
    from sso.login_impl.login_sso import (
        LoginBackendDbusSSO)
    sso_class = LoginBackendDbusSSO(window_id, appname, help_text)
    return sso_class


#if __name__ == "__main__":
#    logging.basicConfig(level=logging.DEBUG)

#    from models.enums import SOFTWARE_CENTER_NAME_KEYRING
#    login = get_login_backend(0, SOFTWARE_CENTER_NAME_KEYRING, "login-text")
#    login.login()

#    from gi.repository import Gtk
#    Gtk.main()
