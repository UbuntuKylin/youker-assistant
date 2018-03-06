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
import os.path

from . import common

class DiskAnalyse():
    def __init__(self):
        pass

    def hundred_large_files(self, size, path):
        mypath = path
        final_list = []
        if os.path.exists(mypath):
            for rootpath, dirnames, filenames in os.walk(mypath):
                for filename in filenames:
                    flag = True
                    filepath = os.path.join(rootpath, filename)
                    if os.path.islink(filepath):
                        continue
                    filelist = [os.path.getsize(filepath), filepath]
                    if not final_list and filelist[0] >= size:
                        final_list.append(filelist)
                        flag = False
                    else:
                        for index, values in enumerate(final_list):
                            if filelist > values:
                                final_list.insert(index, filelist)
                                flag = False
                                break
                        if flag and filelist[0] >= size :
                            final_list.append(filelist)
        else:
            pass
        return final_list

    def adjust_the_list(self, size, path):
        final_str = []
        tmp_list = self.hundred_large_files(size, path)
        if tmp_list:
            for tmp in tmp_list:
                tmp[0] = common.confirm_filesize_unit(tmp[0])
                final_str.append('<2_2>'.join(tmp))
        return final_str


if __name__ == '__main__':
    obj = DiskAnalyse()
    obj.hundred_large_files()
    obj.type_of_file()
