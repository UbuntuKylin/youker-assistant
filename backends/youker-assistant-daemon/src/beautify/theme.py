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

import os
import gsettings
import utils

class Theme:
    homedir = ''

    def __init__(self):
        self.homedir = utils.get_home_dir()

    # ---------------themes---------------

    # get themes
    def get_themes(self):
        dirs = ('/usr/share/themes', os.path.join(self.homedir, ".themes"))
        filters = ('gtk-2.0', 'gtk-3.0', 'metacity-1')
        valid = utils.check_dirs(dirs, filters, True)
        valid.sort()
        return valid

    # get current theme
    def get_theme(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'gtk-theme', 'string')

    # set GTK theme and window theme
    def set_theme(self, theme):
        gstheme = gsettings.get_schema('org.gnome.desktop.interface')
        gstheme.set_string('gtk-theme',theme)
        _gstheme = gsettings.get_schema('org.gnome.desktop.wm.preferences')
        _gstheme.set_string('theme',theme)

    # get icon themes
    def get_icon_themes(self):
        dirs = ('/usr/share/icons', os.path.join(self.homedir, ".icons"))

        '''filters: if use only one filter string,
        the 'for' block in check_dirs() will split the filter string to single chars...'''
        filters = ('cursors', '#')
        valid = utils.check_dirs(dirs, filters, False)
        valid.sort()
        return valid

    # get current icon theme
    def get_icon_theme(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'icon-theme', 'string')

    # set icon theme
    def set_icon_theme(self, theme):
        gstheme = gsettings.get_schema('org.gnome.desktop.interface')
        gstheme.set_string('icon-theme',theme)

    # get cursor themes
    def get_cursor_themes(self):
        dirs = ('/usr/share/icons', os.path.join(self.homedir, ".icons"))

        '''filters: if use only one filter string,
        the 'for' block in check_dirs() will split the filter string to single chars...'''
        filters = ('cursors', '')
        valid = utils.check_dirs(dirs, filters, True)
        valid.sort()
        return valid

    # get current cursor theme
    def get_cursor_theme(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'cursor-theme', 'string')

    # set cursor theme
    def set_cursor_theme(self, theme):
        gstheme = gsettings.get_schema('org.gnome.desktop.interface')
        gstheme.set_string('cursor-theme', theme)

    def set_cursor_theme_with_root(self, theme):
        try :
            fd = open('/usr/share/icons/default/index.theme','w')
            fd.write('[Icon Theme]\n')
            fd.write('Inherits=' + theme + '\n')
            fd.close()
            return True
        except  Exception,e :
            return False

    # get cursor size
    def get_cursor_size(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'cursor-size', 'int')

    # set cursor size
    def set_cursor_size(self, size):
        gstheme = gsettings.get_schema('org.gnome.desktop.interface')
        gstheme.set_int('cursor-size',size)



    # ---------------fonts---------------

    # get font
    def get_font(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'font-name', 'string')

    # set font
    def set_font(self, font):
        return gsettings.set('org.gnome.desktop.interface',
            None,
            'font-name',
            'string', font)

    # get desktop font
    def get_desktop_font(self):
        return gsettings.get('org.gnome.nautilus.desktop',
            None, 'font', 'string')

    # set desktop font
    def set_desktop_font(self, font):
        return gsettings.set('org.gnome.nautilus.desktop',
            None,
            'font',
            'string', font)

    # get document font
    def get_document_font(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'document-font-name', 'string')

    # set document font
    def set_document_font(self, font):
        return gsettings.set('org.gnome.desktop.interface',
            None,
            'document-font-name',
            'string', font)

    # get monospace font
    def get_monospace_font(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'monospace-font-name', 'string')

    # set monospace font (use this func to change document font in ubuntu)
    def set_monospace_font(self, font):
        return gsettings.set('org.gnome.desktop.interface',
            None,
            'monospace-font-name',
            'string', font)

    # get window title font
    def get_window_title_font(self):
        return gsettings.get('org.gnome.desktop.wm.preferences',
            None, 'titlebar-font', 'string')

    # set window title font
    def set_window_title_font(self, font):
        return gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'titlebar-font',
            'string', font)

    # get font zoom
    def get_font_zoom(self):
        return gsettings.get('org.gnome.desktop.interface',
            None, 'text-scaling-factor', 'double')

    # set font zoom
    def set_font_zoom(self, zoom):
        return gsettings.set('org.gnome.desktop.interface',
            None,
            'text-scaling-factor',
            'double', zoom)

if __name__ == '__main__':
    ttt = Theme()
    # print ttt.get_font_zoom()
    # ttt.set_font_zoom(1.0)
    ttt.set_monospace_font('Ubuntu Mono 13')
    print ttt.get_monospace_font()
    # print ttt.get_theme()
    # print ttt.get_icon_theme()
    # print ttt.get_cursor_theme()
    # print ttt.get_cursor_size()
    # ttt.set_font('Ubuntu 11')
# 	print ttt.get_document_font()
# 	ttt.set_document_font('Sans 15')
    # ttt.set_window_title_font('Ubuntu Bold 11')
    # print ttt.get_font()
    # ttt.set_desktop_font('Ubuntu 11')
    # print ttt.get_desktop_font()
    # print ttt.get_document_font()
    # print ttt.get_window_title_font()
    # themes = ttt.get_themes()
    # print themes
    # print ttt.get_theme()
    # ttt.set_theme('ubuntukylin-theme')
    # ttt.set_theme('Radiance')
    # ttt.set_theme('Ambiance')
    # ttt.set_theme('HighContrast')
    # iconthemes = ttt.get_icon_themes()
    # print iconthemes
    # ttt.set_icon_theme('ubuntukylin-icon-theme')
    # cursorthemes = ttt.get_cursor_themes()
    # print cursorthemes
    # print ttt.get_cursor_theme()
    # ttt.set_cursor_theme(cursorthemes[1])
    # ttt.set_cursor_size(24)
