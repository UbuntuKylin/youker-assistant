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

import os, sys
import glob
from gi.repository import Gtk, GLib
import gettext
from gettext import gettext as _
from gettext import ngettext as __

def get_codename():
    try:
        codename = os.popen('lsb_release -cs').read().strip()
        if codename in ['karmic', 'helena', 'Helena']:
            return 'karmic'
        elif codename in ['lucid', 'isadora', 'Isadora']:
            return 'lucid'
        elif codename in ['maverick', 'julia']:
            return 'maverick'
        elif codename in ['natty', 'katya']:
            return 'natty'
        elif codename in ['oneiric', 'lisa']:
            return 'oneiric'
        elif codename in ['precise', 'maya', 'Maya']:
            return 'precise'
        elif codename in ['raring']:
            return 'raring'
        return codename
    except:
        pass
    return ''

CODENAME = get_codename()

def get_cleanerinfo():
    __icon__  = 'computerjanitor'
    __title__ = _('Your system is clean')

    cache_number = len(glob.glob('/var/cache/apt/archives/*.deb'))

    cache_flag = False
    cache_size = ''
    if cache_number:
        cache_flag = True

    cache_packages = ('%s cache packages can be cleaned.') % cache_number
    try:
        if CODENAME in ['oneiric', 'precise']:
            root_path = '~/.thumbnails'
        else:
            root_path = '~/.cache/thumbnails'
        size = int(os.popen('du -bs %s' % root_path).read().split()[0])
    except:
        size = 0

    if size:
        cache_size = ('%s thumbnails cache can be cleaned.') % \
             GLib.format_size_for_display(size)
    return cache_flag, cache_packages, cache_size

CACHE_FLAG, CACHE_PACKAGES, CACHE_SIZE = get_cleanerinfo()

if __name__ == '__main__':
    print(get_cleanerinfo())
