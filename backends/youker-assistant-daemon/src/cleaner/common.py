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
import ConfigParser
import apt
import apt_pkg


def get_dir_size(path):
    size = 0L
    for root, dirs, files in os.walk(path):
        size += sum([os.path.getsize(os.path.join(root, name)) for name in files])
    return size

def get_cache_list():
    cache = None
    apt_pkg.InitConfig()
    apt_pkg.InitSystem()
    cache = apt.Cache()
    return cache

def get_mozilla_path(homedir):
    count = 0
    tmp_pro_section = []
    print 'ccccccccccccccc'
    print homedir
    if homedir:
        app_path = '%s/.mozilla/firefox' % homedir
    else:
        app_path = os.path.expanduser('~/.mozilla/firefox')
    flag_pro_section = ''
    final_path = ''

    profiles_path = '%s/profiles.ini' % app_path
    if os.path.exists(profiles_path):
        cfg = ConfigParser.ConfigParser()
        cfg.read(profiles_path)
        complete_section = cfg.sections()
        for section in complete_section:
            if section.startswith('Profile'):
                tmp_pro_section.append(section)
                complete_option = cfg.options(section)
                try:
                    cfg.getint(section, 'Default') == 1
                except Exception, e:
                    pass
                else:
                    flag_pro_section = section
                count += 1
        if cfg.getint('General', 'StartWithLastProfile'):
            if count == 1:
                if cfg.getint(tmp_pro_section[0], 'IsRelative') == 0:
                    final_path = cfg.get(tmp_pro_section[0], 'Path')
                else:
                    final_path = os.path.expanduser('%s/%s/' % (app_path, cfg.get(tmp_pro_section[0], 'Path')))
            elif count > 1 :
                if cfg.getint(flag_pro_section, 'IsRelative') == 0:
                    final_path = cfg.get(flag_pro_section, 'Path')
                else:
                    final_path = os.path.expanduser('%s/%s/' % (app_path, cfg.get(flag_pro_section, 'Path')))
            else:
                print 'profile.ini has error!'
        else:
            pass
    else:
        final_path = 'Can not find the file!'
    return final_path

