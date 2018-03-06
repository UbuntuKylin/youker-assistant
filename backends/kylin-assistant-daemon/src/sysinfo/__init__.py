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

import sys
import os
from gi.repository import GLib
import platform
import math
import apt

NO_UPDATE_WARNING_DAYS = 7
FILEPATH = "/etc/lsb-release"
RELEASEPATH = "/etc/ubuntukylin-release"

KILOBYTE_FACTOR = 1000.0
MEGABYTE_FACTOR = (1000.0 * 1000.0)
GIGABYTE_FACTOR = (1000.0 * 1000.0 * 1000.0)
TERABYTE_FACTOR = (1000.0 * 1000.0 * 1000.0 * 1000.0)

def get_human_read_capacity_size(size):
    size_str = ""
    displayed_size = 0.0
    unit = "KB"

    if size < MEGABYTE_FACTOR:
        displayed_size = float(size/KILOBYTE_FACTOR)
        unit = "KB"
    elif size < GIGABYTE_FACTOR:
        displayed_size = float(size/MEGABYTE_FACTOR)
        unit = "MB"
    elif size < TERABYTE_FACTOR:
        displayed_size = float(size/GIGABYTE_FACTOR)
        unit = "GB"
    else:
        displayed_size = float(size/TERABYTE_FACTOR)
        unit = "TB"
    #print "displayed_size=", round(displayed_size)
    #round 不是简单的四舍五入，而是ROUND_HALF_EVEN的策略
    #ceil 取大于或者等于x的最小整数
    #floor 取小于或者等于x的最大整数
    #print round(2.5)#3.0
    #print math.ceil(2.5)#3.0
    #print math.floor(2.5)#2.0
    #print round(2.3)#2.0
    #print math.ceil(2.3)#3.0
    #print math.floor(2.3)#2.0
    str_list = [str(int(round(displayed_size))), unit]
    size_str = " ".join(str_list)
    return size_str


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
        CLIPS_DICT['currrent_user'], CLIPS_DICT['home_path'], CLIPS_DICT['terminal'], CLIPS_DICT['language'] = self.get_userinfo()
        CLIPS_DICT['distribution'] = self.get_distro()
        CLIPS_DICT['desktopenvironment'] = self.get_desktop()
        CLIPS_DICT['hostname'], CLIPS_DICT['machine'] = self.get_systeminfo()
        CLIPS_DICT['cpu'], CLIPS_DICT['ram'] = self.get_hardwareinfo()
        return CLIPS_DICT

    def get_userinfo(self):
        dict = {}
        dict['username'] = GLib.get_user_name()
        dict['homedir'] = GLib.get_home_dir()
        dict['terminal'] = GLib.getenv('SHELL')
        dict['lang'] =  GLib.getenv('LANG')
        return dict['username'], dict['homedir'],dict['terminal'],dict['lang']

    def get_distro(self):
        '''It should be: DISTRIB_DESCRIPTION="UbuntuKylin 13.10'''
        #FILEPATH  RELEASEPATH
        distro = ""
        if os.path.exists(RELEASEPATH):
            with open(RELEASEPATH, "r") as fsys:
                for line in fsys:
                    if line.startswith("DISTRIB_DESCRIPTION"):
                        tmp = line
                        break
            # kobe: remove '"' and '\n'
            front = tmp.split('=')[1].replace('"', '').replace('\n', '') #(LP: #1240862)
            distro = front + '-' + platform.dist()[2]
        elif os.path.exists("/etc/os-release"):
            with open("/etc/os-release", "r") as fsys:
                for line in fsys:
                    if line.startswith("PRETTY_NAME"):
                        tmp = line
                        break
            distro = tmp.split('=')[1].replace('"', '').replace('\n', '')
        else:
            a = platform.dist()[0]
            b = platform.dist()[1]
            c = platform.dist()[2]
            distro = '-'.join((a,b,c))
