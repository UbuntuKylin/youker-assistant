#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
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

import sys
import os
from cleanerinfo import CACHE_FLAG, CACHE_PACKAGES, CACHE_SIZE
from hardwareinfo import CPU, RAM
from systeminfo import HOSTNAME, PLATFORM, DISTRO, DESKTOP_FULLNAME
from updateinfo import UPDATE_TIME
from userinfo import CURRENT_USER, HOME_DIRECTORY, SHELL, LANGUAGE

class Sysinfo:
    def get_sys_msg(self):
        CLIPS_DICT = {}
        CLIPS_DICT['cache_flag'] = CACHE_FLAG
        CLIPS_DICT['cache_packages'] = CACHE_PACKAGES
        CLIPS_DICT['cache_size'] = CACHE_SIZE
        CLIPS_DICT['cpu'] = CPU
        CLIPS_DICT['ram'] = RAM
        CLIPS_DICT['hostname'] = HOSTNAME
        CLIPS_DICT['platform'] = PLATFORM
        CLIPS_DICT['distribution'] = DISTRO
        CLIPS_DICT['desktopenvironment'] = DESKTOP_FULLNAME
        CLIPS_DICT['update_time'] = UPDATE_TIME
        CLIPS_DICT['currrent_user'] = CURRENT_USER
        CLIPS_DICT['home_path'] = HOME_DIRECTORY
        CLIPS_DICT['shell'] = SHELL
        CLIPS_DICT['language'] = LANGUAGE
        return CLIPS_DICT
