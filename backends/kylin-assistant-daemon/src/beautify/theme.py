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
from . import utils

class Theme:
    homedir = ''
    desktop = None

    def __init__(self):
        self.homedir = utils.get_home_dir()
        self.desktop = os.getenv('XDG_CURRENT_DESKTOP')
        if self.desktop is None:
             self.desktop = os.getenv('XDG_SESSION_DESKTOP')

    # ---------------themes---------------
    def set_ubuntukylin_default_setting(self, schema, title, key, type, default_value):
        if title == 'unity':
            return gsettings.set(schema, '/org/compiz/profiles/unity/plugins/unityshell/', key, type, default_value)
        else:
            return gsettings.set(schema, None, key, type, default_value)

    # -----------------默认值-----------------
    # Get Default Value
    def get_default_schema_value(self, schema, key):
        default_value = gsettings.get_schema_value(schema, key)
        if self.desktop != "mate" and self.desktop != "MATE":
            if (default_value in (None, '') and schema == 'org.gnome.nautilus.desktop' and key == 'font'):
                default_value = 'Ubuntu 11'
        return default_value

    # Set Default Value
    def set_default_schema_value(self, schema, key, type):
        default_value = self.get_default_schema_value(schema, key)
        if (default_value in (None, '') and schema == 'org.gnome.nautilus.desktop' and key == 'font'):
            default_value = 'Ubuntu 11'
        if default_value is not None:
            return gsettings.set(schema, None, key, type, default_value)
        else:
            raise NotImplemented
    # ----------------------------------

    # get themes
    def get_themes(self):
        dirs = ('/usr/share/themes', os.path.join(self.homedir, ".themes"))
        filters = ('gtk-2.0', 'gtk-3.0', 'metacity-1')
        valid = utils.check_dirs(dirs, filters, True)
        valid.sort()
        return valid

    # get current theme
    def get_theme(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.interface',
                None, 'gtk-theme', 'string')
        else:
            return gsettings.get('org.gnome.desktop.interface',
                None, 'gtk-theme', 'string')

    # set GTK theme and window theme
    def set_theme(self, theme):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gstheme = gsettings.get_schema('org.mate.interface')
            gstheme.set_string('gtk-theme',theme)
        else:
            gstheme = gsettings.get_schema('org.gnome.desktop.interface')
            gstheme.set_string('gtk-theme',theme)
            _gstheme = gsettings.get_schema('org.gnome.desktop.wm.preferences')
            _gstheme.set_string('theme',theme)

    #------------------------窗口主题设置
    # get window theme
    def get_window_themes(self):
        dirs = ('/usr/share/themes', os.path.join(self.homedir, ".themes"))
        filters = ['metacity-1']
        valid = utils.check_dirs(dirs, filters, True)
        valid.sort()
        return valid

    # get current window theme
    def get_current_window_theme(self):
        return gsettings.get('org.gnome.desktop.wm.preferences',
            None, 'theme', 'string')

    # set window theme
    def set_window_theme(self, theme):
        return gsettings.set('org.gnome.desktop.wm.preferences',
            None,
            'theme',
            'string', theme)



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
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.interface',
                None, 'icon-theme', 'string')
        else:
            return gsettings.get('org.gnome.desktop.interface',
                None, 'icon-theme', 'string')

    # set icon theme
    def set_icon_theme(self, theme):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gstheme = gsettings.get_schema('org.mate.interface')
            gstheme.set_string('icon-theme',theme)
        else:
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
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.peripherals-mouse',
                None, 'cursor-theme', 'string')
        else:
            return gsettings.get('org.gnome.desktop.interface',
                None, 'cursor-theme', 'string')

    # set cursor theme
    def set_cursor_theme(self, theme):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gstheme = gsettings.get_schema('org.mate.peripherals-mouse')
            gstheme.set_string('cursor-theme', theme)
        else:
            gstheme = gsettings.get_schema('org.gnome.desktop.interface')
            gstheme.set_string('cursor-theme', theme)

    def set_cursor_theme_with_root(self, theme):
        try :
            fd = open('/usr/share/icons/default/index.theme','w')
            fd.write('[Icon Theme]\n')
            fd.write('Inherits=' + theme + '\n')
            fd.close()
            return True
        except  Exception as e :
            return False

    # get cursor size
    def get_cursor_size(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.peripherals-mouse',
                None, 'cursor-size', 'int')
        else:
            return gsettings.get('org.gnome.desktop.interface',
                None, 'cursor-size', 'int')

    # set cursor size
    def set_cursor_size(self, size):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            gstheme = gsettings.get_schema('org.mate.peripherals-mouse')
            gstheme.set_int('cursor-size', size)
        else:
            gstheme = gsettings.get_schema('org.gnome.desktop.interface')
            gstheme.set_int('cursor-size', size)



    # ---------------fonts---------------

    # get font
    def get_font(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.interface',
                None, 'font-name', 'string')
        else:
            return gsettings.get('org.gnome.desktop.interface',
                None, 'font-name', 'string')

    # set font
    def set_font(self, font):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.interface',
                None,
                'font-name',
                'string', font)
        else:
            return gsettings.set('org.gnome.desktop.interface',
                None,
                'font-name',
                'string', font)

    # get desktop font
    def get_desktop_font(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.caja.desktop',
                None, 'font', 'string')
        else:
            return gsettings.get('org.gnome.nautilus.desktop',
                None, 'font', 'string')

    # set desktop font
    def set_desktop_font(self, font):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.caja.desktop',
                None,
                'font',
                'string', font)
        else:
            return gsettings.set('org.gnome.nautilus.desktop',
                None,
                'font',
                'string', font)

    # get document font
    def get_document_font(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.interface',
                None, 'document-font-name', 'string')
        else:
            return gsettings.get('org.gnome.desktop.interface',
                None, 'document-font-name', 'string')

    # set document font
    def set_document_font(self, font):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.interface',
                None,
                'document-font-name',
                'string', font)
        else:
            return gsettings.set('org.gnome.desktop.interface',
                None,
                'document-font-name',
                'string', font)

    # get monospace font
    def get_monospace_font(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.interface',
                None, 'monospace-font-name', 'string')
        else:
            return gsettings.get('org.gnome.desktop.interface',
                None, 'monospace-font-name', 'string')

    # set monospace font (use this func to change document font in ubuntu)
    def set_monospace_font(self, font):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.interface',
                None,
                'monospace-font-name',
                'string', font)
        else:
            return gsettings.set('org.gnome.desktop.interface',
                None,
                'monospace-font-name',
                'string', font)

    # get window title font
    def get_window_title_font(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'titlebar-font', 'string')
        else:
            return gsettings.get('org.gnome.desktop.wm.preferences',
                None, 'titlebar-font', 'string')

    # set window title font
    def set_window_title_font(self, font):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.gnome.desktop.wm.preferences',
                None,
                'titlebar-font',
                'string', font)
        else:
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

    # -------------------------平滑性----------------------------------
    # get all hinting value.    none:'No hinting',slight:'Basic',medium:'Moderate',full:'Maximum'
    def get_all_hinting(self):
        return ['none', 'slight', 'medium', 'full']
    
    # get current hinting
    def get_hinting(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.font-rendering',
                None,
                'hinting',
                'string')
        else:
            return gsettings.get('org.gnome.settings-daemon.plugins.xsettings',
                None,
                'hinting',
                'string')

    # set hinting
    def set_hinting(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.font-rendering',
                None,
                'hinting',
                'string', value)
        else:
            return gsettings.set('org.gnome.settings-daemon.plugins.xsettings',
                None,
                'hinting',
                'string', value)

    # -------------------------反锯齿----------------------------------
    # get all antialiasing value.  none:'No antialiasing', grayscale:'Standard grayscale antialiasing',rgba:'Subpixel antialiasing (LCD screens only)'
    def get_all_antialiasing(self):
        return ['none', 'grayscale', 'rgba']

    # get current antialiasing
    def get_antialiasing(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.font-rendering',
                None,
                'antialiasing',
                'string')
        else:
            return gsettings.get('org.gnome.settings-daemon.plugins.xsettings',
                None,
                'antialiasing',
                'string')

    # set antialiasing
    def set_antialiasing(self,value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.font-rendering',
                None,
                'antialiasing',
                'string', value)
        else:
            return gsettings.set('org.gnome.settings-daemon.plugins.xsettings',
                None,
                'antialiasing',
                'string', value)

