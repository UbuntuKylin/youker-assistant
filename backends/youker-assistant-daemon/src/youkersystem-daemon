#!/usr/bin/python

import logging
import optparse

import dbus
import dbus.mainloop.glib

from gi.repository import GObject
from common.base import VERSION

if __name__ == '__main__':
    parser = optparse.OptionParser(prog="youkersystem-daemon",
                                   version="%%prog %s" % VERSION,
                                   description="Youker Assistant is a tool for Ubuntu that makes it easy to configure your system and desktop settings.")

    parser.add_option("-d", "--debug", action="store_true", default=False,
                      help="Generate more debugging information.  [default: %default]")
    options, args = parser.parse_args()

    if options.debug:
        logging.basicConfig(level=logging.DEBUG)

    #TODO make it exist when timeout
    from systemdbus.daemon import Daemon
    dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
    mainloop = GObject.MainLoop()
    Daemon(dbus.SystemBus(), mainloop)
    mainloop.run()
