#!/usr/bin/python
# -*- coding: utf-8 -*-

### BEGIN LICENSE

# Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd

# Author:
#     maclin <majun@ubuntukylin.com>
# Maintainer:
#     maclin <majun@ubuntukylin.com>

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
from xdg import BaseDirectory as xdg

# ported from ubuntu-software-center to support Ubuntu-kylin-SSO
UBUNTU_SSO_SERVICE = 'http://login.ubuntukylin.com:8001/api/1.0'#'http://0.0.0.0:8000/api/1.0'
SOFTWARE_CENTER_NAME_KEYRING = "Ubuntu Kylin ID"
SOFTWARE_CENTER_SSO_DESCRIPTION = '注册或登录 Ubuntu Kylin 软件中心。'
datadir = "./utils/"
PISTON_GENERIC_HELPER = "piston_generic_helper.py"