if __name__ == '__main__':
    ttt = Theme()
    # print ttt.get_window_theme()
    # print ttt.get_current_window_theme()
    # print ttt.set_window_theme('Crux')
    # print ttt.get_current_hinting()
    # print ttt.get_current_antialiasing()
    # print ttt.set_hinting('none')
    # print ttt.set_antialiasing('none')
    # print ttt.get_font()
    # print ttt.set_font('Ubuntu 14')
    # print ttt.get_font_zoom()
    # ttt.set_font_zoom(1.0)
    #ttt.set_monospace_font('Ubuntu Mono 13')
    #print ttt.get_monospace_font()

    #aa = ttt.get_default_schema_value('org.gnome.nautilus.desktop', 'font')
    #print aa
    #ttt.set_default_schema_value('org.gnome.nautilus.desktop', 'font', 'string')
    #aa = ttt.get_default_schema_value('org.gnome.settings-daemon.plugins.xsettings', 'hinting')
    #print aa
    #ttt.set_default_schema_value('org.gnome.settings-daemon.plugins.xsettings', 'hinting', 'string')
    #bb = ttt.get_default_schema_value('org.gnome.settings-daemon.plugins.xsettings', 'antialiasing')
    #print bb

    aa = ttt.get_default_schema_value('org.gnome.desktop.interface', 'cursor-size')
    print(aa)
    bb = ttt.get_cursor_size()
    print(bb)
    ttt.set_default_schema_value('org.gnome.desktop.interface', 'cursor-size', 'int')

    #aa = ttt.get_default_schema_value('org.gnome.desktop.interface', 'font-name')
    #print aa
    # ttt.set_default_schema_value('org.gnome.desktop.interface', 'font-name', 'string')
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
