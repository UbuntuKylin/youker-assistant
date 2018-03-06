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
import configparser
import apt
import apt_pkg
import psutil
import re

HOMEDIR = ''

def confirm_filesize_unit(size):
    unit_list = ['B', 'KB', 'MB', 'GB', 'TB']
    flag = 0
    while True:
        if size > 512:
            size /= 1024.0
            flag += 1
        else:                                                                            break
    tmp = "%.2f" % size
    finalsize = tmp + ' ' + unit_list[flag]
    return finalsize

def get_dir_size(path):
    size = 0
    for root, dirs, files in os.walk(path):
        size += sum([os.path.getsize(os.path.join(root, name)) for name in files])
    return size

def process_pid(pname):
    pid = None
    processinfo = psutil.process_iter()
    for one in processinfo:
        one_str = str(one)
        patt = re.compile(pname, re.I)
        if patt.search(one_str):
            pid = int(one_str.split('pid=')[1].split(',')[0])
    return pid

def get_cache_list():
    cache = None
    #apt_pkg.InitConfig()
    #apt_pkg.InitSystem()
    apt_pkg.init_config()
    apt_pkg.init_system()
    cache = apt.Cache()
    return cache

#def get_homedir_sysdaemon(homedir):
#    global HOMEDIR
#    HOMEDIR = homedir

def return_homedir_sysdaemon():
    global HOMEDIR
    return HOMEDIR

def return_homedir_sesdaemon():
    return os.path.expanduser('~')

def analytical_profiles_file(homedir):
    count = 0
    tmp_pro_section = []
    flag_pro_section = ''
    finalpath = ''

    app_path = '%s/.mozilla/firefox' % homedir
    profiles_path = '%s/profiles.ini' % app_path
    if os.path.exists(profiles_path):
        cfg = configparser.ConfigParser()
        cfg.read(profiles_path)
        complete_section = cfg.sections()
        for section in complete_section:
            if section.startswith('Profile'):
                tmp_pro_section.append(section)
                complete_option = cfg.options(section)
                try:
                    cfg.getint(section, 'Default') == 1
                except Exception as e:
                    pass
                else:
                    flag_pro_section = section
                count += 1
        if cfg.getint('General', 'StartWithLastProfile'):
            if count == 1:
                if cfg.getint(tmp_pro_section[0], 'IsRelative') == 0:
                    finalpath = cfg.get(tmp_pro_section[0], 'Path').split('/')[-1]
                else:
                    finalpath = cfg.get(tmp_pro_section[0], 'Path')
            elif count > 1 :
                if cfg.getint(flag_pro_section, 'IsRelative') == 0:
                    finalpath = cfg.get(flag_pro_section, 'Path').split('/')[-1]
                else:
                    finalpath = cfg.get(flag_pro_section, 'Path')
            else:
                pass
        else:
            pass
    return finalpath

def get_mozilla_path(homedir):
    count = 0
    tmp_pro_section = []
    if homedir:
        app_path = '%s/.mozilla/firefox' % homedir
    else:
        app_path = os.path.expanduser('~/.mozilla/firefox')
    flag_pro_section = ''
    finalpath = ''

    profiles_path = '%s/profiles.ini' % app_path
    if os.path.exists(profiles_path):
        cfg = configparser.ConfigParser()
        cfg.read(profiles_path)
        complete_section = cfg.sections()
        for section in complete_section:
            if section.startswith('Profile'):
                tmp_pro_section.append(section)
                complete_option = cfg.options(section)
                try:
                    cfg.getint(section, 'Default') == 1
                except Exception as e:
                    pass
                else:
                    flag_pro_section = section
                count += 1
        if cfg.getint('General', 'StartWithLastProfile'):
            if count == 1:
                if cfg.getint(tmp_pro_section[0], 'IsRelative') == 0:
                    finalpath = cfg.get(tmp_pro_section[0], 'Path')
                else:
                    finalpath = os.path.expanduser('%s/%s/' % (app_path, cfg.get(tmp_pro_section[0], 'Path')))
            elif count > 1 :
                if cfg.getint(flag_pro_section, 'IsRelative') == 0:
                    finalpath = cfg.get(flag_pro_section, 'Path')
                else:
                    finalpath = os.path.expanduser('%s/%s/' % (app_path, cfg.get(flag_pro_section, 'Path')))
            else:
                raise Exception('profile.ini has error!')
        else:
            pass
    return finalpath

if __name__ == '__main__':
    print(analytical_profiles_file('/home/aya'))
