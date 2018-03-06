#!/usr/bin/python3
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

import configparser
import os, sys
import threading
from . import gsettings
from shutil import copy

class CloudConfig(threading.Thread):
    def __init__(self, sysdaemon):
        self.sysdaemon = sysdaemon
        self.conf = configparser.ConfigParser()
        self.home = os.path.expandvars('$HOME')
        self.youker_path = './'
        self.kuaipan_path = ''

    # write profiles
    def write_conf(self, section, conf_id, conf_schema, conf_path, conf_key, conf_type):
        value = gsettings.get(conf_schema, conf_path, conf_key, conf_type)
        if (conf_id in section):
            self.conf.set(conf_id, 'value', str(value))
        else:
            self.conf.add_section(conf_id)
            self.conf.set(conf_id, 'schema', conf_schema)
            self.conf.set(conf_id, 'path', conf_path)
            self.conf.set(conf_id, 'key', conf_key)
            self.conf.set(conf_id, 'type', conf_type)
            self.conf.set(conf_id, 'value', str(value))

    # Save system configuration
    def save_configuration_to_local_file(self, file_name):
        pass
#        self.conf.read(file_name)
#        sections = self.conf.sections()

#    # 桌面图标显示控制-----------------------------
#        self.write_conf(sections, 'show_desktop_icons',
#            'org.gnome.desktop.background',
#            None, 'show-desktop-icons', 'boolean')
#        self.write_conf(sections, 'show_homefolder',
#            'org.gnome.nautilus.desktop',
#            None, 'home-icon-visible', 'boolean')
#        self.write_conf(sections, 'show_network',
#            'org.gnome.nautilus.desktop',
#            None, 'network-icon-visible', 'boolean')
#        self.write_conf(sections, 'show_trash',
#            'org.gnome.nautilus.desktop',
#            None, 'trash-icon-visible', 'boolean')
#        self.write_conf(sections, 'show_devices',
#            'org.gnome.nautilus.desktop',
#            None, 'volumes-visible', 'boolean')

#    # 启动器设置----------------------------------
#        self.write_conf(sections, 'launcher_autohide',
#            'org.compiz.unityshell',
#            '/org/compiz/profiles/unity/plugins/unityshell/',
#            'launcher-hide-mode', 'int')
#        self.write_conf(sections, 'launcher_icon_size',
#            'org.compiz.unityshell',
#            '/org/compiz/profiles/unity/plugins/unityshell/',
#            'icon-size', 'int')

#    # 触摸板设置-----------------------------------
##        self.write_conf(sections, 'touchpad_enable',
##            'org.gnome.settings-daemon.peripherals.touchpad',
##            None, 'touchpad-enabled', 'boolean')
##        self.write_conf(sections, 'touch_horizontal_scrolling',
##            'org.gnome.settings-daemon.peripherals.touchpad',
##            None, 'horiz-scroll-enabled', 'boolean')
##        self.write_conf(sections, 'type_scroll_bar',
##            'com.canonical.desktop.interface',
##            None, 'scrollbar-mode', 'string')
##        self.write_conf(sections, 'touchpad_scrolling_mode',
##            'org.gnome.settings-daemon.peripherals.touchpad',
##            None, 'scroll-method', 'string')

#    # 字体设置-------------------------------------
#        self.write_conf(sections, 'default_font',
#            'org.gnome.desktop.interface',
#            None, 'font-name', 'string')
#        self.write_conf(sections, 'desktop_font',
#            'org.gnome.nautilus.desktop',
#            None, 'font', 'string')
#        self.write_conf(sections, 'document_font',
#            'org.gnome.desktop.interface',
#            None, 'document-font-name', 'string')
#        self.write_conf(sections, 'monospace_font',
#            'org.gnome.desktop.interface',
#            None, 'monospace-font-name', 'string')
#        self.write_conf(sections, 'window_title_font',
#            'org.gnome.desktop.wm.preferences',
#            None, 'titlebar-font', 'string')
#        self.write_conf(sections, 'font_zoom',
#            'org.gnome.desktop.interface',
#            None, 'text-scaling-factor', 'double')
#        self.write_conf(sections, 'font_hinting',
#            'org.gnome.settings-daemon.plugins.xsettings',
#            None, 'hinting', 'string')
#        self.write_conf(sections, 'font_antialiasing',
#            'org.gnome.settings-daemon.plugins.xsettings',
#            None, 'antialiasing', 'string')

