#!/usr/bin/python
# -*- coding: utf-8 -*-
### BEGIN LICENSE
# Copyright (C) 2007-2011 Tualatrix Chou <tualatrix@gmail.com>
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

import thread
import logging

from gi.repository import GObject, Gtk, Gdk, Pango
from policykit.dbusproxy import proxy

log = logging.getLogger('app')

class StartDaemon():
    def __init__(self):
        proxy.get_system_daemon()
        #self.preload_proxy_cache()

    #def preload_proxy_cache(self):
    #    proxy.get_user_cache()

if __name__ == '__main__':
    StartDaemon()
