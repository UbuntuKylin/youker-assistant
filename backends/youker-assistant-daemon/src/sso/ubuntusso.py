#!/usr/bin/python
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
#from gettext import gettext as _

#import logging
import os

import piston_mini_client.auth
import piston_mini_client.failhandlers

# mostly for testing
#from fake_review_settings import FakeReviewSettings, network_delay
from spawn_helper import SpawnHelper
from login import get_login_backend

from backend.piston.ubuntusso_pristine import (
    UbuntuSsoAPI as PristineUbuntuSsoAPI,
)
# patch default_service_root to the one we use
from enums import UBUNTU_SSO_SERVICE
# *Don't* append /api/1.0, as it's already included in UBUNTU_SSO_SERVICE
PristineUbuntuSsoAPI.default_service_root = UBUNTU_SSO_SERVICE

from enums import (
    SOFTWARE_CENTER_NAME_KEYRING,
    SOFTWARE_CENTER_SSO_DESCRIPTION,
)

from utils import clear_token_from_ubuntu_sso_sync

#LOG = logging.getLogger(__name__)


class UbuntuSSO(GObject.GObject):
    """ Ubuntu SSO interface using the oauth token from the keyring

    The methods that work synchronously are suffixed with _sync()
    """

    __gsignals__ = {
        "whoami": (GObject.SIGNAL_RUN_LAST,
                   GObject.TYPE_NONE,
                   (GObject.TYPE_PYOBJECT,),
                   ),
        "error": (GObject.SIGNAL_RUN_LAST,
                  GObject.TYPE_NONE,
                  (GObject.TYPE_PYOBJECT,),
                  ),
    }

    def __init__(self, xid=0):
        GObject.GObject.__init__(self)
        self.oauth = None
        self.xid = xid
        self.loop = GLib.MainLoop(GLib.main_context_default())
        self.show_register = True

    def setShowRegister(self, show):
        self.show_register = not not show

    def _on_whoami_data(self, spawner, piston_whoami):
        # once we have data, make sure to save it
        # config = get_config()
        # config.email = piston_whoami["preferred_email"]
        # config.reviews_username = piston_whoami["username"]
        # emit
        self.emit("whoami", piston_whoami)

    def whoami(self):
        """ trigger request for getting the account information, this
            will also verify if the current token is valid and if not,
            trigger a cleanup/re-authenticate
        """
#        LOG.debug("whoami called")
        spawner = SpawnHelper()
        spawner.connect("data-available", self._on_whoami_data)
        spawner.connect("error", lambda spawner, err: self.emit("error", err))
        spawner.needs_auth = True
        spawner.run_generic_piston_helper("UbuntuSsoAPI", "whoami")

    def _login_successful(self, sso_backend, oauth_result):
#        LOG.debug("_login_successful")
        # print("ubuntusso::_login_successful oauth_result: %s" % oauth_result)
        self.oauth = oauth_result
        self.loop.quit()

    # sync calls
    def verify_token_sync(self, token):
        """ Verify that the token is valid

            Note that this may raise httplib2 exceptions if the server
            is not reachable
        """
