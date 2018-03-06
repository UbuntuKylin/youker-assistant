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

from gi.repository import GObject, GLib
from gettext import gettext as _

import logging
# import os

import piston_mini_client.auth
import piston_mini_client.failhandlers

# mostly for testing
#from fake_review_settings import FakeReviewSettings, network_delay
#from spawn_helper import SpawnHelper

from .login import get_login_backend

from .piston.ubuntusso_pristine import (
    UbuntuSsoAPI as PristineUbuntuSsoAPI,
)
# patch default_service_root to the one we use
from .enums import UBUNTU_KYLIN_SSO_SERVICE
# *Don't* append /api/1.0, as it's already included in UBUNTU_SSO_SERVICE
PristineUbuntuSsoAPI.default_service_root = UBUNTU_KYLIN_SSO_SERVICE

from .enums import (
    SOFTWARE_CENTER_NAME_KEYRING,
    SOFTWARE_CENTER_SSO_DESCRIPTION,
)
import dbus

LOG = logging.getLogger(__name__)


class UbuntuSSO(GObject.GObject):
    """ Ubuntu SSO interface using the oauth token from the keyring

    The methods that work synchronously are suffixed with _sync()
    """
    __gsignals__ = {
        "whoami": (GObject.SIGNAL_RUN_LAST,
                   GObject.TYPE_NONE,
                   (GObject.TYPE_PYOBJECT,),
                   ),
        "logout": (GObject.SIGNAL_RUN_LAST,
                   GObject.TYPE_NONE,
                   (),
                   ),
        "fail":   (GObject.SIGNAL_RUN_LAST,
                   GObject.TYPE_NONE,
                   (),
                   ),
        "error": (GObject.SIGNAL_RUN_LAST,
                  GObject.TYPE_NONE,
                  (GObject.TYPE_PYOBJECT,),
                  ),
    }

    def __init__(self,  xid=0):
        GObject.GObject.__init__(self)
        self.oauth = None
        self.xid = xid
        self.show_register = True
        self.sso = get_login_backend(
            self.xid,
            SOFTWARE_CENTER_NAME_KEYRING,
            _(SOFTWARE_CENTER_SSO_DESCRIPTION))
        self.sso.connect("login-successful", self._dbus_maybe_login_successful)
        self.sso.connect("login-failed", self._fail)
        self.sso.connect("login-canceled",  self._fail)
        self.sso.connect("logout-successful", self._logout_successful)

    def set_show_register(self, show):
        self.show_register = not not show

    def whoami(self, token):
        auth = piston_mini_client.auth.OAuthAuthorizer(
            token["token"], token["token_secret"],
            token["consumer_key"], token["consumer_secret"])
        api = PristineUbuntuSsoAPI(auth=auth)
        try:
            res = api.whoami()
        except piston_mini_client.failhandlers.APIError as e:
            print("api.whoami failed with APIError: '%s'" % e)
            LOG.exception("api.whoami failed with APIError: '%s'" % e)
        if len(res) == 0:
            self.emit("error")
            self.oauth = None
        else:
            self.emit("whoami", res)

    def _dbus_maybe_login_successful(self, sso_backend, oauth_result):
#        LOG.debug("_login_successful")
        # print("ubuntusso::_login_successful oauth_result: %s" % oauth_result)
        self.oauth = oauth_result
        self.whoami(self.oauth)
        # self.loop.quit()

