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

import logging
import optparse

import dbus
import dbus.mainloop.glib

from gi.repository import GObject

VERSION = "0.1.1"

if __name__ == '__main__':
    parser = optparse.OptionParser(prog="youker-assistant-session-daemon",
                                   version="%%prog %s" % VERSION,
                                   description="Youker Assistant is a tool for Ubuntu that makes it easy to configure your system and desktop settings.")

    parser.add_option("-d", "--debug", action="store_true", default=False,
                      help="Generate more debugging information.  [default: %default]")
    options, args = parser.parse_args()

    if options.debug:
        logging.basicConfig(level=logging.DEBUG)

    #TODO make it exist when timeout
    from session_daemon import SessionDaemon
    print("The sessiondbus server is running..........")
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    mainloop = GObject.MainLoop()
    b = SessionDaemon(dbus.SessionBus(), mainloop)
    #GObject.timeout_add(9000, a.construct_msg)
    mainloop.run()
