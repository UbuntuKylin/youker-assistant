#!/usr/bin/python
# Copyright (C) 2011 Canonical
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

import httplib2
import argparse
import logging
import os
import json
import pickle
import sys


# useful for debugging
if "SOFTWARE_CENTER_DEBUG_HTTP" in os.environ:
    httplib2.debuglevel = 1

import piston_mini_client.auth
import piston_mini_client.failhandlers
from piston_mini_client.failhandlers import APIError

try:
    import backend
except ImportError:
    if os.path.exists("./backend"):
        sys.path.insert(0, os.path.abspath("./"))
    else:
        sys.path.insert(0, "/usr/share/ubuntu-kylin-software-center")

import models.enums
from models.enums import UKSC_CACHE_DIR

from backend.ubuntusso import UbuntuSSO

# the piston import
from backend.piston.ubuntusso_pristine import UbuntuSsoAPI
# from softwarecenter.backend.piston.rnrclient import RatingsAndReviewsAPI
# from softwarecenter.backend.piston.scaclient import SoftwareCenterAgentAPI
# from softwarecenter.backend.piston.sreclient_pristine import (
#     SoftwareCenterRecommenderAPI)


# from models.enums import RECOMMENDER_HOST
# SoftwareCenterRecommenderAPI.default_service_root =  \
#     RECOMMENDER_HOST + "/api/1.0"


# patch default_service_root to the one we use
from models.enums import UBUNTU_SSO_SERVICE
# *Don't* append /api/1.0, as it's already included in UBUNTU_SSO_SERVICE
UbuntuSsoAPI.default_service_root = UBUNTU_SSO_SERVICE


# RatingsAndReviewsAPI # pyflakes
UbuntuSsoAPI # pyflakes
# SoftwareCenterAgentAPI # pyflakes
# SoftwareCenterRecommenderAPI # pyflakes


LOG = logging.getLogger(__name__)

if __name__ == "__main__":
    logging.basicConfig()

    # command line parser
    parser = argparse.ArgumentParser(
        description="Backend helper for piston-mini-client based APIs")
    parser.add_argument("--debug", action="store_true", default=False,
                        help="enable debug output")
    parser.add_argument("--datadir", default="/usr/share/software-center",
                        help="setup alternative datadir")
    parser.add_argument("--ignore-cache", action="store_true", default=False,
                        help="force ignore cache")
    parser.add_argument("--disable-offline-mode", action="store_true", 
                        default=False,
                        help="force disable offline mode")
    parser.add_argument("--needs-auth", default=False, action="store_true",
                        help="need oauth credentials")
    parser.add_argument("--no-relogin", default=False, action="store_true",
                        help="do not attempt relogin if token is invalid")
    parser.add_argument("--output", default="pickle",
                        help="output result as [pickle|json|text]")
    parser.add_argument("--parent-xid", default=0,
                        help="xid of the parent window")
    parser.add_argument('klass', help='class to use')
    parser.add_argument('function', help='function to call')
    parser.add_argument('kwargs', nargs="?",
                        help='kwargs for the function call as json')
    args = parser.parse_args()

    if args.debug:
        logging.basicConfig(level=logging.DEBUG)
        LOG.setLevel(logging.DEBUG)

    if args.ignore_cache:
        cachedir = None
    else:
        cachedir = os.path.join(UKSC_CACHE_DIR, "piston-helper")
        
    # check what we need to call
    klass = globals()[args.klass]
    func = args.function
    kwargs = json.loads(args.kwargs or '{}')

    models.enums.datadir = args.datadir

    if args.needs_auth:
        helper = UbuntuSSO(args.parent_xid)
        token = helper.get_oauth_token_and_verify_sync(
            no_relogin=args.no_relogin)
        # if we don't have a token, error here
        if not token:
            # it may happen that the parent is closed already so the pipe
            # is gone, that is ok as we exit anyway
            try:
                sys.stderr.write("ERROR: can not obtain a oauth token\n")
            except IOError:
                pass
            sys.exit(1)

        auth = piston_mini_client.auth.OAuthAuthorizer(
            token["token"], token["token_secret"],
            token["consumer_key"], token["consumer_secret"])
        api = klass(cachedir=cachedir, auth=auth)
    else:
        api = klass(cachedir=cachedir)
        
    piston_reply = None
    # handle the args
    f = getattr(api, func)
    try:
        piston_reply = f(**kwargs)
    except httplib2.ServerNotFoundError as e:
        if not args.disable_offline_mode:
            # switch to offline mode and try again from the cache
            try:
                api._offline_mode = True
                piston_reply = f(**kwargs)
            except Exception as e:
                LOG.warn(e)
                sys.exit(1)
    except APIError as e:
        LOG.warn(e)
        sys.exit(1)
    except:
        LOG.exception("urclient_apps")
        sys.exit(1)

    # no data is a error, the server does always return something,
    # this can happen if e.g. we try cached data but have nothing
    # in the cache
    if piston_reply is None:
        LOG.warn("no data")
        sys.exit(1)

    if args.debug:
        for itm in piston_reply:
            s = "** itm: %s\n" % itm
            for var in vars(itm):
                s += "%s: '%s'\n" % (var, getattr(itm, var))
            LOG.debug(s)

    # print to stdout where its consumed by the parent

    # check what format to use
    if args.output == "pickle":
        res = pickle.dumps(piston_reply)
    elif args.output == "json":
        res = json.dumps(piston_reply)
    elif args.output == "text":
        res = piston_reply

    # and output it
    try:
        print res
    except IOError:
        # this can happen if the parent gets killed, no need to trigger
        # apport for this
        pass