#        LOG.debug("verify_token")
        auth = piston_mini_client.auth.OAuthAuthorizer(
            token["token"], token["token_secret"],
            token["consumer_key"], token["consumer_secret"])
        api = PristineUbuntuSsoAPI(auth=auth)
        try:
            res = api.whoami()
        except piston_mini_client.failhandlers.APIError as e:
            LOG.exception("api.whoami failed with APIError: '%s'" % e)
            return False
        return len(res) > 0

    def clear_token(self):
        clear_token_from_ubuntu_sso_sync(SOFTWARE_CENTER_NAME_KEYRING)

    def _get_login_backend_and_connect(self):
        sso = get_login_backend(
            self.xid,
            SOFTWARE_CENTER_NAME_KEYRING,
            _(SOFTWARE_CENTER_SSO_DESCRIPTION))
        sso.connect("login-successful", self._login_successful)
        sso.connect("login-failed", lambda s: self.loop.quit())
        sso.connect("login-canceled", lambda s: self.loop.quit())
        return sso

    def find_oauth_token_sync(self):
        self.oauth = None
        sso = self. _get_login_backend_and_connect()
        sso.find_credentials()
        self.loop.run()
        return self.oauth

    def get_oauth_token_sync(self):
        self.oauth = None
        sso = self. _get_login_backend_and_connect()
        if self.show_register:
            sso.login_or_register()
        else:
            sso.login()
        self.loop.run()
        return self.oauth

    def get_oauth_token_and_verify_sync(self, no_relogin=False):
        token = self.get_oauth_token_sync()
        # check if the token is valid and reset it if not
        if token:
            # verify token will return false if there is a API error,
            # but there may be httplib2 errors if there is no network,
            # so ignore them
            try:
                if not self.verify_token_sync(token):
                    attempt_relogin = not no_relogin
                    if attempt_relogin:
                        self.clear_token()
                        # re-trigger login once
                        token = self.get_oauth_token_sync()
                    else:
                        return None
            except Exception as e:
                LOG.warn(
                    "token could not be verified (network problem?): %s" % e)
        return token

    def find_oauth_token_and_verify_sync(self):
        token = self.find_oauth_token_sync()
        # check if the token is valid and reset it if not
        if token:
            # verify token will return false if there is a API error,
            # but there may be httplib2 errors if there is no network,
            # so ignore them
            try:
                self.verify_token_sync(token)
            except Exception as e:
                LOG.warn(
                    "token could not be verified (network problem?): %s" % e)
        return token

# # decorator to add a fake network delay if set
# # in FakeReviewSettings.fake_network_delay
# def network_delay(fn):
#     def slp(self, *args, **kwargs):
#         # fake_settings = FakeReviewSettings()
#         # delay = fake_settings.get_setting('fake_network_delay')
#         delay = 2 #直接设置为2秒
#         if delay:
#             time.sleep(delay)
#         return fn(self, *args, **kwargs)
#     return slp
#
# class UbuntuSSOAPIFake(UbuntuSSO):
#
#     def __init__(self):
#         UbuntuSSO.__init__(self)
#         self._fake_settings = FakeReviewSettings()
#
#     @network_delay
#     def whoami(self):
#         if self._fake_settings.get_setting('whoami_response') == "whoami":
#             self.emit("whoami", self._create_whoami_response())
#         elif self._fake_settings.get_setting('whoami_response') == "error":
#             self.emit("error", self._make_error())
#
#     def _create_whoami_response(self):
#         username = (self._fake_settings.get_setting('whoami_username') or
#             "anyuser")
#         response = {
#                     u'username': username.decode('utf-8'),
#                     u'preferred_email': u'user@email.com',
#                     u'displayname': u'Fake User',
#                     u'unverified_emails': [],
#                     u'verified_emails': [],
#                     u'openid_identifier': u'fnerkWt'
#         }
#         return response
#
#     def _make_error():
#         return 'HTTP Error 401: Unauthorized'


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


# test code
def _login_success(lp, token):
    print "success", lp, token


def _login_failed(lp):
    print "fail", lp


def _login_need_user_and_password(sso):
    import sys
    sys.stdout.write("user: ")
    sys.stdout.flush()
    user = sys.stdin.readline().strip()
    sys.stdout.write("pass: ")
    sys.stdout.flush()
    password = sys.stdin.readline().strip()
    sso.login(user, password)


# interactive test code
if __name__ == "__main__":
    def _whoami(sso, result):
        print "res: ", result
        Gtk.main_quit()

    def _error(sso, result):
        print "err: ", result
        Gtk.main_quit()

    def _dbus_maybe_login_successful(ssologin, oauth_result):
        print "got token, verify it now"
        sso = UbuntuSSO()
        sso.connect("whoami", _whoami)
        sso.connect("error", _error)
        sso.whoami()

    from gi.repository import Gtk
#    logging.basicConfig(level=logging.DEBUG)
    # softwarecenter.paths.datadir = "./data"

    backend = get_login_backend("", "appname", "help_text")
    backend.connect("login-successful", _dbus_maybe_login_successful)
    backend.login_or_register()
    Gtk.main()