#     def verify_token(self, token):
#         """ Verify that the token is valid
#
#             Note that this may raise httplib2 exceptions if the server
#             is not reachable
#         """
# #        LOG.debug("verify_token")
#         auth = piston_mini_client.auth.OAuthAuthorizer(
#             token["token"], token["token_secret"],
#             token["consumer_key"], token["consumer_secret"])
#         api = PristineUbuntuSsoAPI(auth=auth)
#         try:
#             res = api.whoami()
#         except piston_mini_client.failhandlers.APIError as e:
#             print "api.whoami failed with APIError: '%s'" % e
#             LOG.exception("api.whoami failed with APIError: '%s'" % e)
#             return False
#         return len(res) > 0

    def clear_token(self):
        # clear_token_from_ubuntu_sso_sync(SOFTWARE_CENTER_NAME_KEYRING)
        # sso = self. _get_login_backend_and_connect()
        self.sso.logout()
        # GLib.timeout_add_seconds(2, self.loop.quit())
        # self.loop.run()
        # return True

    # def _get_login_backend_and_connect(self):
    #     sso = get_login_backend(
    #         self.xid,
    #         SOFTWARE_CENTER_NAME_KEYRING,
    #         _(SOFTWARE_CENTER_SSO_DESCRIPTION))
    #     sso.connect("login-successful", self._dbus_maybe_login_successful)
    #     sso.connect("login-failed", self._fail)
    #     sso.connect("login-canceled",  self._fail)
    #     sso.connect("logout-successful", self._logout_successful)
    #     return sso

    def _fail(self, sso_backend):
        self.emit("fail")

    def _logout_successful(self, sso_backend):
        self.oauth = None
        self.emit("logout")

    def find_oauth_token(self):
        self.oauth = None
        # sso = self. _get_login_backend_and_connect()
        self.sso.find_credentials()
        # self.loop.run()
        # return self.oauth

    def get_oauth_token(self):
        self.oauth = None
        # sso = self. _get_login_backend_and_connect()
        if self.show_register:
            self.sso.login_or_register()
        else:
            self.sso.login()
        # self.loop.run()
        # return self.oauth

    # def get_oauth_token_and_verify(self, no_relogin=False):
    #     token = self.oauth
    #     # check if the token is valid and reset it if not
    #     if token:
    #         # verify token will return false if there is a API error,
    #         # but there may be httplib2 errors if there is no network,
    #         # so ignore them
    #         try:
    #             if not self.verify_token(token):
    #                 attempt_relogin = not no_relogin
    #                 if attempt_relogin:
    #                     self.clear_token()
    #                     # re-trigger login once
    #                     token = self.get_oauth_token()
    #                 else:
    #                     return None
    #         except Exception as e:
    #             print "token could not be verified (network problem?): %s" % e
    #             LOG.warn(
    #                 "token could not be verified (network problem?): %s" % e)
    #     return token
    #
    # def find_oauth_token_and_verify(self):
    #     token = self.find_oauth_token()
    #     # check if the token is valid and reset it if not
    #     if token:
    #         # verify token will return false if there is a API error,
    #         # but there may be httplib2 errors if there is no network,
    #         # so ignore them
    #         try:
    #             self.verify_token(token)
    #         except Exception as e:
    #             print "token could not be verified (network problem?): %s" % e
    #             LOG.warn(
    #                 "token could not be verified (network problem?): %s" % e)
    #     return token


def get_ubuntu_sso_backend(): #get_ubuntu_sso_backend(xid):
    """
    factory that returns an ubuntu sso loader singleton
    """
    # if "SOFTWARE_CENTER_FAKE_REVIEW_API" in os.environ:
    #     ubuntu_sso_class = UbuntuSSOAPIFake()
    #     LOG.warn('Using fake Ubuntu SSO API. Only meant for testing purposes')
    # else:
    ubuntu_sso_class = UbuntuSSO() #UbuntuSSO(xid)
    return ubuntu_sso_class


# # test code
# def _login_success(lp, token):
#     print "success", lp, token
#
#
# def _login_failed(lp):
#     print "fail", lp
#
#
# def _login_need_user_and_password(sso):
#     import sys
#     sys.stdout.write("user: ")
#     sys.stdout.flush()
#     user = sys.stdin.readline().strip()
#     sys.stdout.write("pass: ")
#     sys.stdout.flush()
#     password = sys.stdin.readline().strip()
#     sso.login(user, password)
#
#
# # interactive test code
# if __name__ == "__main__":
#     def _whoami(sso, result):
#         print "res: ", result
#         Gtk.main_quit()
#
#     def _error(sso, result):
#         print "err: ", result
#         Gtk.main_quit()
#
#     def _dbus_maybe_login_successful(ssologin, oauth_result):
#         print "got token, verify it now"
#         sso = UbuntuSSO()
#         sso.connect("whoami", _whoami)
#         sso.connect("error", _error)
#         sso.whoami()
#
#     from gi.repository import Gtk
# #    logging.basicConfig(level=logging.DEBUG)
#     # softwarecenter.paths.datadir = "./data"
#
#     backend = get_login_backend("", "appname", "help_text")
#     backend.connect("login-successful", _dbus_maybe_login_successful)
#     backend.login_or_register()
#     Gtk.main()
