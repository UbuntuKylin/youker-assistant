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
#import apt
import apt_pkg
import re

from . import common

class OldKernel():
    def __init__(self):
        #cache = None
        self.flag = '(\w+-)*[.\d]+-\d+[\D]*'

    def scan_oldkernel_packages(self):
        #pkgs = self.cache.packages
        cache = common.get_cache_list()
        final_oldkernel_list = []
        current_version = '-'.join(os.uname()[2].split('-')[:2])
        if cache:
            for pkg in cache:
                if pkg.is_installed and pkg.name.startswith('linux'):
                    if re.match(self.flag, pkg.name):
                        #version = pkg.installedVersion[:-3]
                        version = pkg.installed.version
                        if apt_pkg.version_compare(version, current_version) < 0:
                            #tmp_oldkernel_list = [pkg.name, common.confirm_filesize_unit(pkg.installedSize)]
                            #final_oldkernel_list.append('<2_2>'.join(tmp_oldkernel_list))
                            final_oldkernel_list.append(pkg)
        return final_oldkernel_list

    def get_oldkernel_packages(self):
        #pkgs = self.cache.packages
        cache = common.get_cache_list()
        oldkernel_list = []
        current_version = '-'.join(os.uname()[2].split('-')[:2])
        if cache:
            for pkg in cache:
                if pkg.is_installed and pkg.name.startswith('linux'):
                    if re.match(self.flag, pkg.name):
                        #version = pkg.installedVersion[:-3]
                        version = pkg.installed.version
                        if apt_pkg.version_compare(version, current_version) < 0:
                            #tmp_oldkernel_list = [pkg.name, common.confirm_filesize_unit(pkg.installedSize)]
                            #final_oldkernel_list.append('<2_2>'.join(tmp_oldkernel_list))
                            oldkernel_list.append('Name:' + pkg.name + ';' + 'Summary:' + pkg.installed.summary + ';' + 'Size:' + common.confirm_filesize_unit(pkg.installed.installed_size))

        return oldkernel_list
if __name__ == "__main__":
    objo = OldKernel()
    #objo.get_the_kernel()
    aaa = objo.get_old_kernel()
    print(aaa)
    
