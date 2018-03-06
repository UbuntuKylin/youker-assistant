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
import fnmatch
import filecmp
import hashlib

class SearchSame():
    def __init__(self):
        self.style = ['.gz', '.bz2']
        self.style_dic = {}
        self.tmp_style_dic = {}

    def search_by_style(self, spath):
        if not os.path.exists(spath):
            raise Exception('no such path!')
        else:
            if not spath.endswith('/'):
                spath += '/'
        for name in os.listdir(spath):
            tmp = spath + name
            if os.path.islink(tmp):
                continue
            elif os.path.isdir(tmp):
                self.search_by_style(tmp)
            else:
                front, behind = os.path.splitext(tmp)
                if behind in self.style:
                    addf, addb = os.path.splitext(front)
                    if addb == '.tar':
                        behind = addb + behind
                self.tmp_style_dic.setdefault(behind, []).append(tmp)

    def search_by_size(self):
        self.style_dic = self.reduce_the_dic(self.tmp_style_dic)
        size_dic = {}
        for k in list(self.style_dic.keys()):
            for abc in self.style_dic[k]:
                filesize = os.path.getsize(abc)
                size_dic.setdefault(filesize, []).append(abc)
        return self.reduce_the_dic(size_dic)

    def search_by_cmp(self):
        final_dic = {}
        size_dic = self.search_by_size()
        for k in list(size_dic.keys()):
            for content in size_dic[k]:
                sha1sumva = self.get_file_hash(content)
                final_dic.setdefault(sha1sumva, []).append(content)
        return self.reduce_the_dic(final_dic)


    def get_file_hash(self, filepath):
        with open(filepath, 'rb') as f:
            sha1obj = hashlib.sha1()
            sha1obj.update(f.read())
            hashvalue = sha1obj.hexdigest()
            return  hashvalue

    def adjust_the_dic(self):
        final_list = []
        final_dic = self.search_by_cmp()
        for key in list(final_dic.keys()):
            tmp_str = "<2_2>".join(final_dic[key])
            final_list.append(tmp_str)
        # init 
        self.style_dic = {}
        self.tmp_style_dic = {}
        return final_list
        
    def reduce_the_dic(self, tmp_dic):
        for key in list(tmp_dic.keys()):
            if len(tmp_dic[key]) < 2:
                del tmp_dic[key]
        return tmp_dic

if __name__ == '__main__':
    path = '/home/kylin/ubuntu-tweak'
    obj = SearchSame()
    obj.search_by_style(path)
    #obj.search_by_size()
    #obj.search_by_cmp()
    obj.adjust_the_dic()
    #obj.get_file_hash('/home/aya/test.py')
