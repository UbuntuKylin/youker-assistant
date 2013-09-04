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

import os
import os.path

class DiskAnalyse():
    def __init__(self):
        self.final_list_str = []
        self.final_list = []

    def hundred_large_files(self, size, path):
        mypath = path
        if not os.path.exists(mypath):
            raise Exception("make a mistake")
        for rootpath, dirnames, filenames in os.walk(mypath):
            for filename in filenames:
                flag = True
                filepath = os.path.join(rootpath, filename)
                if os.path.islink(filepath):
                    continue
                filetuple = (os.path.getsize(filepath), filepath)
                if not self.final_list and filetuple[0] >= size:
                    self.final_list.append(filetuple)
                    flag = False
                else:
                    for index, values in enumerate(self.final_list):
                        if filetuple > values:
                            self.final_list.insert(index, filetuple)
                            flag = False
                            break
                    if flag and filetuple[0] >= size :
                        self.final_list.append(filetuple)

    def type_of_file(self):
        code = ['.py', '.cpp', 'pl', '.cpp', '.c']
        video = ['.avi', '.mpg', '.mp4', '.swf']
        music = ['.mp3', '.wav', '.aif', '.au']
        document = ['.doc', '.txt', '.hlp', '.wps', '.rtf', '.pdf', '.odt']
        compress = ['.rar','.zip','.gz', '.bz2', '.7z', '.jar']
        picture = ['.pic', '.gif', '.jpg', '.bmp', '.png', '.ico']
        for index, content in enumerate(self.final_list):
            front, behind = os.path.splitext(content[1])
            if behind in video:
                self.final_list[index] = content + ('video',)
            elif behind in music:
                self.final_list[index] = content + ('music',)
            elif behind in document:
                self.final_list[index] = content + ('document',)
            elif behind in compress:
                self.final_list[index] = content + ('compress',)
            elif behind in picture:
                self.final_list[index] = content + ('picture',)
            else:
                self.final_list[index] = content + ('others',)

    def adjust_the_list(self):
        final_list_str = []
        for con in self.final_list:
            tmp = list(con)
            tmp[0] = str(tmp[0])
            final_list_str.append('<2_2>'.join(tmp))
        self.final_list = []
        return final_list_str


if __name__ == '__main__':
    obj = DiskAnalyse()
    obj.hundred_large_files()
    obj.type_of_file()