#    # 主题设置-------------------------------------
#        #self.write_conf(sections, 'gtk_theme',
#        #    'org.gnome.desktop.interface',
#        #    None, 'gtk-theme', 'string')
##        self.write_conf(sections, 'window_theme',
##            'org.gnome.desktop.wm.preferences',
##            None, 'theme', 'string')
#        self.write_conf(sections, 'icon_theme',
#            'org.gnome.desktop.interface',
#            None, 'icon-theme', 'string')

#    # 窗口设置--------------------------------------
#        self.write_conf(sections, 'window_button',
#            'org.gnome.desktop.wm.preferences',
#            None, 'button-layout', 'string')
#        self.write_conf(sections, 'menus_have_icons',
#            'org.gnome.desktop.interface',
#            None, 'menus-have-icons', 'boolean')
#        self.write_conf(sections, 'titlebar_wheel',
#            'org.compiz.gwd',
#            None, 'mouse-wheel-action', 'string')
#        self.write_conf(sections, 'titlebar_double',
#            'org.gnome.desktop.wm.preferences',
#            None, 'action-double-click-titlebar', 'string')
#        self.write_conf(sections, 'titlebar_middle',
#            'org.gnome.desktop.wm.preferences',
#            None, 'action-middle-click-titlebar', 'string')
#        self.write_conf(sections, 'titlebar_right',
#            'org.gnome.desktop.wm.preferences',
#            None, 'action-right-click-titlebar', 'string')

#    # 文件管理器-----------------------------------
#        self.write_conf(sections, 'location_replace_pathbar',
#            'org.gnome.nautilus.preferences',
#            None, 'always-use-location-entry', 'boolean')
#        self.write_conf(sections, 'auto_mount_media',
#            'org.gnome.desktop.media-handling',
#            None, 'automount', 'boolean')
#        self.write_conf(sections, 'auto_open_folder',
#            'org.gnome.desktop.media-handling',
#            None, 'automount-open', 'boolean')
#        self.write_conf(sections, 'prompt_autorun_programs',
#            'org.gnome.desktop.media-handling',
#            None, 'autorun-never', 'boolean')
#        self.write_conf(sections, 'thumbnail_icon_size',
#            'org.gnome.nautilus.icon-view',
#            None, 'thumbnail-size', 'int')
#        self.write_conf(sections, 'thumbnail_cache_time',
#            'org.gnome.desktop.thumbnail-cache',
#            None, 'maximum-age', 'int')
#        self.write_conf(sections, 'thumbnail_cache_size',
#            'org.gnome.desktop.thumbnail-cache',
#            None, 'maximum-size', 'int')

