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

import gsettings

class Unity:

	# ---------------launcher---------------

	# launcher auto hide mode, True/False
	def set_launcher_autohide(self, flag):
		return gsettings.set('org.compiz.unityshell',
			'/org/compiz/profiles/unity/plugins/unityshell/',
			'launcher-hide-mode',
			'int', flag)

	# get launcher auto hide mode
	def get_launcher_autohide(self):
		value = gsettings.get('org.compiz.unityshell',
			'/org/compiz/profiles/unity/plugins/unityshell/',
			'launcher-hide-mode', 'int')
		if value == 0:
			return False
		elif value == 1:
			return True
		else:
			return None

	# launcher icon size 32-64
	def set_launcher_icon_size(self, size):
		return gsettings.set('org.compiz.unityshell',
			'/org/compiz/profiles/unity/plugins/unityshell/',
			'icon-size',
			'int', size)

	# get launcher icon size
	def get_launcher_icon_size(self):
		return gsettings.get('org.compiz.unityshell',
			'/org/compiz/profiles/unity/plugins/unityshell/',
			'icon-size', 'int')

	# launcher 'show desktop' icon True/False
	def set_launcher_have_showdesktopicon(self, flag):
		launcher = gsettings.get_schema('com.canonical.Unity.Launcher')
		icons = launcher.get_strv('favorites')
		desktop = 'unity://desktop-icon'
		if flag == True:
			if desktop not in icons:
				icons.append(desktop)
				launcher.set_strv('favorites', icons)
		else:
			if desktop in icons:
				icons.remove(desktop)
				launcher.set_strv('favorites', icons)

	# get is launcher have 'show desktop' icon
	def get_launcher_have_showdesktopicon(self):
		launcher = gsettings.get_schema('com.canonical.Unity.Launcher')
		icons = launcher.get_strv('favorites')
		desktop = 'unity://desktop-icon'
		if desktop in icons:
			return True
		else:
			return False

# if __name__ == '__main__':
# 	uuu = Unity()
	# print uuu.get_launcher_icon_size()
	# print uuu.get_launcher_have_showdesktopicon()
	# uuu.set_launcher_autohide(0)
	# print uuu.get_launcher_autohide()
	# uuu.set_launcher_have_showdesktopicon(True)
	# uuu.set_launcher_icon_size(48)