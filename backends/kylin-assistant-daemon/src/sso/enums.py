#!/usr/bin/python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE

# Copyright (C) 2014 National University of Defense Technology(NUDT) & Kylin Ltd

# Author:
#     Robert <luolei@ubuntukylin.com>

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

import os
import errno
from xdg import BaseDirectory as xdg

def safe_makedirs(dir_path):
    """ This function can be used in place of a straight os.makedirs to
        handle the possibility of a race condition when more than one
        process may potentially be creating the same directory, it will
        not fail if two processes try to create the same dir at the same
        time
    """
    # avoid throwing an OSError, see for example LP: #743003
    if not os.path.exists(dir_path):
        try:
            os.makedirs(dir_path)
        except OSError as e:
            if e.errno == errno.EEXIST:
                # it seems that another process has already created this
                # directory in the meantime, that's ok
                pass
            else:
                # the error is due to something else, so we want to raise it
                raise

# ported from ubuntu-software-center to support Ubuntu-kylin-SSO
UBUNTU_KYLIN_SSO_SERVICE = 'https://login.ubuntukylin.com/api/1.0'
SOFTWARE_CENTER_NAME_KEYRING = "Youker ID"
SOFTWARE_CENTER_SSO_DESCRIPTION = '注册或登录优客账号。'
datadir = './sso/utils/'
PISTON_GENERIC_HELPER = "piston_generic_helper.py"
YOUKER_ASSISTANT_CACHE_DIR = os.path.join(xdg.xdg_cache_home, "kylin-assistant")
safe_makedirs(YOUKER_ASSISTANT_CACHE_DIR)