#        fd = open(file_name, 'w')
#        self.conf.write(fd)
#        fd.close()

    # system settings
    def setconf(self, conf_id):
        conf_schema = self.conf.get(conf_id, 'schema')
        conf_path = self.conf.get(conf_id, 'path')
        if conf_path == 'None':
            conf_path = None
        conf_key = self.conf.get(conf_id, 'key')
        conf_type = self.conf.get(conf_id, 'type')
        if conf_type == 'boolean' :
            conf_value = self.conf.getboolean(conf_id, 'value')
        elif conf_type == 'int' :
            conf_value = self.conf.getint(conf_id, 'value')
        elif conf_type == 'double' or conf_type == 'float' :
            conf_value = self.conf.getfloat(conf_id, 'value')
        else :
            conf_value = self.conf.get(conf_id, 'value')
        #gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)

        if conf_id == 'window_button':
            value = gsettings.get('org.gnome.desktop.wm.preferences',
                        None, 'button-layout', 'string')
            left_list = ['close,minimize,maximize:', 'close,maximize,minimize:']
            right_list = [':minimize,maximize,close', ':maximize,minimize,close']
            if value in left_list and conf_value in right_list:
                    gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
                    self.sysdaemon.download_cloud_conf_signal('window_button')
            elif value in right_list and conf_value in left_list:
                    gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
                    self.sysdaemon.download_cloud_conf_signal('window_button')
        else:
            value = gsettings.get(conf_schema, conf_path, conf_key, conf_type)
            if value != conf_value:
                gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
                self.sysdaemon.download_cloud_conf_signal(conf_id)

        #----------------desktop icon settings----------------
        #if conf_id == 'show_desktop_icons':
        #    value = gsettings.get('org.gnome.desktop.background',
        #                None, 'show-desktop-icons', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('show_desktop_icons')
        #elif conf_id == 'show_homefolder':
        #    value = gsettings.get('org.gnome.nautilus.desktop',
        #                None, 'home-icon-visible', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('show_homefolder')
        #elif conf_id == 'show_network':
        #    value = gsettings.get('org.gnome.nautilus.desktop',
        #                None, 'network-icon-visible', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('show_network')
        #elif conf_id == 'show_trash':
        #    value = gsettings.get('org.gnome.nautilus.desktop',
        #                None, 'trash-icon-visible', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('show_trash')
        #elif conf_id == 'show_devices':
        #    value = gsettings.get('org.gnome.nautilus.desktop',
        #                None, 'volumes-visible', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('show_devices')

        #----------------launcher settings----------------
        #elif conf_id == 'launcher_autohide':
        #    value = gsettings.get('org.compiz.unityshell',
        #                '/org/compiz/profiles/unity/plugins/unityshell/',
        #                'launcher-hide-mode', 'int')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('launcher_autohide')
        #elif conf_id == 'launcher_icon_size':
        #    value = gsettings.get('org.compiz.unityshell',
        #                '/org/compiz/profiles/unity/plugins/unityshell/',
        #                'icon-size', 'int')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('launcher_icon_size')

        #----------------touchpad settings----------------
        #elif conf_id == 'touchpad_enable':
        #    value = gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
        #                None, 'touchpad-enabled', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('touchpad_enable')
        #elif conf_id == 'touch_horizontal_scrolling':
        #    value = gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
        #                None, 'horiz-scroll-enabled', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('touch_horizontal_scrolling')
        #elif conf_id == 'type_scroll_bar':
        #    value = gsettings.get('com.canonical.desktop.interface',
        #                None, 'scrollbar-mode', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('type_scroll_bar')
        #elif conf_id == 'touchpad_scrolling_mode':
        #    value = gsettings.get('org.gnome.settings-daemon.peripherals.touchpad',
        #                None, 'scroll-method', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('touchpad_scrolling_mode')

        #----------------font settings----------------
        #elif conf_id == 'default_font':
        #    value = gsettings.get('org.gnome.desktop.interface',
        #                None, 'font-name', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('default_font')
        #elif conf_id == 'desktop_font':
        #    value = gsettings.get('org.gnome.nautilus.desktop',
        #                None, 'font', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('desktop_font')
        #elif conf_id == 'document_font':
        #    value = gsettings.get('org.gnome.desktop.interface',
        #                None, 'document-font-name', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('document_font')
        #elif conf_id == 'monospace_font':
        #    value = gsettings.get('org.gnome.desktop.interface',
        #                None, 'monospace-font-name', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('monospace_font')
        #elif conf_id == 'window_title_font':
        #    value = gsettings.get('org.gnome.desktop.wm.preferences',
        #                None, 'titlebar-font', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('window_title_font')
        #elif conf_id == 'font_zoom':
        #    value = gsettings.get('org.gnome.desktop.interface',
        #                None, 'text-scaling-factor', 'double')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('font_zoom')
        #elif conf_id == 'font_hinting':
        #    value = gsettings.get('org.gnome.settings-daemon.plugins.xsettings',
        #                None, 'hinting', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('font_hinting')
        #elif conf_id == 'font_antialiasing':
        #    value = gsettings.get('org.gnome.settings-daemon.plugins.xsettings',
        #                None, 'antialiasing', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('font_antialiasing')


        #----------------theme settings----------------
        #elif conf_id == 'gtk_theme':
        #    value = gsettings.get('org.gnome.desktop.interface',
        #                None, 'gtk-theme', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('gtk_theme')
        #elif conf_id == 'window_theme':
        #    value = gsettings.get('org.gnome.desktop.wm.preferences',
        #                None, 'theme', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('window_theme')
        #elif conf_id == 'icon_theme':
        #    value = gsettings.get('org.gnome.desktop.interface',
        #                None, 'icon-theme', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('icon_theme')

        #----------------window settings----------------
        #elif conf_id == 'window_button':
        #    value = gsettings.get('org.gnome.desktop.wm.preferences',
        #                None, 'button-layout', 'string')
        #    left_list = ['close,minimize,maximize:', 'close,maximize,minimize:']
        #    right_list = [':minimize,maximize,close', ':maximize,minimize,close']
        #    if value in left_list and conf_value in right_list:
        #            gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #            self.sysdaemon.download_cloud_conf_signal('window_button')
        #    elif value in right_list and conf_value in left_list:
        #            gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #            self.sysdaemon.download_cloud_conf_signal('window_button')
        #elif conf_id == 'menus_have_icons':
        #    value = gsettings.get('org.gnome.desktop.interface',
        #                None, 'menus-have-icons', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('menus_have_icons')
        #elif conf_id == 'titlebar_wheel':
        #    value = gsettings.get('org.compiz.gwd',
        #                None, 'mouse-wheel-action', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('titlebar_wheel')
        #elif conf_id == 'titlebar_double':
        #    value = gsettings.get('org.gnome.desktop.wm.preferences',
        #                None, 'action-double-click-titlebar', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('titlebar_double')
        #elif conf_id == 'titlebar_middle':
        #    value = gsettings.get('org.gnome.desktop.wm.preferences',
        #                None, 'action-middle-click-titlebar', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('titlebar_middle')
        #elif conf_id == 'titlebar_right':
        #    value = gsettings.get('org.gnome.desktop.wm.preferences',
        #                None, 'action-right-click-titlebar', 'string')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('titlebar_right')

        #----------------file manager----------------
        #elif conf_id == 'location_replace_pathbar':
        #    value = gsettings.get('org.gnome.nautilus.preferences',
        #                None, 'always-use-location-entry', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('location_replace_pathbar')
        #elif conf_id == 'auto_mount_media':
        #    value = gsettings.get('org.gnome.desktop.media-handling',
        #                None, 'automount', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('auto_mount_media')
        #elif conf_id == 'auto_open_folder':
        #    value = gsettings.get('org.gnome.desktop.media-handling',
        #                None, 'automount-open', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('auto_open_folder')
        #elif conf_id == 'prompt_autorun_programs':
        #    value = gsettings.get('org.gnome.desktop.media-handling',
        #                None, 'autorun-never', 'boolean')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('prompt_autorun_programs')
        #elif conf_id == 'thumbnail_icon_size':
        #    value = gsettings.get('org.gnome.nautilus.icon-view',
        #                None, 'thumbnail-size', 'int')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('thumbnail_icon_size')
        #elif conf_id == 'thumbnail_cache_time':
        #    value = gsettings.get('org.gnome.desktop.thumbnail-cache',
        #                None, 'maximum-age', 'int')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('thumbnail_cache_time')
        #elif conf_id == 'thumbnail_cache_size':
        #    value = gsettings.get('org.gnome.desktop.thumbnail-cache',
        #                None, 'maximum-size', 'int')
        #    if value != conf_value:
        #        gsettings.set(conf_schema, conf_path, conf_key, conf_type, conf_value)
        #        self.sysdaemon.download_cloud_conf_signal('thumbnail_cache_size')

        # desktop icon settings
        #if conf_id == 'show_desktop_icons':
        #    self.sysdaemon.download_cloud_conf_signal('show_desktop_icons')
        #elif conf_id == 'show_homefolder':
        #    self.sysdaemon.download_cloud_conf_signal('show_homefolder')
        #elif conf_id == 'show_network':
        #    self.sysdaemon.download_cloud_conf_signal('show_network')
        #elif conf_id == 'show_trash':
        #    self.sysdaemon.download_cloud_conf_signal('show_trash')
        #elif conf_id == 'show_devices':
        #    self.sysdaemon.download_cloud_conf_signal('show_devices')

        # launcher settings
        #elif conf_id == 'launcher_autohide':
        #    self.sysdaemon.download_cloud_conf_signal('launcher_autohide')
        #elif conf_id == 'launcher_icon_size':
        #    self.sysdaemon.download_cloud_conf_signal('launcher_icon_size')

        # touchpad settings
        #elif conf_id == 'touchpad_enable':
        #    self.sysdaemon.download_cloud_conf_signal('touchpad_enable')
        #elif conf_id == 'touch_horizontal_scrolling':
        #    self.sysdaemon.download_cloud_conf_signal('touch_horizontal_scrolling')
        #elif conf_id == 'type_scroll_bar':
        #    self.sysdaemon.download_cloud_conf_signal('type_scroll_bar')
        #elif conf_id == 'touchpad_scrolling_mode':
        #    self.sysdaemon.download_cloud_conf_signal('touchpad_scrolling_mode')

        # font settings
        #elif conf_id == 'default_font':
        #    self.sysdaemon.download_cloud_conf_signal('default_font')
        #elif conf_id == 'desktop_font':
        #    self.sysdaemon.download_cloud_conf_signal('desktop_font')
        #elif conf_id == 'document_font':
        #    self.sysdaemon.download_cloud_conf_signal('document_font')
        #elif conf_id == 'monospace_font':
        #    self.sysdaemon.download_cloud_conf_signal('monospace_font')
        #elif conf_id == 'window_title_font':
        #    self.sysdaemon.download_cloud_conf_signal('window_title_font')
        #elif conf_id == 'font_zoom':
        #    self.sysdaemon.download_cloud_conf_signal('font_zoom')
        #elif conf_id == 'font_hinting':
        #    self.sysdaemon.download_cloud_conf_signal('font_hinting')
        #elif conf_id == 'font_antialiasing':
        #    self.sysdaemon.download_cloud_conf_signal('font_antialiasing')

        # theme settings
        #elif conf_id == 'gtk_theme':
        #    self.sysdaemon.download_cloud_conf_signal('gtk_theme')
        #elif conf_id == 'window_theme':
        #    self.sysdaemon.download_cloud_conf_signal('window_theme')
        #elif conf_id == 'icon_theme':
        #    self.sysdaemon.download_cloud_conf_signal('icon_theme')

        # window settings
        #elif conf_id == 'window_button':
        #    self.sysdaemon.download_cloud_conf_signal('window_button')
        #elif conf_id == 'menus_have_icons':
        #    self.sysdaemon.download_cloud_conf_signal('menus_have_icons')
        #elif conf_id == 'titlebar_wheel':
        #    self.sysdaemon.download_cloud_conf_signal('titlebar_wheel')
        #elif conf_id == 'titlebar_double':
        #    self.sysdaemon.download_cloud_conf_signal('titlebar_double')
        #elif conf_id == 'titlebar_middle':
        #    self.sysdaemon.download_cloud_conf_signal('titlebar_middle')
        #elif conf_id == 'titlebar_right':
        #    self.sysdaemon.download_cloud_conf_signal('titlebar_right')

        # file manager
        #elif conf_id == 'location_replace_pathbar':
        #    self.sysdaemon.download_cloud_conf_signal('location_replace_pathbar')
        #elif conf_id == 'auto_mount_media':
        #    self.sysdaemon.download_cloud_conf_signal('auto_mount_media')
        #elif conf_id == 'auto_open_folder':
        #    self.sysdaemon.download_cloud_conf_signal('auto_open_folder')
        #elif conf_id == 'prompt_autorun_programs':
        #    self.sysdaemon.download_cloud_conf_signal('prompt_autorun_programs')
        #elif conf_id == 'thumbnail_icon_size':
        #    self.sysdaemon.download_cloud_conf_signal('thumbnail_icon_size')
        #elif conf_id == 'thumbnail_cache_time':
        #    self.sysdaemon.download_cloud_conf_signal('thumbnail_cache_time')
        #elif conf_id == 'thumbnail_cache_size':
        #    self.sysdaemon.download_cloud_conf_signal('thumbnail_cache_size')

    
    # Restore the system configuration
    def use_cloud_configuration(self, file_name):
        print(file_name)
        self.conf.read(file_name)
        sections = self.conf.sections()
        for conf_id in sections:
            self.setconf(conf_id)
        return True

    # Get kuaipan directory address
    def get_kuaipan_path(self):
        kpconf = configparser.ConfigParser()
        kpconf.read(self.home + '/.config/ubuntukylin/kuaipan4uk.conf')
        return kpconf.get('client-info', 'Root')
        
    # Determine whether kuaipan process starts
    def kuaipan_run(self):
        ps = os.popen('pgrep kuaipan4uk')
        kuaipan_ps = ps.read()
        ps.close()
        return kuaipan_ps

    # Configuration file upload
    def real_upload_kysoft_cloud_conf(self):
        if not self.kuaipan_run():
        # 快盘没有启动或没有安装，提示用户安装并启动快盘才能上传
            self.sysdaemon.upload_cloud_conf_signal('upload_norun')
            return
        self.kuaipan_path = self.get_kuaipan_path() + '/[Ubuntu Kylin Sync]'
        if not os.path.isdir(self.kuaipan_path):
            os.makedirs(self.kuaipan_path)
        self.kuaipan_path = self.kuaipan_path + '/kylin-assistant'
        if not os.path.isdir(self.kuaipan_path):
            os.makedirs(self.kuaipan_path)
        self.youker_path = self.home + '/.config/ubuntukylin/kylin-assistant/'
        youker_abs_path = self.youker_path + 'kylin-settings-cloud.conf'
        self.save_configuration_to_local_file(youker_abs_path)
        copy(youker_abs_path, self.kuaipan_path)
        self.sysdaemon.upload_cloud_conf_signal('upload_ok')

    # Configuration file download
    def real_download_kysoft_cloud_conf(self):
        if not self.kuaipan_run():
        # 快盘没有启动或没有安装，提示用户安装并启动快盘才能下载
            self.sysdaemon.download_cloud_conf_signal('download_norun')
            return
        self.youker_path = self.home + '/.config/ubuntukylin/kylin-assistant/'
        youker_abs_path = self.youker_path + 'kylin-settings-cloud.conf'
        if not os.path.exists(youker_abs_path):
            os.mknod(youker_abs_path)
        cloud_abs_path = self.get_kuaipan_path() + '/[Ubuntu Kylin Sync]/kylin-assistant/kylin-settings-cloud.conf'
        if not os.path.isfile(cloud_abs_path):
        # 云端没有备份的配置文件
            self.sysdaemon.download_cloud_conf_signal('download_notconf')
            return
        copy(cloud_abs_path, self.youker_path)
        self.use_cloud_configuration(youker_abs_path)
        self.sysdaemon.download_cloud_conf_signal('download_ok')

    def upload_kysoft_cloud_conf(self):
        threading.Thread(target=self.real_upload_kysoft_cloud_conf, name='UpLoad').start()

    def download_kysoft_cloud_conf(self):
        threading.Thread(target=self.real_download_kysoft_cloud_conf, name='DownLoad').start()

if __name__ == '__main__':
    pass
    #cc = CloudConfig(None)
    #cc.upload_kysoft_cloud_conf()
    #cc.download_kysoft_cloud_conf()

