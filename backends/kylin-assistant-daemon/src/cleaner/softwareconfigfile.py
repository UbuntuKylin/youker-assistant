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

import subprocess

from . import common

class SoftwareConfigfile():
    def __init__(self):
        pass

    def scan_configfile_packages(self):
        cache = common.get_cache_list()
        final_softwareconfigfile_list = []

        status, output = subprocess.getstatusoutput('dpkg -l')
        result = [(line.split()[1]).split(':')[0] for line in output.split('\n') if line.startswith('rc')]
        for one in result:
            final_softwareconfigfile_list.append(cache[one])
        return final_softwareconfigfile_list
    def get_configfile_packages(self):
        cache = common.get_cache_list()
        softwareconfigfile_list = []

        status, output = subprocess.getstatusoutput('dpkg -l')
        result = [(line.split()[1]).split(':')[0] for line in output.split('\n') if line.startswith('rc')]
        for one in result:
            pkg = cache[one]
            softwareconfigfile_list.append('Name:' + pkg.name + ';' + 'Summary:' + ';' + 'Size:')
        return softwareconfigfile_list


if __name__ == '__main__':
    obj = SoftwareConfigfile()
    a = obj.scan_configfile_packages()
    print(a)
