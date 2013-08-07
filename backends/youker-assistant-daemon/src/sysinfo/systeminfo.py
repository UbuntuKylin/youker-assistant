#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2010 TualatriX <tualatrix@gmail.com>
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
from gi.repository import Gtk
import platform
import gettext
from gettext import gettext as _
from gettext import ngettext as __

def get_distro():
    '''It should be "Ubuntu 10.10 maverick"'''
    return ' '.join(platform.dist())

def get_desktop():
    '''
    ubuntu
    ubuntu-2d
    gnome-classic
    gnome-shell
    '''
    return os.getenv('DESKTOP_SESSION')
def get_desktop_fullname():
    desktop_dict = {'ubuntu': 'Unity',
                    'ubuntu-2d': 'Unity 2D',
                    'gnome': 'GNOME Shell',
                    'gnome-classic': _('GNOME Classic'),
                    'gnome-shell': 'GNOME Shell',
                    'gnome-fallback': _('GNOME Fallback'),
                    'pantheon': 'elementary OS (Luna)',
                    'Lubutu': 'LXDE',
    }
    desktop = get_desktop()
    if desktop in desktop_dict:
        return desktop_dict[desktop]
    else:
        if desktop:
            return _('Unknown (%s)') % desktop
        else:
            return _('Unknown')

DISTRO = get_distro()
SKTOP = get_desktop()
DESKTOP_FULLNAME = get_desktop_fullname()

def get_systeminfo():
    __icon__ = 'distributor-logo'
    __title__ = 'UbuntuKylin Desktop Information'
    return os.uname()[1], os.uname()[-1]

HOSTNAME, PLATFORM = get_systeminfo()

if __name__ == '__main__':
    print(get_systeminfo())
