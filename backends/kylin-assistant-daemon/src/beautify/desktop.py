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

import os
from . import gsettings

class Desktop:
    desktop = None

    def __init__(self):
        self.desktop = os.getenv('XDG_CURRENT_DESKTOP')
        if self.desktop is None:
             self.desktop = os.getenv('XDG_SESSION_DESKTOP')

    # ---------------desktopicon---------------
    # -----------------默认值-----------------
    # Get Default Value
    def get_default_schema_value(self, schema, key):
        return gsettings.get_schema_value(schema, key)

    # Set Default Value
    def set_default_schema_value(self, schema, key, type):
        default_value = self.get_default_schema_value(schema, key)
        if default_value is not None:
            return gsettings.set(schema, None, key, type, default_value)
        else:
            raise NotImplemented
    # ----------------------------------


    # show desktop icons, True/False
    def set_show_desktop_icons(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.background',
                None,
                'show-desktop-icons',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.desktop.background',
                None,
                'show-desktop-icons',
                'boolean', flag)

    # get is show desktop icons
    def get_show_desktop_icons(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.background',
                None, 'show-desktop-icons', 'boolean')
        else:
            return gsettings.get('org.gnome.desktop.background',
                None, 'show-desktop-icons', 'boolean')

    def set_show_computer(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.caja.desktop',
                None,
                'computer-icon-visible',
                'boolean', flag)

    def get_show_computer(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.caja.desktop',
                None, 'computer-icon-visible', 'boolean')

    # show home folder
    def set_show_homefolder(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.caja.desktop',
                None,
                'home-icon-visible',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.nautilus.desktop',
                None,
                'home-icon-visible',
                'boolean', flag)

    # get show homefolder
    def get_show_homefolder(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.caja.desktop',
                None, 'home-icon-visible', 'boolean')
        else:
            return gsettings.get('org.gnome.nautilus.desktop',
                None, 'home-icon-visible', 'boolean')

    # show network
    def set_show_network(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.caja.desktop',
                None,
                'network-icon-visible',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.nautilus.desktop',
                None,
                'network-icon-visible',
                'boolean', flag)

    # get show network
    def get_show_network(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.caja.desktop',
                None, 'network-icon-visible', 'boolean')
        else:
            return gsettings.get('org.gnome.nautilus.desktop',
                None, 'network-icon-visible', 'boolean')

    # show trash
    def set_show_trash(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.caja.desktop',
                None,
                'trash-icon-visible',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.nautilus.desktop',
                None,
                'trash-icon-visible',
                'boolean', flag)

    # get show trash
    def get_show_trash(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.caja.desktop',
                None, 'trash-icon-visible', 'boolean')
        else:
            return gsettings.get('org.gnome.nautilus.desktop',
                None, 'trash-icon-visible', 'boolean')

    # show devices
    def set_show_devices(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.caja.desktop',
                None,
                'volumes-visible',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.nautilus.desktop',
                None,
                'volumes-visible',
                'boolean', flag)

    # get show devices
    def get_show_devices(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.caja.desktop',
                None, 'volumes-visible', 'boolean')
        else:
            return gsettings.get('org.gnome.nautilus.desktop',
                None, 'volumes-visible', 'boolean')


    #-------------------------cinnamon--------------------------------
    # show desktop icons, True/False
    def set_show_cinnamon_desktop_icons(self, flag):
        return gsettings.set('org.nemo.desktop',
            None,
            'show-desktop-icons',
            'boolean', flag)

    # get is show desktop icons
    def get_show_cinnamon_desktop_icons(self):
        return gsettings.get('org.nemo.desktop',
            None, 'show-desktop-icons', 'boolean')

    def set_show_cinnamon_computer(self, flag):
        return gsettings.set('org.nemo.desktop',
            None,
            'computer-icon-visible',
            'boolean', flag)

    def get_show_cinnamon_computer(self):
        return gsettings.get('org.nemo.desktop',
            None, 'computer-icon-visible', 'boolean')

    # show home folder
    def set_show_cinnamon_homefolder(self, flag):
        return gsettings.set('org.nemo.desktop',
            None,
            'home-icon-visible',
            'boolean', flag)

    # get show homefolder
    def get_show_cinnamon_homefolder(self):
        return gsettings.get('org.nemo.desktop',
            None, 'home-icon-visible', 'boolean')

    # show network
    def set_show_cinnamon_network(self, flag):
        return gsettings.set('org.nemo.desktop',
            None,
            'network-icon-visible',
            'boolean', flag)

    # get show network
    def get_show_cinnamon_network(self):
        return gsettings.get('org.nemo.desktop',
            None, 'network-icon-visible', 'boolean')

    # show trash
    def set_show_cinnamon_trash(self, flag):
        return gsettings.set('org.nemo.desktop',
            None,
            'trash-icon-visible',
            'boolean', flag)

    # get show trash
    def get_show_cinnamon_trash(self):
        return gsettings.get('org.nemo.desktop',
            None, 'trash-icon-visible', 'boolean')

    # show devices
    def set_show_cinnamon_devices(self, flag):
        return gsettings.set('org.nemo.desktop',
            None,
            'volumes-visible',
            'boolean', flag)

    # get show devices
    def get_show_cinnamon_devices(self):
        return gsettings.get('org.nemo.desktop',
            None, 'volumes-visible', 'boolean')

# if __name__ == '__main__':
# 	ddd = Desktop()
	# print ddd.get_show_desktop_icons()
	# print ddd.get_show_homefolder()
	# print ddd.get_show_network()
	# print ddd.get_show_trash()
	# print ddd.get_show_devices()
	# ddd.set_show_desktop_icons(True)
	# ddd.set_show_homefolder(True)
	# ddd.set_show_network(True)
	# ddd.set_show_trash(True)
	# ddd.set_show_devices(True)
