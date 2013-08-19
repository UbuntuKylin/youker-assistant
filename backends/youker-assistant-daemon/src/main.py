# Ubuntu Tweak - Ubuntu Configuration Tool
#
# Copyright (C) 2007-2011 Tualatrix Chou <tualatrix@gmail.com>
#
# Ubuntu Tweak is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# Ubuntu Tweak is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Ubuntu Tweak; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA

import thread
import logging

from gi.repository import GObject, Gtk, Gdk, Pango
from policykit.dbusproxy import proxy

log = logging.getLogger('app')

class SystemDbusDaemon():
    def __init__(self, feature='', module='', splash_window=None):
        self.get_system_daemon_main()

    def get_system_daemon_main(self):
        return proxy.get_system_daemon()

if __name__ == '__main__':
    SystemDbusDaemon()
