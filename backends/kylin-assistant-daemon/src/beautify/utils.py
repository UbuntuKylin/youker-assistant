#!/usr/bin/python3
# -*- coding: utf-8 -*-
### BEGIN LICENSE

# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
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

import os

# get ~ dir
def get_home_dir():
    return os.path.expanduser('~')

# check dirs with given filters and filtertype
def check_dirs(dirs, filters, filtertype):
    result = []
    try:
        for onedir in dirs:
            if os.path.isdir(onedir):
                for f in os.listdir(onedir):
                    if use_filters(os.path.join(onedir, f), filters, filtertype):
                        result.append(f)
    except:
        pass
    return result

# check the fpathdir with filters filtertype: True == include, False == exlude
def use_filters(fpath, filters, filtertype):
    # not a directory
    if os.path.isdir(fpath) == False:
        return False

    if filtertype:
        for onefilter in filters:
            if os.path.exists(os.path.join(fpath, onefilter)):
                continue
            else:
                return False
        return True
    else:
        for onefilter in filters:
            if os.path.exists(os.path.join(fpath, onefilter)):
                return False
            else:
                continue
        return True