#        if not os.path.exists(RELEASEPATH):
#            with open(FILEPATH, "r") as fsys:
#                for line in fsys:
#                    if line.startswith("DISTRIB_DESCRIPTION"):
#                        tmp = line
#                        break
#            # kobe: remove '"' and '\n'
#            front = tmp.split('=')[1].replace('"', '').replace('\n', '') #(LP: #1240862)
#            if front.startswith("UbuntuKylin") or front.startswith("Ubuntu Kylin"):
#                distro = front + '-' + platform.dist()[2]
#            else:
#                a = platform.dist()[0]
#                b = platform.dist()[1]
#                c = platform.dist()[2]
#                distro = '-'.join((a,b,c))
#        else:
#            with open(RELEASEPATH, "r") as fp:
#                for line in fp:
#                    if line.startswith("DISTRIB_ID"):
#                        tmp1 = line
#                    elif line.startswith("DISTRIB_RELEASE"):
#                        tmp2 = line
#                    elif line.startswith("DISTRIB_CODENAME"):
#                        tmp3 = line
#            # kobe: remove '"' and '\n'
#            id = tmp1.split('=')[1].replace('"', '').replace('\n', '')
#            release = tmp2.split('=')[1].replace('"', '').replace('\n', '')
#            codename = tmp3.split('=')[1].replace('"', '').replace('\n', '')
#            distro = '-'.join((id, release, codename))
        return distro

    def get_desktop(self):
        apt_cache = apt.Cache()
        try:
            package = apt_cache["kylin-menu"]
        except:
            package = None
        if package is not None and package.is_installed:
            return "UKUI"
        desktop_dict = {'ubuntu': 'Unity',
                        'ubuntu-2d': 'Unity 2D',
                        'gnome': 'GNOME Shell',
                        'gnome-classic': 'GNOME Classic',
                        'gnome-shell': 'GNOME Shell',
                        'gnome-fallback': 'GNOME Fallback',
                        'pantheon': 'elementary OS (Luna)',
                        'Lubutu': 'LXDE',
        }
        try:
            desktop_name = os.getenv('XDG_CURRENT_DESKTOP')
            if desktop_name is None:
                 desktop_name = os.getenv('XDG_SESSION_DESKTOP')
            if desktop_name is None:
                desktop_name = "N/A"
            return desktop_name
        except Exception as e:
            print(e)
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
        model_name = 'N/A'
#        MemTotal2 = ''
        MemSize = None
        # CPU
        with open('/proc/cpuinfo') as f:
            for line in f:
                if line.strip():
                    if line.rstrip('\n').startswith('model name'):
                        model_name = line.rstrip('\n').split(':')[1]
                        break
                    elif line.rstrip('\n').startswith('Hardware'):
                        model_name = line.rstrip('\n').split(':')[1].strip()
                        break
        # Memory
#        with open('/proc/meminfo') as f:
#            for line in f:
#                if line.strip():
#                    if line.rstrip('\n').startswith('MemTotal'):
#                        MemTotal = line.rstrip('\n').split(':')[1].strip()
#                        MemTotal1 = MemTotal.split(' ')[0]
#                        #MemTotal2 = GLib.format_size_for_display(int(MemTotal1) * 1024)
#                        MemTotal2 = str(round(float(MemTotal1) / (1000 ** 2), 1)) + "G"
#                        break

        with open('/proc/meminfo') as f:
            for line in f:
                if line.strip():
                    if line.rstrip('\n').startswith('MemTotal'):
                        MemTotal = line.rstrip('\n').split(':')[1].strip()
                        MemTmp = MemTotal.split(' ')[0]
                        #print "MemTmp=",MemTmp
                        #MemTmp = 1000204886#8156252#7889972
                        MemSize = get_human_read_capacity_size(int(MemTmp)*1000)
                        break
        if MemSize is None:
            MemSize = "N/A"
        return model_name,str(MemSize)
#        return model_name,MemTotal2

    def get_codename(self):
        codename = platform.dist()[2]
        return codename

if __name__ == '__main__':
    c = Sysinfo()
    print((c.get_sys_msg()))
    import getpass
    print((getpass.getuser()))
