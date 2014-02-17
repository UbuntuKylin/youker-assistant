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

import os
import gsettings

class FileManager:
    def __init__(self):
        pass

    # 使用路径输入框取代路径栏
    # Get: Use the location entry instead of the pathbar
    def get_location_replace_pathbar(self):
        return gsettings.get('org.gnome.nautilus.preferences',
            None, 'always-use-location-entry', 'boolean')

    # Set: Use the location entry instead of the pathbar
    def set_location_replace_pathbar(self, flag):
        #gstheme = gsettings.get_schema('org.gnome.desktop.sound')
        #gstheme.set_string('theme-name',theme)
        return gsettings.set('org.gnome.nautilus.preferences',
            None,
            'always-use-location-entry',
            'boolean', flag)

    # 自动挂载媒体
    # Get: Automatically mount media
    def get_auto_mount_media(self):
        return gsettings.get('org.gnome.desktop.media-handling',
            None, 'automount', 'boolean')

    # Set: Automatically mount media
    def set_auto_mount_media(self, flag):
        return gsettings.set('org.gnome.desktop.media-handling',
            None,
            'automount',
            'boolean', flag)

    # 自动打开文件夹
    # Get: Automatically open a folder
    def get_auto_open_folder(self):
        return gsettings.get('org.gnome.desktop.media-handling',
            None, 'automount-open', 'boolean')

    # Set: Automatically open a folder
    def set_auto_open_folder(self, flag):
        return gsettings.set('org.gnome.desktop.media-handling',
            None,
            'automount-open',
            'boolean', flag)

    # 提示自动运行的程序
    # Get: Prompt or autorun/autostart programs
    def get_prompt_autorun_programs(self):
        return gsettings.get('org.gnome.desktop.media-handling',
            None, 'autorun-never', 'boolean')

    # Set: Prompt or autorun/autostart programs
    def set_prompt_autorun_programs(self, flag):
        return gsettings.set('org.gnome.desktop.media-handling',
            None,
            'autorun-never',
            'boolean', flag)

    # 缩略图图标尺寸（像素） min=16, max=512, step=16, default=64
    # Get: Thumbnail icon size (pixels)
    def get_thumbnail_icon_size(self):
        return gsettings.get('org.gnome.nautilus.icon-view',
            None, 'thumbnail-size', 'int')

    # Set: Thumbnail icon size (pixels)
    def set_thumbnail_icon_size(self, size):
        return gsettings.set('org.gnome.nautilus.icon-view',
            None,
            'thumbnail-size',
            'int', size)

    # 缩略图缓存时间（天数） min=-1, max=180, step=1, default=180
    # Get: Thumbnail cache time (days)
    def get_thumbnail_cache_time(self):
        return gsettings.get('org.gnome.desktop.thumbnail-cache',
            None, 'maximum-age', 'int')

    # Set: Thumbnail cache time (days)
    def set_thumbnail_cache_time(self, size):
        return gsettings.set('org.gnome.desktop.thumbnail-cache',
            None,
            'maximum-age',
            'int', size)

    # 最大缩略图缓存尺寸（MB） min=-1, max=512, step=1, default=512
    # Get: Maximum thumbnail cache size (MB)
    def get_thumbnail_cache_size(self):
        return gsettings.get('org.gnome.desktop.thumbnail-cache',
            None, 'maximum-size', 'int')

    # Set: Maximum thumbnail cache size (MB)
    def set_thumbnail_cache_size(self, size):
        return gsettings.set('org.gnome.desktop.thumbnail-cache',
            None,
            'maximum-size',
            'int', size)


if __name__ == '__main__':
    fm = FileManager()
    #value = fm.get_location_replace_pathbar()
    #if(value):
    #    fm.set_location_replace_pathbar(False)
    #else:
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

    value = fm.get_thumbnail_cache_size()
    if(value == 512):
        fm.set_thumbnail_cache_size(500)
    else:
        fm.set_thumbnail_cache_size(512)
