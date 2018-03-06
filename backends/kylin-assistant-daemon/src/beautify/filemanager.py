#! /usr/bin/env python3
# -*- coding: utf-8 -*-

### BEGIN LICENSE
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
#
# Author:     Kobe Lee <xiangli@ubuntukylin.com>
# Maintainer: Ubuntu Kylin
#
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

class FileManager:

    desktop = None

    def __init__(self):
        self.desktop = os.getenv('XDG_CURRENT_DESKTOP')
        if self.desktop is None:
             self.desktop = os.getenv('XDG_SESSION_DESKTOP')

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

    # -----------------使用路径输入框取代路径栏-----------------
    # Get: Use the location entry instead of the pathbar
    def get_location_replace_pathbar(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.caja.preferences',
                None, 'always-use-location-entry', 'boolean')
        else:
            return gsettings.get('org.gnome.nautilus.preferences',
                None, 'always-use-location-entry', 'boolean')

    # Set: Use the location entry instead of the pathbar
    def set_location_replace_pathbar(self, flag):
        #gstheme = gsettings.get_schema('org.gnome.desktop.sound')
        #gstheme.set_string('theme-name',theme)
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.caja.preferences',
                None,
                'always-use-location-entry',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.nautilus.preferences',
                None,
                'always-use-location-entry',
                'boolean', flag)

    # -----------------自动挂载媒体-----------------
    # Get: Automatically mount media
    def get_auto_mount_media(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.media-handling',
                None, 'automount', 'boolean')
        else:
            return gsettings.get('org.gnome.desktop.media-handling',
                None, 'automount', 'boolean')

    # Set: Automatically mount media
    def set_auto_mount_media(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.media-handling',
                None,
                'automount',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.desktop.media-handling',
                None,
                'automount',
                'boolean', flag)

    # -----------------自动打开文件夹-----------------
    # Get: Automatically open a folder
    def get_auto_open_folder(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.media-handling',
                None, 'automount-open', 'boolean')
        else:
            return gsettings.get('org.gnome.desktop.media-handling',
                None, 'automount-open', 'boolean')

    # Set: Automatically open a folder
    def set_auto_open_folder(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.media-handling',
                None,
                'automount-open',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.desktop.media-handling',
                None,
                'automount-open',
                'boolean', flag)

    # -----------------提示自动运行的程序-----------------
    # Get: Prompt or autorun/autostart programs
    def get_prompt_autorun_programs(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.media-handling',
                None, 'autorun-never', 'boolean')
        else:
            return gsettings.get('org.gnome.desktop.media-handling',
                None, 'autorun-never', 'boolean')

    # Set: Prompt or autorun/autostart programs
    def set_prompt_autorun_programs(self, flag):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.media-handling',
                None,
                'autorun-never',
                'boolean', flag)
        else:
            return gsettings.set('org.gnome.desktop.media-handling',
                None,
                'autorun-never',
                'boolean', flag)

    # -----------------缩略图图标尺寸（像素） min=16, max=512, step=16, default=64-----------------
    # Get: Thumbnail icon size (pixels)
    def get_thumbnail_icon_size(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.caja.icon-view',
                None, 'thumbnail-size', 'int')
        else:
            return gsettings.get('org.gnome.nautilus.icon-view',
                None, 'thumbnail-size', 'int')

    # Set: Thumbnail icon size (pixels)
    def set_thumbnail_icon_size(self, size):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.caja.icon-view',
                None,
                'thumbnail-size',
                'int', size)
        else:
            return gsettings.set('org.gnome.nautilus.icon-view',
                None,
                'thumbnail-size',
                'int', size)

    # -----------------缩略图缓存时间（天数） min=-1, max=180, step=1, default=180-----------------
    # Get: Thumbnail cache time (days)
    def get_thumbnail_cache_time(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.thumbnail-cache',
                None, 'maximum-age', 'int')
        else:
            return gsettings.get('org.gnome.desktop.thumbnail-cache',
                None, 'maximum-age', 'int')

    # Set: Thumbnail cache time (days)
    def set_thumbnail_cache_time(self, value):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.thumbnail-cache',
                None,
                'maximum-age',
                'int', value)
        else:
            return gsettings.set('org.gnome.desktop.thumbnail-cache',
                None,
                'maximum-age',
                'int', value)

    # -----------------最大缩略图缓存尺寸（MB） min=-1, max=512, step=1, default=512-----------------
    # Get: Maximum thumbnail cache size (MB)
    def get_thumbnail_cache_size(self):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.get('org.mate.thumbnail-cache',
                None, 'maximum-size', 'int')
        else:
            return gsettings.get('org.gnome.desktop.thumbnail-cache',
                None, 'maximum-size', 'int')

    # Set: Maximum thumbnail cache size (MB)
    def set_thumbnail_cache_size(self, size):
        if self.desktop == "mate" or self.desktop == "MATE" or self.desktop == "ukui" or self.desktop == "UKUI":
            return gsettings.set('org.mate.thumbnail-cache',
                None,
                'maximum-size',
                'int', size)
        else:
            return gsettings.set('org.gnome.desktop.thumbnail-cache',
                None,
                'maximum-size',
                'int', size)

if __name__ == '__main__':
    pass
#    fm = FileManager()
    #value = fm.get_location_replace_pathbar()
    #if(value):
    #    print "yes"
    #    fm.set_location_replace_pathbar(False)
    #else:
    #    print "False"
    #    fm.set_location_replace_pathbar(True)

    #value = fm.get_auto_mount_media()
    #if(value):
    #    fm.set_auto_mount_media(False)
    #else:
    #    fm.set_auto_mount_media(True)

    #value = fm.get_auto_open_folder()
    #if(value):
    #    fm.set_auto_open_folder(False)
    #else:
    #    fm.set_auto_open_folder(True)

    #value = fm.get_prompt_autorun_programs()
    #if(value):
    #    fm.set_prompt_autorun_programs(False)
    #else:
    #    fm.set_prompt_autorun_programs(True)

    #value = fm.get_thumbnail_icon_size()
    #if(value == 64):
    #    fm.set_thumbnail_icon_size(48)
    #else:
    #    fm.set_thumbnail_icon_size(64)

    #value = fm.get_thumbnail_cache_time()
    #if(value == 180):
    #    fm.set_thumbnail_cache_time(120)
    #else:
    #    fm.set_thumbnail_cache_time(180)

    #value = fm.get_thumbnail_cache_size()
    #aa = fm.test()
    #print aa
    #if(value == 512):
    #    fm.set_thumbnail_cache_size(500)
    #else:
    #    fm.set_thumbnail_cache_size(512)

#    aa = fm.get_default_schema_value('org.gnome.desktop.media-handling', 'automount')
#    print aa
#    #aa = fm.get_default_schema_value('org.gnome.desktop.media-handling', 'automount')
#    #print aa
#    #fm.set_default_schema_value('org.gnome.desktop.media-handling', 'automount', 'boolean')

#    bb = fm.get_default_schema_value('org.gnome.nautilus.desktop', 'font')
#    print bb
