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
from gi.repository import Gtk, GLib
import gettext
from gettext import gettext as _
from gettext import ngettext as __

def get_userinfo():
    __icon__  = 'config-users'
    __title__ = _('User Information')
    return GLib.get_user_name(), GLib.get_home_dir(), GLib.getenv('SHELL'), GLib.getenv('LANG')

CURRENT_USER, HOME_DIRECTORY, SHELL, LANGUAGE = get_userinfo()

if __name__ == '__main__':
    print(get_userinfo())
