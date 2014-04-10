#!/usr/bin/python
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

import sys
import os
from gi.repository import GLib
import platform

NO_UPDATE_WARNING_DAYS = 7
FILEPATH = "/etc/lsb-release"
RELEASEPATH = "/etc/ubuntukylin-release"

class Sysinfo:
    CACHE_FLAG = ''
    CACHE_PACKAGES = ''
    CACHE_SIZE = ''
    CPU = ''
    RAM = ''
    HOSTNAME = ''
    PLATFORM = ''
    DISTRO = ''
    DESKTOP_FULLNAME = ''
    UPDATE_TIME = ''
    CURRENT_USER = ''
    HOME_DIRECTORY = ''
    SHELL = ''
    LANGUAGE = ''

    def __init__(self):
        self.CACHE_FLAG = 'a'
        self.CACHE_PACKAGES = 'b'
        self.CACHE_SIZE = 'c'
        self.CPU = 'd' 
        self.RAM = 'e'
        self.HOSTNAME = 'f'
        self.PLATFORM = 'g'
        self.DISTRO = 'h'
        self.DESKTOP_FULLNAME = 'i'
        self.UPDATE_TIME = 'j'
        self.CURRENT_USER = 'k'
        self.HOME_DIRECTORY = 'l'
        self.SHELL = 'm'
        self.LANGUAGE = 'n'     

    def get_sys_msg(self):
        CLIPS_DICT = {}
        CLIPS_DICT['currrent_user'], CLIPS_DICT['home_path'], CLIPS_DICT['shell'], CLIPS_DICT['language'] = self.get_userinfo()
        CLIPS_DICT['distribution'] = self.get_distro()
        CLIPS_DICT['desktopenvironment'] = self.get_desktop()
        CLIPS_DICT['hostname'], CLIPS_DICT['platform'] = self.get_systeminfo()
        CLIPS_DICT['cpu'], CLIPS_DICT['ram'] = self.get_hardwareinfo()
        CLIPS_DICT['currrent_user']
        return CLIPS_DICT

    def get_userinfo(self):
        dict = {}
        dict['username'] = GLib.get_user_name()
        dict['homedir'] = GLib.get_home_dir()
        dict['shell'] = GLib.getenv('SHELL')
        dict['lang'] =  GLib.getenv('LANG')
        return dict['username'], dict['homedir'],dict['shell'],dict['lang']

    def get_distro(self):
        '''It should be: DISTRIB_DESCRIPTION="UbuntuKylin 13.10'''
        #FILEPATH  RELEASEPATH
        distro = ""
        if not os.path.exists(RELEASEPATH):
            with open(FILEPATH, "r") as fsys:
                for line in fsys:
                    if line.startswith("DISTRIB_DESCRIPTION"):
                        tmp = line
                        break
            # kobe: remove '"' and '\n'
            front = tmp.split('=')[1].replace('"', '').replace('\n', '') #(LP: #1240862)
            if front.startswith("UbuntuKylin") or front.startswith("Ubuntu Kylin"):
                distro = front + '-' + platform.dist()[2]
            else:
                a = platform.dist()[0]
                b = platform.dist()[1]
                c = platform.dist()[2]
                distro = '-'.join((a,b,c))
        else:
            with open(RELEASEPATH, "r") as fp:
                for line in fp:
                    if line.startswith("DISTRIB_ID"):
                        tmp1 = line
                    elif line.startswith("DISTRIB_RELEASE"):
                        tmp2 = line
                    elif line.startswith("DISTRIB_CODENAME"):
                        tmp3 = line
            # kobe: remove '"' and '\n'
            id = tmp1.split('=')[1].replace('"', '').replace('\n', '')
            release = tmp2.split('=')[1].replace('"', '').replace('\n', '')
            codename = tmp3.split('=')[1].replace('"', '').replace('\n', '')
            distro = '-'.join((id, release, codename))
        return distro

    def get_desktop(self):
        desktop_dict = {'ubuntu': 'Unity',
                        'ubuntu-2d': 'Unity 2D',
                        'gnome': 'GNOME Shell',
                        'gnome-classic': 'GNOME Classic',
                        'gnome-shell': 'GNOME Shell',
                        'gnome-fallback': 'GNOME Fallback',
                        'pantheon': 'elementary OS (Luna)',
                        'Lubutu': 'LXDE',
        }
        desktop = os.getenv('DESKTOP_SESSION')
        if desktop in desktop_dict:
            return desktop_dict[desktop]
        else:
            if desktop:
                return 'Unknown (%s)' % desktop
            else:
                return 'Unknown'


    def get_systeminfo(self):
        return platform.node() , platform.processor()

    def get_hardwareinfo(self):
        # CPU
        with open('/proc/cpuinfo') as f:
            for line in f:
                if line.strip():
                    if line.rstrip('\n').startswith('model name'):
                        model_name = line.rstrip('\n').split(':')[1]

        # Memory
        with open('/proc/meminfo') as f:
            for line in f:
                if line.strip():
                    if line.rstrip('\n').startswith('MemTotal'):
                        MemTotal = line.rstrip('\n').split(':')[1]
                        MemTotal1 = MemTotal.split(' ')[8]
                        MemTotal2 = GLib.format_size_for_display(int(MemTotal1) * 1024)
        return model_name,MemTotal2

    def get_codename(self):
        codename = platform.dist()[2]
        return codename

if __name__ == '__main__':
    c = Sysinfo()
    print(c.get_sys_msg())
    import getpass
    print(getpass.getuser())
